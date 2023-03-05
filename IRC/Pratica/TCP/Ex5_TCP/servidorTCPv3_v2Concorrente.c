/*________________________________servidorTCP_Concorrente.c___________________________________*/
/*======================= Servidor concorrente TCP ============================
Este servidor destina-se mostrar mensagens recebidas via TCP, no porto
definido pela constante SERV_TCP_PORT.
Trata-se de um servidor que envia confirmacao (o comprimento, em bytes, da
mensagem recebida). 

Concorrente --> atende varios clientes em "simultaneo".

O atendimento de um determinado cliente termina quando a ligacao deixa de estar
operacional ou quando e' recebida a sequencia de caracteres definida
pela constante EXIT.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>

#define SERV_TCP_PORT  6000
#define BUFFERSIZE     1000
#define EXIT	"EXIT"

void Abort(char *msg, SOCKET s);
void AtendeCliente(LPVOID param);
int writeN(SOCKET sock,char * buffer,int nbytes);
int readLine(SOCKET sock,char * buffer,int nbytes);

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	SOCKET sock = INVALID_SOCKET, newSock = INVALID_SOCKET;
	int iResult;
	int cliaddr_len;	
	struct sockaddr_in cli_addr,serv_addr;
	WSADATA wsaData;
	SECURITY_ATTRIBUTES sa;
	DWORD thread_id;

	/*=============== INICIA OS WINSOCKS ==============*/
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if((sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		Abort("Impossibilidade de abrir socket", sock);

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  /*Recebe de qq interface*/
	serv_addr.sin_port=htons(SERV_TCP_PORT);  /*Escuta no porto Well-Known*/

	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if(bind(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == SOCKET_ERROR)
		Abort("Impossibilidade de registar-se para escuta", sock);

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if(listen(sock,5) == SOCKET_ERROR) 
		Abort("Impossibilidade de escutar pedidos", sock);

	/*================ PASSA A ATENDER CLIENTES INTERACTIVAMENTE =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if((newSock=accept(sock,(struct sockaddr *)&cli_addr,&cliaddr_len)) == SOCKET_ERROR)
			fprintf(stderr,"<SERV> Impossibilidade de aceitar cliente...\n");
		else{

			sa.nLength=sizeof(sa);
			sa.lpSecurityDescriptor=NULL;

			if(CreateThread(&sa,0 ,(LPTHREAD_START_ROUTINE)AtendeCliente, (LPVOID)newSock, (DWORD)0, &thread_id)==NULL){
				printf("Nao e' possivel iniciar uma nova thread (error: %d)\n", GetLastError());			
				printf("O cliente <%s:%d> nao sera' atendido\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
				closesocket(newSock);
			}

		}
	}
}

/*___________________________ AtendeCliente ____________________________________
Atende cliente. 
______________________________________________________________________________*/

void AtendeCliente(LPVOID param){
	char msg[BUFFERSIZE], resposta[BUFFERSIZE];
	static unsigned int cont=0;
	int nbytes, nBytesSent;
	SOCKET sock;
	struct sockaddr_in cli_addr;

	sock = (SOCKET)param;

	nbytes = sizeof(cli_addr);
	if(getpeername(sock, (struct sockaddr *)&cli_addr,&nbytes) != SOCKET_ERROR)
		printf("Sou a thread com id %d e vou atender o cliente <%s:%d>\n", GetCurrentThreadId(), inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

	/*==================== PROCESSA PEDIDOS ==========================*/
	do{	
		
		msg[0] = '\0'; //String vazia

		switch((nbytes=readLine(sock, msg, BUFFERSIZE))){

			case SOCKET_ERROR:
				fprintf(stderr,"\n<SER_%d> Erro na recepcao de dados...\n", GetCurrentThreadId());
				break;

			case  0:
				fprintf(stderr,"\n<SER_%d> O cliente encerrou a ligacao...\n", GetCurrentThreadId());
				break;

			default:
				msg[nbytes]='\0';
				printf("\n<SER_%d> Mensagem n. %d recebida {%s}\n", GetCurrentThreadId(), ++cont, msg);												

				/*============ ENVIA CONFIRMACAO =============*/
				printf("<SER_%d> Confirma recepcao de mensagem.\n", GetCurrentThreadId());
				sprintf_s(resposta, BUFFERSIZE, "%d\r\n", nbytes);
				nbytes=strlen(resposta);

				if((nBytesSent=writeN(sock, resposta, nbytes)) == SOCKET_ERROR)
					fprintf(stderr,"<SER_%d> Impossibilidade de Confirmar.\n", GetCurrentThreadId());
				else if(nBytesSent<nbytes)
					fprintf(stderr,"<SER_%d> Mensagem confirmada, mas truncada.\n", GetCurrentThreadId());
				else 
					printf("<SER_%d> Mensagem confirmada.\n", GetCurrentThreadId());
		}		
		
		if(strcmp(msg, EXIT)==0){
			printf("<SER_%d> E' para terminar...\n", GetCurrentThreadId());
			break;
		}

	}while(nbytes > 0);

	closesocket(sock);	
}

/*________________________________ Abort________________________________________
Mostra a mensagem de erro associada ao ultimo erro no SO e abando com 
"exit status" a 1
_______________________________________________________________________________
*/
void Abort(char *msg, SOCKET s)
{
	fprintf(stderr,"\a<SER_%d>Erro fatal: <%d>\n", WSAGetLastError(), GetCurrentThreadId());
	
	if(s != INVALID_SOCKET)
		closesocket(s);

	exit(EXIT_FAILURE);
}

/*______________________________ writeN _______________________________________
Escreve n bytes no socket em causa. Devolve o numero de bytes escritos ou
SOCKET_ERROR caso ocorra um erro ou 0 caso a ligacao seja encerrada.
______________________________________________________________________________*/

int writeN(SOCKET sock,char * buffer,int nbytes){

	int nLeft,nWritten;

	nLeft=nbytes;

	while(nLeft>0){

		nWritten=send(sock,buffer,nLeft, 0);

		if(nWritten == 0 || nWritten == SOCKET_ERROR)
			return(nWritten); /*Erro ou End Of File (0) */

		nLeft-=nWritten;
		buffer+=nWritten;

	}

	return(nWritten);
}

/*______________________________ readLine _______________________________________
Le uma linha de texto (conjunto de caracteres terminados em '\n') 
no socket em causa.

Regressa quando encontra o caractere '\n', quando o buffer fica cheio,
quando a ligacao TCP e' encerrada ou quando quando ocorre um erro.

Devolve o numero de bytes lidos ou SOCKET_ERROR caso ocorra um erro.
______________________________________________________________________________*/

int readLine(SOCKET sock,char * buffer,int nbytes){

	int nread;

	int i;
	char c;

	i = 0;

	while(i < nbytes-1){ /* -1 para deixar espaco ao '\0' */
		
		nread = recv(sock, &c, sizeof(c), 0);
	
		if(nread == SOCKET_ERROR)
			return nread; /*Erro*/

		if(nread == 0)
			break; /*End Of File*/

		if(c == '\r')
			continue; /*Ignora o '\r' numa sequencia "\r\n"*/
		
		if(c == '\n')
			break; /*Final da linha*/

		buffer[i++] = c;
	}
	
	buffer[i] = '\0';
	
	return i;
}


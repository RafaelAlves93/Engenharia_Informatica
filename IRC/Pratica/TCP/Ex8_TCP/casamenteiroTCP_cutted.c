/*_______________________________casamenteiroTCP.C___________________________________*/
/*============================= Servidor concorrente TCP  =========================
Este servidor destina-se a colocar em contacto pares de clientes.
Forma os pares de forma sucessiva.
Em cada par, sempre que recebe um byte num dos sockets, reencaminha-o para o outro.
===========================================
========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define TIMEOUT		3   //segundos
#define BUFFERSIZE	4096
#define MSG_BOAS_VINDAS "Servidor Casamenteiro\r\nAguarde...\r\n"
#define MSG_ARRANQUE_CONVERSA "Pode iniciar conversa com par...\r\n"

struct /* */; //uma estrutura para 2 sockets

void AtendeCliente(LPVOID param);
int exchange(SOCKET s1, SOCKET s2);
void Abort(char *msg, SOCKET s);

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	SOCKET sock = /**/, newSock = /**/; //iniciar sockets
	int iResult;
	int cliaddr_len;
	struct sockaddr_in cli_addr, serv_addr;
	WSADATA wsaData;
	SECURITY_ATTRIBUTES sa;
	DWORD thread_id;
	SOCKET /* */; //algo que possa conter 2 sockets
	int contador;
	struct /* */; //um ponteiro para a estrutura que tem os 2 sockets

	if(argc!=2){
		fprintf(stderr, "Usage: %s <porto de escuta>\n",argv[0]); 
		exit(EXIT_SUCCESS);
	}

	/*=============== INICIA OS WINSOCKS ==============*/
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
		Abort("Impossibilidade de abrir socket", sock);

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr = htonl(/* */);  /*Recebe de qq interface*/
	serv_addr.sin_port = htons(/**/(argv[1]));  /*Escuta no porto Well-Known*/

	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if (/**/(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Abort("Impossibilidade de registar-se para escuta", sock);

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if (/**/(sock, 5) == SOCKET_ERROR)
		Abort("Impossibilidade de escutar pedidos", sock);

	printf("<SER> Servidor casamenteiro pronto no porto de escuta: %s\n", argv[1]);

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len=sizeof(cli_addr);
	contador = 0;
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if(/* */ == SOCKET_ERROR){

			if(WSAGetLastError() == WSAEINTR)
				continue;

			fprintf(stderr,"<SERV> Impossibilidade de aceitar cliente...\n");

		}else{

			printf("<SER> Novo cliente conectado: <%s:%d>.\n", /*..importante..*/(cli_addr.sin_addr), /*.....*/(cli_addr.sin_port));

			/* */ //envia mensagem MSG_BOAS_VINDAS ao cliente conectado

			/* */ //copia socket do cliente conectada para "algo que possa conter 2 sockets"

			if(contador == 2){

				contador = 0;

				/* */ = (/* */); //alocar espaco em memoria (dinamica) para os sockets na estrutura

				if(/* */ == NULL){

					printf("<SER> Nao foi possivel reservar espaco para passar parametros\n!");			
					closesocket(/*...*/); closesocket(/*...*/);
				
				}else{

					/* */ = /*...*/;  //passa o socket de "algo que possa conter 2 sockets" para a estrutura, ponteiro?
					/* */ = /*...*/;

					sa.nLength=sizeof(sa);
					sa.lpSecurityDescriptor=NULL;

					if (/* */) == NULL){ //cria thread, inicia atendecliente passa ponteiro
						printf("<SER> Nao foi possivel iniciar uma nova thread (error: %d)!\n", GetLastError());			
						printf("<SER> O par actual nao sera' atendido!\n");
						closesocket(ligacoesAceites[0]); closesocket(ligacoesAceites[1]);
					}

					printf("<SER> Um novo par acaba de ser formado.\n");

				}
			}
		}
	}
}

/*___________________________ AtendeCliente ____________________________________
Atende cliente.
______________________________________________________________________________*/

void AtendeCliente(LPVOID param){
	SOCKET sockCli1, sockCli2;
	fd_set fdread, fdtemp;
	struct ParSockets *p;
	int i;
	//struct timeval timeout = {TIMEOUT, 0};	

	//Obtem parametros (sockets para os elementos do par)
	p = /* */;
	sockCli1 =/* */; //usar o ponteiro
	sockCli2 =/* */;
	free(p);

	send(/* */), 0);
	send(/* */, 0);

	/* */(&fdread); //fd...
	/* */(sockCli1, &fdread);
	/* */(sockCli2, &fdread);

	while(1){
		/*==================== PROCESSA PEDIDO ==========================*/

		fdtemp=fdread;
		//timeout.tv_sec=TIMEOUT;
		//timeout.tv_usec=0;

		switch (/* */(/* */)){ // select - Sem timeout
		
			case SOCKET_ERROR:
				if(WSAGetLastError()==WSAEINTR)
					break;

				fprintf(stderr, "<SER_%d> Erro na rotina select (%d) ...\n", /*vai buscar id da thread*/(), WSAGetLastError());
				closesocket(sockCli1); closesocket(sockCli2);
				return;

			case  0:printf(".");
				break;

			default:
				if (/* */(sockCli1, &fdtemp)){
					if(exchange(sockCli1, sockCli2) <= 0){
						closesocket(sockCli1); closesocket(sockCli2);
						return;
					}
				}

				if (/* */(sockCli2, &fdtemp)){
					if(exchange(sockCli2, sockCli1) <= 0){
						closesocket(sockCli2); closesocket(sockCli1);
						return;
					}
				}

				break;
		} //switch
	} //while
}

/*_____________________________ exchange _______________________________________
Recebe um caractere do primeiro socket e escreve-o no segundo

Devolve:
	SOCKET_ERROR : se houve erro
			   0 : EOF
	        >= 0 : se leu algum byte
______________________________________________________________________________*/
int exchange(SOCKET s1, SOCKET s2)
{
	int result;
	char c;

	if (result =/* */(/* */) == sizeof(/* */))  //recebe de um, envia para outro
		result =/* */;

	if(result==0)
		fprintf(stderr, "<SER_%d> Connection closed by foreign host\n", GetCurrentThreadId());

	if (result == /* */){ //deu erro
		fprintf(stderr, "<SER_%d> Erro no acesso para I/O a um dos sockets (%d)\n", GetCurrentThreadId(), WSAGetLastError());	
	}

	return result;
}

/*________________________________ Abort________________________________________
Mostra a mensagem de erro associada ao ultimo erro dos Winsock e abandona com 
"exit status" a 1
_______________________________________________________________________________
*/
void Abort(char *msg, SOCKET s)
{
	fprintf(stderr,"\a<SER_%d> Erro fatal: <%d>\n", WSAGetLastError(), GetCurrentThreadId());
	
	if(s != INVALID_SOCKET)
		closesocket(s);

	exit(EXIT_FAILURE);
}

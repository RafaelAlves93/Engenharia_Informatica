/*________________________________PROXY.C___________________________________*/
/*======================= Servidor concorrente Proxy =========================
Este servidor destina-se a servir de proxy para acesso a um determinado servidor.
O porto de escuta bem como o IP/nome e porto do servidor sao passados na linha
de comando.
============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define TIMEOUT		3   //segundos
#define BUFFERSIZE	4096

void AtendeCliente(LPVOID param);
int exchange(/* */); //vai trocar mensagens de um socket para outro
void Abort(char *msg, SOCKET s);

struct sockaddr_in dest_addr;

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	SOCKET sock = INVALID_SOCKET, newSock = INVALID_SOCKET;
	int iResult;
	int cliaddr_len;
	struct sockaddr_in /* */;
	struct hostent *info; //<-- importante saber usar
	WSADATA wsaData;
	SECURITY_ATTRIBUTES sa;
	DWORD thread_id;

	printf("Ola'\n");
	
	if(argc!=4){
		fprintf(stderr, "Usage: %s <porto de escuta> <maquina destino> <porto destino>\n",argv[0]); 
		exit(EXIT_SUCCESS);
	}

	/*=============== INICIA OS WINSOCKS ==============*/
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*===== PREENCHE A ESTRUTURA DE ENDERECO PARA O SERVIDOR ============*/
	memset((char *)/* */, 0, sizeof(/* */)); // DESTINO
	/* */.sin_family = AF_INET;
	/* */.sin_port = /* */;
	/* */.sin_addr.s_addr = /* */;

	//Resolve o nome caso seja necessario ...
	if (dest_addr.sin_addr.s_addr ==/* */)
	if ((info = /* */(argv[2])) == NULL)
			Abort("Host desconhecido", sock);
		else
			memcpy(/* */);

	/*================== ABRE SOCKET PARA ESCUTA DE CLIENTES ================*/
	if ((sock =/**/(/**/)) == /**/)
		Abort("Impossibilidade de abrir socket", sock);

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr =/**/(INADDR_ANY);  /*Recebe de qq interface*/
	serv_addr.sin_port = /**/(/**/(argv[1]));  /*Escuta no porto Well-Known*/

	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if (/**/(/* */) == SOCKET_ERROR)
		Abort("Impossibilidade de registar-se para escuta", sock);

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if (/**/(sock, 5) == SOCKET_ERROR)
		Abort("Impossibilidade de escutar pedidos", sock);

	printf("<SER> Servidor proxy pronto no porto de escuta: %s\n", argv[1]);
	printf("<SER> A fazer de \"ponte para\": <%s:%s>\n\n", argv[2], argv[3]);

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len=sizeof(cli_addr);
	while(1){
		/*====================== ATENDE PEDIDO ========================*/
		if ((newSock =/* */) == SOCKET_ERROR){

			if(WSAGetLastError() == WSAEINTR)
				continue;

			fprintf(stderr,"<SERV> Impossibilidade de aceitar cliente...\n");

		}else{

			sa.nLength=sizeof(sa);
			sa.lpSecurityDescriptor=NULL;

			if (/* */) == NULL){
				printf("<SER> Nao e' possivel iniciar uma nova thread (error: %d)\n", GetLastError());			
				printf("<SER> O cliente <%s:%d> nao sera' atendido\n", /*....*/(cli_addr.sin_addr), /**/(cli_addr.sin_port));
				closesocket(newSock);
			}

			printf("<SER> Cliente <%s:%d> atendido pela thread com id: %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), thread_id);
		}
	}
}

/*___________________________ AtendeCliente ____________________________________
Atende cliente.
______________________________________________________________________________*/

void AtendeCliente(LPVOID param){
	SOCKET sockCli, sockDest; // sockDest: socket para comunicar como o servidor
	fd_set /* */;
	struct timeval timeout = {TIMEOUT, 0};	

	sockCli = (SOCKET)param;

	if ((/* */(PF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR){
		fprintf(stderr,"<SER_%d> Erro na criacao do socket para comunicar com o destino (%d)...\n", GetCurrentThreadId(), WSAGetLastError());
		closesocket(sockCli);
		return;
	}

	if (/* */) == SOCKET_ERROR){
		fprintf(stderr,"<SER_%d> Erro na ligacao ao destino (%d)...\n", GetCurrentThreadId(), WSAGetLastError());	
		closesocket(sockCli); closesocket(sockDest);
		return;
	}

	//limpar e preencher estrutura fd
	FD_/**/(/**/);
	FD_/**/(/* */);
	FD_/**/(/* */);

	while(1){
		/*==================== PROCESSA PEDIDO ==========================*/

		fdtemp=fdread;
		//timeout.tv_sec=TIMEOUT;
		//timeout.tv_usec=0;

		switch (select(/* */)){ // Sem timeout
		//switch(select()){
			case SOCKET_ERROR:
				if(WSAGetLastError()==WSAEINTR)
					break;

				fprintf(stderr,"<SER_%d> Erro na rotina select (%d) ...\n", GetCurrentThreadId(), WSAGetLastError());
				/**/(/**/); /**/(/**/); //feche os sockets
				return;

			case  0:printf(".");
				break;

			default:
				if (/* */){
					if (exchange(/**/, /**/) <= 0){  //que significa <= 0?
						closesocket(sockCli); closesocket(sockDest);
						return;
					}
				}

				if (/* */){
					if (exchange(/**/, /**/) <= 0){
						closesocket(sockDest); closesocket(sockCli);
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
int exchange(/**/, /**/)
{
	int result;
	char c;

	if (/* */ == sizeof(/**/)) //recebe de um e envia para outro
		result = /**/(/* */), 0);

	if (result ==/**/) //nao leu nada
		fprintf(stderr, "<SER_%d> Connection closed by foreign host\n", GetCurrentThreadId());

	if (result == /**/){ //erro
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

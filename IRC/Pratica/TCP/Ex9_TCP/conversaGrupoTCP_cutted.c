/*_______________________________conversaGrupoTCP.C___________________________________*/
/*============================= Servidor concorrente TCP  =========================
Este servidor destina-se a colocar em contacto grupos de clientes.
Forma grupos de forma sucessiva.
Um grupo fica formado quando o limite MAX_TAM_GRUPO e' atingido ou
se aguarda mais de LIMIT_ESPERA segundo.
Em cada grupo, sempre que um byte e' recebido num dos sockets, 
reencaminha-o para os restantes.
===================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define TIMEOUT		3   //segundos
#define BUFFERSIZE	4096
#define MAX_TAM_GRUPO 5
#define LIMITE_ESPERA 30 //segundos
#define MSG_BOAS_VINDAS "Servidor conversa em grupo\r\nAguarde...\r\n"
#define MSG_ARRANQUE_CONVERSA "Pode iniciar conversa...\r\n"

//criar uma estrutura para MAX_TAM_GRUPO sockets
struct /* */; 

void fechaSockets(/* */); //passa ponteiro e tamanho
void AtendeCliente(LPVOID param);
//reenvia, ou seja, quem enviou, para quem vai enviar(todos menos ele proprio)
//e tamanho (quantos sao, podem ser menos que MAX_TAM_GRUPO)
int difunde(/* */); 
void Abort(char *msg, SOCKET s);

/*________________________________ main ________________________________________
*/
int main(int argc,char *argv[]){

	SOCKET sock = INVALID_SOCKET, newSock = INVALID_SOCKET;
	int iResult;
	int cliaddr_len;
	struct sockaddr_in cli_addr, serv_addr;
	WSADATA wsaData;
	SECURITY_ATTRIBUTES sa;
	DWORD thread_id;
	SOCKET /* */; //algo para conter MAX_TAM_GRUPO sockets
	int contador, tam, i;
	struct /* */; //ponteiro para a estrutura dos sockets
	int ocorrenciaTimeout;
	fd_set fd_accept;
	struct timeval tempoEspera;

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
	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) == /*...*/)
		Abort("Impossibilidade de abrir socket", sock);

	/*=================== PREENCHE ENDERECO DE ESCUTA =======================*/
	memset(/*...*/, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr = htonl(/*...*/);  /*Recebe de qq interface*/
	serv_addr.sin_port=htons(atoi(argv[1]));  /*Escuta no porto Well-Known*/

	/*====================== REGISTA-SE PARA ESCUTA =========================*/
	if (/* */(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Abort("Impossibilidade de registar-se para escuta", sock);

	/*============ AVISA QUE ESTA PRONTO A ACEITAR PEDIDOS ==================*/
	if(/* */ == SOCKET_ERROR)
		Abort("Impossibilidade de escutar pedidos", sock);

	printf("<SER> Servidor conversa em grupo pronto no porto de escuta: %s\n", argv[1]);

	/*========== PASSA A ATENDER CLIENTES DE FORMA CONCORRENTE  =============*/
	cliaddr_len =/*...*/;
	contador = 0;
	
	while(1){
		/* Caso o grupo ja' tenha pelo menos 2 elementos,
		 * aguarda LIMITE_ESPERA ate' dar a constituicao do grupo
		 * por concluida. Caso contrario, aguarda um novo pedido
		 * de ligacao sem timeout.
		 * O timeout e' realizado 'a custa da funcao "select()".
		 */
		ocorrenciaTimeout=0; //false

		if(contador >= 2){
			
			FD_ZERO(/*...*/);
			FD_SET(sock, &fd_accept);
			
			tempoEspera.tv_sec = LIMITE_ESPERA;
			tempoEspera.tv_usec = 0;

			switch (select(32, /*...*/, NULL, NULL,/*...*/)){ //Com tempo de espera
				case SOCKET_ERROR:
					fprintf(stderr,"<SERV> Erro ao invocar \"select()\" para efeitos de timeout de ligacao (error: %d)!\n");
					continue;
				case 0:
					ocorrenciaTimeout = 1;
					break;
				default:
					break;
			}

		}

		if(!ocorrenciaTimeout){
			/*====================== ATENDE PEDIDO ========================*/
			if ((/* */ = /* */(sock, (struct sockaddr *)&cli_addr, &cliaddr_len)) == SOCKET_ERROR){

				if(WSAGetLastError() == WSAEINTR)
					continue;
				
				fprintf(stderr,"<SERV> Impossibilidade de aceitar cliente...\n");
				continue;				
			}

			printf("<SER> Novo cliente conectado: <%s:%d>.\n",/* */(cli_addr.sin_addr), /* */(cli_addr.sin_port));
			send(/* ....... */); //envia MSG_BOAS_VINDAS
			/*...*/[/*...*/++] = newSock; //passa o socket para "algo" que pode conter varios sockets

		}

		if(contador == /* maximo */ || (ocorrenciaTimeout && contador>=2)){

			tam = contador;
			contador = 0;

			/* */ = (struct /* */ *)/* */(sizeof(struct /* */)); //ponteiro, alocar espaco memoria dinamica

			if(/* */ == NULL){ //nao conseguiu alocar espaco

				printf("<SER> Nao foi possivel reservar espaco para passar parametros\n!");			
				fechaSockets(/* */, tam);
				
			}else{

				/* */ = tam; //passa o tam para a estrutura (ponteiro)
				for (i = 0; i < tam; i++)
					/* */->/*...*/[i] = /*...*/; //passa os sockets de "algo para conter sockets" para a estrutura

				sa.nLength=sizeof(sa);
				sa.lpSecurityDescriptor=NULL;

				if (/* */(&sa, 0, (LPTHREAD_START_ROUTINE)AtendeCliente, (LPVOID)parametrosThreadAtendeCliente, (DWORD)0, &thread_id) == NULL){
					printf("<SER> Nao foi possivel iniciar uma nova thread (error: %d)!\n", GetLastError());			
					printf("<SER> O grupo actual nao sera' atendido!\n");
					fechaSockets(grupoSockets, contador);
				}

				printf("<SER> Um novo grupo acaba de ser formado com %d elementos.\n", tam);

			}
		}
	}
}

/*___________________________ fechaSockets ____________________________________
______________________________________________________________________________*/
void fechaSockets(SOCKET *grupo, int tam)
{
	int i;

	for(i=0; i<tam; i++)
		closesocket(/* */); //fechar todas as sockets
}


/*___________________________ AtendeCliente ____________________________________
Atende cliente.
______________________________________________________________________________*/

void AtendeCliente(LPVOID param){
	fd_set /*...*/, /*...*/;
	struct /*...*/ *grupo;
	int i;
	//struct timeval timeout = {TIMEOUT, 0};	

	grupo = (/*...*/ *)param;

	for (i = 0; i</* */; i++){
		send(/* */, MSG_ARRANQUE_CONVERSA, strlen(MSG_ARRANQUE_CONVERSA), 0);
	}

	FD_ZERO(&fdread);
	for (i = 0; i</* */; i++){
		FD_SET(/* */, &fdread);
	}

	while(1){
		/*==================== PROCESSA PEDIDO ==========================*/

		fdtemp=fdread;
		//timeout.tv_sec=TIMEOUT;
		//timeout.tv_usec=0;

		switch (/*...*/(32, &fdtemp, NULL, NULL, NULL)){ // Sem timeout
		//switch(select(32, &fdtemp, NULL, NULL, &timeout)){
			case SOCKET_ERROR:
				if(WSAGetLastError()==WSAEINTR)
					break;

				fprintf(stderr,"<SER_%d> Erro na rotina select (%d) ...\n", GetCurrentThreadId(), WSAGetLastError());
				fechaSockets(grupo->sockets, grupo->tamGrupo);
				free(grupo);
				return;

			case  0:printf(".");
				break;

			default:
				for (i = 0; i</* */; i++){

					if (FD_ISSET(/* */, &fdtemp)){
						if (difunde(/* */) <= 0){
							fechaSockets(/* */);
							free(grupo);
							return;
						}
					}

				}
					
				break;
		} //switch
	} //while
}

/*_____________________________ difunde _______________________________________
Recebe um caractere em s1 e reenvia-o para o grupo.
Não reenvia para s1.
Quando ocorre um problema com um dos elementos do grupo,
o grupo e' eliminado.

Devolve:
	SOCKET_ERROR : se houve erro
			   0 : EOF
	        >= 0 : se leu algum byte
______________________________________________________________________________*/
int difunde(SOCKET origem, SOCKET *grupo, int tam)
{
	int result, i;
	char c;

	if (result =/* */ == sizeof(/*...*/)){ //recebe mensagem, de quem?

		for(i=0; i<tam; i++){

			if (origem !=/* */) //nao vai enviar para ele proprio...
				result =/* */(grupo[i], &c, sizeof(char), 0);
			
			if(result == 0 || result == SOCKET_ERROR)
				break;

		}

	}

	if(result==0)
		fprintf(stderr, "<SER_%d> Connection closed by foreign host\n", GetCurrentThreadId());

	if(result == SOCKET_ERROR){
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

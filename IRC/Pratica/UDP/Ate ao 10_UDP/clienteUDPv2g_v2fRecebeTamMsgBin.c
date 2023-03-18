/*=========================== Cliente basico UDP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cuja localizacao e' igualmente
passada na linha de comando.

Aguarda pela resposta (inteiro em formato binário) um maximo de 
TIMEOUT segundos e verifica a origem.

O protocolo usado e' o UDP e o timeout e' baseado na rotina setsockopt().
==============================================================================*/

#include <stdio.h>
#include <winsock.h>

#define BUFFERSIZE	4096
#define TIMEOUT		10000 //msec

void Abort(char *msg);

/*________________________________ main _______________________________________
*/

int main( int argc , char *argv[] )
{

	SOCKET sockfd;
	int iResult, msg_len, nbytes;
	int tam, response;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFFERSIZE];
	DWORD timeout;
	WSADATA wsaData;

	timeout = TIMEOUT;

	/*========================= TESTA A SINTAXE =========================*/

	if(argc != 4){
		fprintf(stderr,"Sintaxe: %s frase_a_enviar ip_destino porto_destino\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=============== INICIA OS WINSOCKS ==============*/

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*=============== CRIA SOCKET PARA ENVIO/RECEPCAO DE DATAGRAMAS ==============*/

	sockfd = socket( PF_INET , SOCK_DGRAM , 0 );
	if(sockfd == INVALID_SOCKET)
		Abort("Impossibilidade de criar socket");

	/*================ CONFIGURA O SOCKET PARA TIMEOUT DE RECEPCAO ==============*/
	
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/

	memset( (char*)&serv_addr, 0 , sizeof(serv_addr) ); /*Coloca a zero todos os bytes*/
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]); /*IP no formato "dotted decimal" => 32 bits*/
	serv_addr.sin_port = htons(atoi(argv[3])); /*Host TO Netowork Short*/

	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/

	msg_len = strlen(argv[1]);
	if(sendto( sockfd , argv[1] , msg_len , 0 , (struct sockaddr*)&serv_addr , sizeof(serv_addr) ) == SOCKET_ERROR)
		Abort("SO nao conseguiu aceitar o datagram");

	/*==================== OBTEM O PORTO ATRIBUIDO PELO SO  ==============*/

	tam = sizeof(cli_addr);	
	if (getsockname(sockfd, (struct sockaddr *)&cli_addr, &tam) != SOCKET_ERROR)
		printf("<CLI1>O porto atribuido pelo SO e': %d\n", ntohs(cli_addr.sin_port));

	printf("<CLI1>Mensagem enviada ... a entrega nao e' confirmada.\n"); 

	/*======================== AGUARDA RESPOSTA ==========================*/

	tam = sizeof(serv_addr);
	nbytes = recvfrom(sockfd, (char *)&response, sizeof(response),0,(struct sockaddr *)&serv_addr, &tam); //ex10
	//nbytes = recvfrom(sockfd, (char*)&par_addr, sizeof(par_addr), 0, (struct sockaddr*) & serv_check, &serv_len); ex11

	/* ex11
	if (serv_check != serv_addr)
		printf("Sou o cliente 1\n");
		printf("o meu par e {IP:%s, porto:%d}\n")
	{
	else {
		printf("Sou o cliente 2\n");
		printf("O mey oar e {IP:%s, porto%d}\n", serv_check, );
		sendto(sockfd, (char*)& par_addr, sizeof(par_addr), 0, (struct sockaddr*) & par_addr, sizeof(par_addr);
	} }
	*/

	//response = ntohl(response);

	if(nbytes == SOCKET_ERROR){
		if(WSAGetLastError() != WSAETIMEDOUT)
			Abort("Erro enquanto aguarda pela resposta");
		else
			Abort("Timeout de recepcao");
	}

	printf("<CLI1>Mensagem recebida: %d\n", response); //ex10

	if (strcmp(inet_ntoa(serv_addr.sin_addr), argv[2]) == 0 && ntohs(serv_addr.sin_port) == atoi(argv[3])){
		printf("<CLI1>A mensagem veio do servidor.\n");
	}else{
		printf("<CLI1>A mensagem nao veio do servidor!\n");
	}
	
	/*========================= FECHA O SOCKET ===========================*/

	closesocket(sockfd);

	printf("\n");
	exit(EXIT_SUCCESS);
}

/*________________________________ Abort________________________________________
  Mostra uma mensagem de erro e o código associado ao ultimo erro com Winsocks. 
  Termina a aplicacao com "exit status" a 1 (constante EXIT_FAILURE)
________________________________________________________________________________*/

void Abort(char *msg)
{
	fprintf(stderr,"<CLI1>Erro fatal: <%s> (%d)\n",msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}
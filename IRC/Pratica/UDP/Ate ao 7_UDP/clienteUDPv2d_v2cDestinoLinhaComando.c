/*=========================== Cliente basico UDP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cuja localizacao e' igualmente
passada na linha de comando. 

Aguarda pela resposta (cadeia de carateres) e verifica a origem.

O protocolo usado e' o UDP.
==============================================================================*/

#include <stdio.h>
#include <winsock.h>

#define BUFFERSIZE     4096

void Abort(char *msg);

/*________________________________ main _______________________________________
*/

int main( int argc , char *argv[] )
{

	SOCKET sockfd;
	int iResult, msg_len, nbytes, opt; /*EXTRA opt*/
	int tam;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFFERSIZE];
	WSADATA wsaData;

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

	/*=============== ACTIVA POSSIBILIDADE DE ENVIO POR DIFUSAO ==============*//*EXTRAEXTRA*//*EXTRAEXTRA*/

	opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));

	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/

	memset( (char*)&serv_addr, 0 , sizeof(serv_addr) ); /*Coloca a zero todos os bytes*/
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]); /*IP no formato "dotted decimal" => 32 bits*/
	serv_addr.sin_port = htons(atoi(argv[3])); /*Host TO Network Short*/

	/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/

	msg_len = strlen(argv[1]);
	
	if(sendto( sockfd , argv[1] , msg_len , 0 , (struct sockaddr*)&serv_addr , sizeof(serv_addr) ) == SOCKET_ERROR)
		Abort("SO nao conseguiu aceitar o datagram");

	/* Descobre qual o porto que o SO atribuiu ao cliente */ /*EXTRAEXTRA*//*EXTRAEXTRA*/
	tam = sizeof(cli_addr);	
	if (getsockname(sockfd, (struct sockaddr *)&cli_addr, &tam) != SOCKET_ERROR)
		printf("O porto atribuido pelo SO e: %d\n", ntohs(cli_addr.sin_port));

	printf("<CLI1>Mensagem enviada ... a entrega nao e' confirmada.\n"); 


	/*====================== AGUARDA RESPOSTA ==========================*/

	tam = sizeof(serv_addr);
	nbytes = recvfrom(sockfd, buffer, sizeof(buffer),0,(struct sockaddr *)&serv_addr, &tam);

	if(nbytes == SOCKET_ERROR)
		Abort("Erro enquanto aguarda pela resposta");

	buffer[nbytes] = '\0';
	printf("<CLI1>Mensagem recebida: %s\n", buffer); 

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
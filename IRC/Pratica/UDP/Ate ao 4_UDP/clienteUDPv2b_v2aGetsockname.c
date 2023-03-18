/*=========================== Cliente basico UDP ===============================
Este cliente destina-se a enviar mensagens passadas na linha de comando, sob
a forma de um argumento, para um servidor especifico cuja locacao e' dada
pelas seguintes constantes: SERV_HOST_ADDR (endereco IP) e SERV_UDP_PORT (porto)

Mostra o porto local que foi automaticamente atribuido pelo sistema operativo.

Aguarda pela resposta (cadeia de carateres).

O protocolo usado e' o UDP.
==============================================================================*/

#include <stdio.h>
#include <winsock.h>


#define SERV_HOST_ADDR "10.65.132.252"
#define SERV_UDP_PORT  6000

#define BUFFERSIZE     4096

void Abort(char *msg);

/*______________________________ main _____________________________________
*/

int main(int argc, char *argv[])
{

	SOCKET sockfd;
	int iResult, msg_len, nbytes;

	int tam; /*EXTRA*/ /*EXTRA*/

	struct sockaddr_in serv_addr, cli_addr; /*EXTRA CLI_ADDR*/

	char buffer[BUFFERSIZE];
	WSADATA wsaData;

	/*========================= TESTA A SINTAXE =========================*/

	if (argc != 4) {
		fprintf(stderr, "Sintaxe: %s frase_a_enviar %s ip_destino %s porto_destino\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=============== INICIA OS WINSOCKS ==============*/

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*=============== CRIA SOCKET PARA ENVIO/RECEPCAO DE DATAGRAMAS ==============*/

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd == INVALID_SOCKET)
		Abort("Impossibilidade de criar socket");

	/*================= PREENCHE ENDERECO DO SERVIDOR ====================*/

	memset((char*)&serv_addr, 0, sizeof(serv_addr)); /*Coloca a zero todos os bytes*/
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]); /*IP no formato "dotted decimal" => 32 bits*/ /*EXTRA*//*muda para arg[]*/
	serv_addr.sin_port = htons(atoi(argv[3]); /*Host TO Netowork Short*/ /*EXTRA*//*muda para arg*/

/*====================== ENVIA MENSAGEM AO SERVIDOR ==================*/

	msg_len = strlen(argv[1]);

	if (sendto(sockfd, argv[1], msg_len, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Abort("SO nao conseguiu aceitar o datagram");

	printf("<CLI1>Mensagem enviada ... a entrega nao e' confirmada.\n");

	tam = sizeof(cli_addr); /*EXTRA*//*EXTRA*/
	if (getsockname(sockfd, (struct sockaddr *)&cli_addr, &tam) != SOCKET_ERROR) { /*EXTRA*//*EXTRA*/
		printf("<CLI1>Porto local automatico: %d\n", ntohs(cli_addr.sin_port));
	}

	/*====================== AGUARDA RESPOSTA ==========================*/

	tam = sizeof(serv_addr);
	nbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, &tam); /*DIFERENTE 2 ultimos parametros*/

	if (nbytes == SOCKET_ERROR)
		Abort("Erro enquanto aguarda pela resposta");

	buffer[nbytes] = '\0';
	printf("<CLI1>Mensagem recebida: %s\n", buffer);

	if (strcmp(inet_ntoa(serv_addr.sin_addr), SERV_HOST_ADDR) == 0 && ntohs(serv_addr.sin_port) == SERV_UDP_PORT) { /*EXTRA*//*EXTRA*/

		printf("<CLI1> mensagem veio do servidor.\n");

	}
	else
	{
		printf("<CLI1> a mensagem nao vio do servidor");
	}
	/*========================= FECHA O SOCKET ===========================*/

	closesocket(sockfd);

	printf("\n");
	exit(EXIT_SUCCESS);
}


/*______________________________ Abort________________________________________
Mostra uma mensagem de erro e o código associado ao ultimo erro com Winsocks.
Termina a aplicacao com "exit status" a 1 (constante EXIT_FAILURE)
______________________________________________________________________________*/

void Abort(char *msg)
{
	fprintf(stderr, "<CLI1>Erro fatal: <%s> (%d)\n", msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}
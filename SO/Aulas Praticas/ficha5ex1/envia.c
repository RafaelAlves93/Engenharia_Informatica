#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SERVER_FIFO "teste"

typedef struct{
    pid_t pid;
    char mensagem[100];
} dataMSG;


int main(){
    //char res[100]; //SEM A ESTRUTURA DE DADOS!
	dataMSG res;
	strcpy(res, "doi a cabeca");

    	int fde = open(SERVER_FIFO,O_WRONLY);
	if (fde == -1){
	printf("Erro a abrir o servidor\n");
    	return 1;
	}

    	int size = write (fde,&res,sizeof(res));
    	close(fde);
}

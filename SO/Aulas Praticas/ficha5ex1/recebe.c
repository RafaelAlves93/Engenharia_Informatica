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
    if(mkfifo(SERVER_FIFO,0666)==-1){
        if(errno == EEXIST){
        printf("Fifo ja existe\n");
        }
    printf("Erro ao abrir o fifo\n");
    return 1;
    }
    int fde = open(SERVER_FIFO,O_RDONLY);
    if (fde == -1){
    printf("Erro ao abrir o servidor\n");
    return 1;}

    int size = read (fde, &res, sizeof(res));
    if (size > 0)
        printf("Mensagem - [%s] PID do cliente [%d]",res,mensagem,pid);
    close(fde);
    
    unlink(SERVER_FIFO); //apagar o FIFO
}
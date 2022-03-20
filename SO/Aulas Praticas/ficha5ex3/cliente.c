#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#define SERVER_FIFO "SERVIDOR"
#define CLIENT_FIFO "CLIENTE%d" //CLIENTE123

char CLIENT_FIFO_FINAL[100]; //CLIENTE123

//mensagem que recebe
//sprintf("CLIENT_FIFO_FINAL,CLIENT_FIFO,mensagemRecebida.pid);

typedef struct {
    pid_t pid;
    char operador;
    int num1;
    int num2;
} dataMSG;

//mensagem com a resposta
typedef struct{
    float res;
} dataRPL;

int main(){
    dataMSG mensagem;
    dataRPL resposta;
    mensagem.pid = getpid();
    int fd_envio,fd_resposta;
    sprintf(CLIENT_FIFO_FINAL,CLIENT_FIFO,getpid());
    if(mkfifo(CLIENT_FIFO_FINAL,0666)== -1){
        if(errno == EEXIST){
        printf("fifo ja existe");
        }
    printf("Erro abrir o fifo");
    return 1;
    }
    int fde = open(SERVER_FIFO,O_RDONLY);
    if (fde == -1){
    printf("erro abrir o servidor\n");
    return -1;
    }
    do{
    printf("Introduza o operador\n");
    fflush(stdin);
    scanf(" %c",&mensagem.operador);
    if(mensagem.operador == '.'){ //SE FOR .
        fd_envio = open(SERVER_FIFO,O_WRONLY);
        int size = write(fd_envio,&mensagem,sizeof(mensagem));
        close(fd_envio);
        unlink(CLIENT_FIFO_FINAL);
        exit(1);
    }else{
        printf("Introduza o numero 1\n");
        scanf("%d",&mensagem.num1);
        printf("Introduza o numero 2\n");
        scanf("%d",&mensagem.num2);
    }
    fd_envio = open(SERVER_FIFO,O_WRONLY);
    int size = write(fd_envio,&mensagem,sizeof(mensagem));
    close(fd_envio);
    //RECEBER O CALCULO
    fd_resposta = open(CLIENT_FIFO_FINAL,O_RDONLY);
    int size2 = read(fd_resposta,&resposta,sizeof(resposta));
    close(fd_resposta);
    printf("\nResultado do calculo - [%f]\n",resposta.res);
    }while(1);
}
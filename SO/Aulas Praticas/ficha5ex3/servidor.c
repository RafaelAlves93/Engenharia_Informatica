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

char CLIENTE_FIFO_FINAL[100]; //CLIENTE123

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

void handler_sigalrm(int s, siginfo_t *i, void *v){
    unlink(SERVER_FIFO);
    printf("\nAdeus\n");
    exit(1);
}

int main(){
    struct sigaction sa;
        sa.sa_sigaction=handler_sigalrm;
        sa.sa_flags = SA_RESTART | SA_SIGINFO; //NAO E NECESSARIO
    sigaction(SIGINT,&sa,NULL);
    dataMSG mensagemRecebida;
    dataRPL resposta;
    if(mkfifo(SERVER_FIFO,0666)== -1){
        if(errno == EEXIST){
        printf("fifo ja existe");
        }
    printf("Erro abrir o fifo");
    return 1;
    }
    int fde = open(SERVER_FIFO,O_RDONLY);
    if (fde == -1){
    printf("erro abrir o servidor");
    return -1;
    }
    int fdRecebe = open(SERVER_FIFO,O_RDONLY);
    if(fdRecebe==-1){
        printf("Erro");
        return -1;
    }
    do{
    int size = read(fdRecebe,&mensagemRecebida,sizeof(mensagemRecebida));
    if(size>0){
        if(mensagemRecebida.operador == '+')
        resposta.res = mensagemRecebida.num1 + mensagemRecebida.num2;
        else if(mensagemRecebida.operador == '.')
        kill(getpid(),SIGINT);
        //responder ao meu cliente...
        sprintf(CLIENTE_FIFO_FINAL,CLIENT_FIFO,mensagemRecebida.pid);
        int fdEnvio= open(CLIENTE_FIFO_FINAL,O_WRONLY);
        int size2 = write (fdEnvio,&resposta,sizeof(resposta));
        close(fdEnvio);
    }
    }while(1);
    unlink (SERVER_FIFO);
}
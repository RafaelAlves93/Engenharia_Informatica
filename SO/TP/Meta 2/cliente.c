#include "estruturas.h"

char pathCliente[20];
char pathMedico[20];
COMBALCAO cb;

void sair(int s);
void kickado(int s);

int main(int argc, char **argv) {
  char sin[50];
  char mensagem[100];
  int serv, cli, med, diag, fd, mpid;
  struct timeval tv;
  fd_set leitura;
  cb.pid=getpid();
  cb.estado=0;
  cb.novo=1;
  cb.tipo='c';

  if(argc <= 1){
    printf("Nao passou o nome como argumento (./cliente [nome])\n");
    exit(EXIT_FAILURE);
  }
  strcpy(cb.username,argv[1]);
  if(signal(SIGINT, sair) == SIG_ERR){
    perror("\nNao foi possivel configurar o sinal SIGINT");
    exit(EXIT_FAILURE);
  }

  if(signal(SIGUSR1, kickado) == SIG_ERR){
    perror("\nNao foi possivel configurar o sinal SIGUSR1");
    exit(EXIT_FAILURE);
  }


  sprintf(pathCliente, CLIENT_FIFO, cb.pid);
  if(mkfifo(pathCliente, 0777) == -1){
    perror("\nmkfifo do FIFO do cliente deu erro");
    exit(EXIT_FAILURE);
  }

  serv = open(SERV_FIFO, O_WRONLY);
  if(serv == -1){
    fprintf(stderr, "\nO servidor não está a correr\n");
    unlink(pathCliente);
    exit(EXIT_FAILURE);
  }
  cli = open(pathCliente, O_RDWR);
  if(cli == -1){
    perror("\nErro ao abrir o FIFO do cliente");
    close(serv);
    unlink(pathCliente);
    exit(EXIT_FAILURE);
  }

  write(serv,&cb,sizeof(cb));
  cb.novo=0;
  system("clear");
  printf("\nLigou-se ao balcao!\n");
  printf("\nIntroduza os sintomas: \n");

  fgets(sin,99,stdin);
  strcpy(cb.mensagem, sin);
  write(serv, &cb, sizeof(cb));

  diag = read(cli, &cb, sizeof(cb));
  if(diag == sizeof(cb)){
    printf("\nDiagnostico:%s %d\n", cb.especialidade, cb.prioridade);
    printf("Existem %d medico(s) com a sua especialidade atualmente no sistema ligados\n", cb.medDisp);
    printf("Encontra-se na posicao %d de espera\n", cb.pos );
  }
  else{
    printf("\nSem diagnostico");
    exit(EXIT_FAILURE);
  }
  close(serv);

  while(1){
    tv.tv_sec = 0;
    tv.tv_usec = 10;
    FD_ZERO(&leitura);
    FD_SET(0, &leitura);
    FD_SET(cli, &leitura);
    fd = select(cli+1, &leitura, NULL, NULL, &tv);

    if(cb.estado == 0){  //fora de consulta

      if(FD_ISSET(0, &leitura)){
        fgets(cb.mensagem,99,stdin);
        if(strcmp(cb.mensagem,"adeus\n") == 0)
        sair(1);
        printf("A aguardar por medico se quiser sair escreva 'adeus'\n");
      }
      //entrar em consulta
      if(FD_ISSET(cli, &leitura)){
        read(cli, &mpid, sizeof(mpid));
        printf("Conexao entre medpid:%d ", mpid);
        printf("e clipid:%d\n", cb.pid);
        sprintf(pathMedico, MEDIC_FIFO, mpid);
        med = open(pathMedico, O_WRONLY);
        cb.estado = 1;
      }
    }
    else{  //em consulta

      if(FD_ISSET(0, &leitura)){
        fgets(mensagem,99,stdin);
        write(med, &mensagem, sizeof(mensagem));
        if(strcmp(mensagem,"adeus\n") == 0){
          cb.estado=0;
          close(med);
          sair(1);
        }
        //printf("->A mensagem do cliente: %s", ctm.mensagem);
      }

      if(FD_ISSET(cli, &leitura)){
        read(cli, &mensagem, sizeof(mensagem));
        if(strcmp(mensagem,"adeus\n") == 0)
         sair(1);
        printf("Medico: %s",mensagem);
      }

    }
  }
  close(med);
  close(cli);
  unlink(pathCliente);
  return 0;
}

  void sair(int s){
    system("clear");
    printf("O cliente foi fechado!\n");

    if(cb.estado == 1){
      char mensagem[10];
      strcpy(mensagem,"adeus\n");
      int med = open(pathMedico, O_WRONLY);
      write(med,&mensagem,sizeof(mensagem));
      close(med);
    }
    int serv = open(SERV_FIFO, O_WRONLY);
    cb.estado=-1;
    write(serv, &cb, sizeof(cb));
    close(serv);
    unlink(pathCliente);
    exit(EXIT_SUCCESS);
  }

  void kickado(int s){
    system("clear");
    printf("Foi desconectado do servidor\n");
    unlink(pathCliente);
    exit(EXIT_SUCCESS);

  }

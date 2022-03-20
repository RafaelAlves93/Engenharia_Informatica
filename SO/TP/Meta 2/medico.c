#include "estruturas.h"

char pathCliente[20];
char pathMedico[20];
COMBALCAO cb;
pthread_mutex_t lock;
void sair(int s);
void kickado(int s);

void* envPing(){
  int vida, pid = getpid();
  vida = open(VIDA_MEDICO, O_WRONLY);
  while (1) {
    sleep(1);
    write(vida, &pid, sizeof(pid));
    sleep(19);
  }

  close(vida);
  pthread_exit(NULL);
}
int main(int argc, char **argv) {
  char sin[50];
  char mensagem[100];
  int serv, cli, med, diag, fd, cpid;
  struct timeval tv;
  fd_set leitura;
  cb.pid=getpid();
  cb.estado=0;
  cb.novo=1;
  cb.tipo='m';
  pthread_t medicoPing;

  if(pthread_create(&medicoPing, NULL, &envPing, NULL) != 0)
    printf("Criacao da thread para o medico deu erro\n");

  if(argc <= 2){
    printf("Nao passou o nome como argumento (./medico [nome] [especialidade])\n");
    exit(EXIT_FAILURE);
  }
  strcpy(cb.username,argv[1]);
  strcpy(cb.especialidade,argv[2]);
  if(signal(SIGINT, sair) == SIG_ERR){
    perror("\nNao foi possivel configurar o sinal SIGINT");
    exit(EXIT_FAILURE);
  }

  if(signal(SIGUSR1, kickado) == SIG_ERR){
    perror("\nNao foi possivel configurar o sinal SIGUSR1");
    exit(EXIT_FAILURE);
  }


  sprintf(pathMedico, MEDIC_FIFO, cb.pid);
  if(mkfifo(pathMedico, 0777) == -1){
    perror("\nmkfifo do FIFO do medico deu erro");
    exit(EXIT_FAILURE);
  }

  serv = open(SERV_FIFO, O_WRONLY);
  if(serv == -1){
    fprintf(stderr, "\nO servidor não está a correr\n");
    unlink(pathMedico);
    exit(EXIT_FAILURE);
  }
  med = open(pathMedico, O_RDWR);
  if(med == -1){
    perror("\nErro ao abrir o FIFO do medico");
    close(serv);
    unlink(pathMedico);
    exit(EXIT_FAILURE);
  }

  write(serv,&cb,sizeof(cb));
  cb.novo=0;
  close(serv);

  system("clear");
  printf("\nLigou-se ao balcao!");
  printf("\nAguarde atribuição\n");

  while(1){
    tv.tv_sec = 0;
    tv.tv_usec = 10;
    FD_ZERO(&leitura);
    FD_SET(0, &leitura);
    FD_SET(med, &leitura);
    fd = select(med+1, &leitura, NULL, NULL, &tv);

    if(cb.estado == 0){ // fora de consulta

      if(FD_ISSET(0, &leitura)){
        fgets(cb.mensagem,99,stdin);
        if(strcmp(cb.mensagem,"sair\n") == 0)
        sair(1);
        printf("A espera de atribuição se quiser sair escreva 'sair'\n");
      }
      //entrar em consulta
      if(FD_ISSET(med, &leitura)){
        read(med, &cpid, sizeof(cpid));
        printf("Conexao entre medpid:%d ", cb.pid);
        printf("e clipid:%d\n", cpid);
        sprintf(pathCliente, CLIENT_FIFO, cpid);
        cli = open(pathCliente, O_WRONLY);
        cb.estado = 1;
      }
    }
    else{ //  em consulta
      if(FD_ISSET(0, &leitura)){
        fgets(mensagem,99,stdin);
        if(strcmp(mensagem,"sair\n") == 0){
           write(cli, "adeus\n", sizeof("adeus\n"));
           sair(1);
        }
        write(cli, &mensagem, sizeof(mensagem));
        if(strcmp(mensagem,"adeus\n") == 0){
          cb.estado = 0;
          //cb.pid = 0;
          serv = open(SERV_FIFO, O_WRONLY);
          write(serv, &cb, sizeof(cb));
          close(serv);
          printf("\nTerminou a consulta!");
          printf("\nAguarde atribuição\n");
        }
      }

      if(FD_ISSET(med, &leitura)){
        read(med, &mensagem, sizeof(mensagem));
        printf("Utente: %s",mensagem);
        if(strcmp(mensagem,"adeus\n") == 0){
          cb.estado = 0;
          //cb.pid = 0;
          serv = open(SERV_FIFO, O_WRONLY);
          write(serv, &cb, sizeof(cb));
          close(serv);
          printf("\nTerminou a consulta!");
          printf("\nAguarde atribuição\n");
        }
      }

    }
  }
  pthread_join(medicoPing, NULL);
  close(med);
  close(cli);
  unlink(pathCliente);
  return 0;
}

  void sair(int s){
    system("clear");
    printf("O medico foi fechado!\n");
    if(cb.estado == 1){
      char mensagem[10];
      strcpy(mensagem,"adeus\n");
      write(*pathCliente,&mensagem,sizeof(mensagem));
      close(*pathCliente);
    }
    unlink(pathMedico);
    exit(EXIT_SUCCESS);
  }

  void kickado(int s){
    system("clear");
    printf("Foi desconectado do servidor\n");
    unlink(pathMedico);
    exit(EXIT_SUCCESS);

  }

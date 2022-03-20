//
// Autores: Rafael Alves | Ricardo Fernandes
//

#include "estruturas.h"

ESTRUTURABALCAO estruturas;
ESTRUTURACLIENTES eCli;
ESTRUTURAMEDICOS eMD;
struct EstruturaClientes* headC = NULL;
struct EstruturaMedicos* headM = NULL;

int vambiente();
int vfich();
void classi(COMBALCAO* pcb);
void sair(int s);
int loginCliente(COMBALCAO* pcb);
int loginMedico(COMBALCAO* pcb);
void removerUtente(int pid);
void removerMedico(int pid);
void mostrarUtentes();
void mostrartMedicos();
void consultaMC();
void fecharTudo();
void listasEspera();
int posicaoUtente(int pid);
int medicosDisp(char * especialidade);
int contarUtentes();
int contarMedicos();
int contarUtEsp(char * especialidade);
struct EstruturaClientes* encontrarUt(int pid);
struct EstruturaMedicos* encontrarEsp(int pid);

int medp, clip, serv;
COMBALCAO cb;
pthread_mutex_t lock;

void* receberPing(){
  time_t ping;
  time_t atual;
  double seconds;

  while(1){
    sleep(3);
    pthread_mutex_lock(&lock);
    struct EstruturaMedicos* ind = headM;
    time(&atual);
    while (ind != NULL) {
      if(ind->ping != 0 && difftime(atual, ind->ping) > 20){
        printf("\nO especialista(%d) levou timeout.\n", ind->pid);
        ind->estado = 0;
        removerMedico(ind->pid);
      }
      ind= ind->prox;
    }
    pthread_mutex_unlock(&lock);
  }

  pthread_exit(NULL);
}


int main(int argc, char **argv) {
  int v,pid,fd,vida,maxfd,cli,rd,n=30;
  time_t ping;
  struct timeval tv;
  fd_set leitura;
  char pathCliente[20];
  char pathMedico[20];
  char input[50];
  char *token[20];
  estruturas.n_listaespera = 5;

  pthread_t medicoPing;

  pthread_mutex_init(&lock, NULL);

  if(pthread_create(&medicoPing, NULL, &receberPing, NULL) != 0)
    printf("Criacao da thread para o medico deu erro\n");


  if(signal(SIGINT, sair) == SIG_ERR){
    perror("\nNao foi possivel configurar o sinal SIGINT");
    exit(EXIT_FAILURE);
  }
  v = mkfifo(SERV_FIFO, 0777);
  if(v == -1){
    perror("\nmkfifo do FIFO do balcao deu erro");
    exit(EXIT_FAILURE);
  }
  v = mkfifo(VIDA_MEDICO, 0777);
  if(v == -1){
    perror("\nmkfifo do FIFO do sinal de vida do medico deu erro");
    exit(EXIT_FAILURE);
  }
  vida = open(VIDA_MEDICO, O_RDWR);
  if(serv == -1){
    perror("\nErro ao abrir o FIFO de vida do medico ");
    exit(EXIT_FAILURE);
  }
  serv = open(SERV_FIFO, O_RDWR);
  if(serv == -1){
    perror("\nErro ao abrir o FIFO do balcao");
    exit(EXIT_FAILURE);
  }

  if(vfich("classificador") == 1){
    printf("O ficheiro classificador não existe!\n");
    exit(1);
  }
  vambiente();
  system("clear");
  printf("Balcão em execução!%d\n", getpid());
  while(1){
    FD_ZERO(&leitura);
    FD_SET(0, &leitura);
    FD_SET(serv, &leitura);
    FD_SET(vida, &leitura);
    tv.tv_sec = n;
    tv.tv_usec = 0;

    maxfd = serv > vida ? serv : vida;
    fd = select(maxfd+1, &leitura, NULL, NULL, &tv);


    if(fd == 0){
      listasEspera();
      fflush(stdout);
      continue;
    }
    if(fd == -1){
      perror("\nErro no Select");
      close(serv);
      unlink(SERV_FIFO);
      return EXIT_FAILURE;
    }
    if(FD_ISSET(0, &leitura)){                      //alterar
      fgets(input,40 ,stdin);
      input[strlen(input)-1]='\0';
      token[0]=strtok(input," ");
      int k = 0;
      do{
        k++;
        token[k]=strtok(NULL," ");
      }while(token[k]!=NULL);

      if(strcmp(token[0],"utentes") == 0) {
        mostrarUtentes();
      }
      else if(strcmp(token[0],"especialistas") == 0) {
        mostrartMedicos();
      }
      else if(strcmp(token[0],"delut") == 0) {
        if(isdigit(*token[1]) != 0){
          int vint = atoi(token[1]);
          printf("\nO utente(%d) irá ser removido da lista.\n", vint);
          removerUtente(vint);
        }
        else
        printf("O pid do utente a remover não é um número.\n");

      }
      else if(strcmp(token[0],"delesp") == 0) {
        if(isdigit(*token[1]) != 0){
          int vint = atoi(token[1]);
          printf("\nO especialista(%d) irá ser removido do sistema.\n", vint);
          removerMedico(vint);
        }
        else
        printf("O pid do especialista a remover não é um número.\n");
      }
      else if(strcmp(token[0],"freq") == 0) {
        if(isdigit(*token[1]) != 0){
          int vint = atoi(token[1]);
          if (n<0)
          printf("Número para frequencia tem que ser positivo\n");
          else{
            n=vint;
            printf("Frequencia é agora %d\n", n);
          }
        }
        else
        printf("O valor inserido para a frequencia não é um número\n");
      }
      else if(strcmp(token[0],"encerra") == 0) {
        sair(1);
      }
      else
      printf("Comando Desconhecido!\n");
    }
    if(FD_ISSET(vida, &leitura)){
      read(vida, &pid, sizeof(pid));
      struct EstruturaMedicos* pingado = encontrarEsp(pid);
      pingado->ping = time(&ping);
    }

    if(FD_ISSET(serv, &leitura)){
      rd = read(serv, &cb, sizeof(cb));
      if(rd == -1)
      fprintf(stderr, "\nErro de leitura.");

      if(cb.tipo == 'c'){
        sprintf(pathCliente, CLIENT_FIFO, cb.pid );
        if(cb.novo == 1){
          printf("\nLigou-se um novo cliente de nome:%s pid(%d)\n", cb.username,cb.pid);
        }
        else if(cb.estado == -1){
          printf("\nO utente(%d) foi desconectado.\n", cb.pid);
          encontrarUt(cb.pid)->estado=-1;
          removerUtente(cb.pid);
        }
        else{
          classi(&cb);
          cli=open(pathCliente, O_WRONLY);
          cb.pos=posicaoUtente(cb.pid);
          cb.medDisp=medicosDisp(cb.especialidade);
          write(cli, &cb, sizeof(cb));
          printf("\nO utente %d recebeu o seguinte diagnostico:%s %d\n",cb.pid, cb.especialidade, cb.prioridade);
          if(loginCliente(&cb)==-1){
            printf("Lista de espera cheia para %s, utente(%d) não entrou!\n",cb.especialidade, cb.pid);
            kill(cb.pid,SIGUSR1);
          }
          else
          printf("Utente(%d) adicionado a lista de espera\n",cb.pid);
          close(cli);
        }
      }
      else if(cb.tipo == 'm'){
        sprintf(pathMedico, MEDIC_FIFO, cb.pid);
        if(cb.novo == 1){
          printf("\nLigou-se um novo especialista de nome:%s pid(%d) com especialidade em %s\n", cb.username,cb.pid, cb.especialidade);
          if(loginMedico(&cb) == -1){
            printf("Número maximo de médicos atingido, medico(%d) não entrou!\n", cb.pid);
            kill(cb.pid,SIGUSR1);
          }
          else
          printf("Médico(%d) adicionado ao sistema\n", cb.pid);
        }
        else if(cb.estado == -1){
          printf("\nO especialista(%d) foi desconectado.\n", cb.pid);
          removerMedico(cb.pid);
        }
        else{
          printf("A consulta entre especialista(%d) e utente(%d) terminou\n",cb.pid, encontrarEsp(cb.pid)->cpid );
          printf("\nO especialista %s com especialidade em %s está novamente desponível\n", cb.username, cb.especialidade);
          encontrarEsp(cb.pid)->estado=0;
        }
      }
      else
      printf("\nUtilizador com o pid:%d não possui um tipo\n",cb.pid);

    }
    consultaMC();
  }
  sair(1);
}

int contarUtEsp(char * especialidade){
  struct EstruturaClientes* iCli = headC;
  int i=0;
  while (iCli != NULL) {
    if(strcmp(iCli->especialidade,especialidade) == 0 && iCli->estado == 0)
    i++;
    iCli = iCli->prox;
  }
  return i;
}

int contarMedicos(){
  struct EstruturaMedicos* iMed = headM;
  int i = 0;
  while (iMed != NULL) {
    i++;
    iMed= iMed->prox;
  }
  return i;
}

int contarUtentes(){
  struct EstruturaClientes* iCli = headC;
  int i = 0;
  while (iCli != NULL) {
    i++;
    iCli= iCli->prox;
  }
  return i;
}

int posicaoUtente(int pid){
  struct EstruturaClientes* iCli = headC;
  struct EstruturaClientes* atual = encontrarUt(pid);
  int pos = 0;
  char especialidade[50];
  while (iCli != NULL) {
    if(strcmp(atual->especialidade, iCli->especialidade) == 0 && iCli->prioridade >= atual->prioridade){
      pos++;
    }
    iCli = iCli -> prox;
  }
  return pos;
}

int medicosDisp(char * especialidade){
  struct EstruturaMedicos* iMed = headM;
  int total = 0;
  while( iMed != NULL){
    if(strcmp(especialidade, iMed->especialidade) == 0 )
    total++;
    iMed = iMed -> prox;
  }
  return total;
}

void listasEspera(){
  struct EstruturaClientes* iCli = headC;
  int oft = 0, neu = 0, est = 0, ort = 0, ger = 0;
  while (iCli != NULL) {
    if(strcmp(iCli->especialidade,"oftalmologia") == 0 && iCli->estado == 0)
    oft++;
    if(strcmp(iCli->especialidade,"neurologia") == 0 && iCli->estado == 0)
    neu++;
    if(strcmp(iCli->especialidade,"estomatologia") == 0 && iCli->estado == 0)
    est++;
    if(strcmp(iCli->especialidade,"ortopedia") == 0 && iCli->estado == 0)
    ort++;
    if(strcmp(iCli->especialidade,"geral") == 0 && iCli->estado == 0)
    ger++;
    iCli = iCli->prox;
  }
  printf("Lista de espera\n");
  printf("Oftalmologia: %d utente(s)\n", oft);
  printf("Neurologia: %d utente(s)\n", neu);
  printf("Estomatologia: %d utente(s)\n", est);
  printf("Ortopedia: %d utente(s)\n", ort);
  printf("Geral: %d utente(s)\n", ger);

}

void fecharTudo(){
  struct EstruturaClientes* iCli = headC;
  struct EstruturaMedicos* iMed = headM;
  while (iCli != NULL) {
    kill(iCli->pid,SIGUSR1);
    iCli=iCli->prox;
  }
  while (iMed != NULL) {
    kill(iMed->pid,SIGUSR1);
    iMed=iMed->prox;
  }
}

void removerMedico(int pid){
  struct EstruturaMedicos* ant = NULL;
  struct EstruturaMedicos* iMed = headM;
  while (iMed != NULL && iMed->pid != pid){
    ant = iMed;
    iMed = iMed->prox;
  }
  if (iMed == NULL){
    printf("Medico(%d) nao existe!\n", pid);
  }
  else if(iMed->estado == 1){
    printf("Medico(%d) esta em consulta!\n", pid);
  }
  else if (ant == NULL){
    headM = iMed->prox;
  }
  else{
    ant->prox = iMed->prox;
  }
  if( iMed != NULL){
      free(iMed);
      if (cb.estado =! -1)
      kill(iMed->pid, SIGUSR1);
  }

}

void removerUtente(int pid){
  struct EstruturaClientes* ant = NULL;
  struct EstruturaClientes* iCli = headC;
  while (iCli != NULL && iCli->pid != pid){
    ant = iCli;
    iCli = iCli->prox;
  }
  if (iCli == NULL){
      printf("Utente(%d) nao existe!\n", pid);
  }
  else if(iCli->estado == 1){
    printf("Utente(%d) esta em consulta!\n", pid);
    iCli = NULL;
  }
  else if(ant == NULL){
    headC = iCli->prox;
  }
  else{
    ant->prox = iCli->prox;
  }
  if( iCli != NULL){
    free(iCli);
    if (cb.estado =! -1)
    kill(iCli->pid, SIGUSR1);
  }
}

struct EstruturaMedicos* encontrarEsp(int pid){
  struct EstruturaMedicos* iMed = headM;
  while (iMed != NULL && iMed->pid != pid){
    iMed = iMed->prox;
  }
  if(iMed == NULL)
    return headM;
  return iMed;

}

struct EstruturaClientes* encontrarUt(int pid){
  struct EstruturaClientes* iCli = headC;
  while (iCli != NULL && iCli->pid != pid){
    iCli = iCli->prox;
  }
  if(iCli == NULL)
    return headC;
  return iCli;
}

void consultaMC(){
  struct EstruturaClientes* iCli = headC;
  struct EstruturaMedicos* iMed = headM;
  char pathCliente[20];
  char pathMedico[20];
  int med, cli, pid;
  while(iMed != NULL){
    if(iMed->estado == 0){
      while(iCli != NULL){
        if(iCli->estado == 0 && (strcmp(iCli->especialidade, iMed->especialidade)) == 0 ){
          sprintf(pathMedico, MEDIC_FIFO, iMed->pid);
          med = open(pathMedico, O_WRONLY);
          pid = iCli->pid;
          write(med, &pid, sizeof(pid));
          iCli->mpid = iMed->pid;
          close(med);
          sprintf(pathCliente, CLIENT_FIFO, iCli->pid);
          cli = open(pathCliente, O_WRONLY);
          pid = iMed->pid;
          write(cli, &pid, sizeof(pid));
          iMed->cpid = iCli->pid;
          close(cli);
          iMed->estado=1;
          iCli->estado=1;
          printf("Conexao estabelecida entre especialista(%d) e utente(%d)\n", iMed->pid, iCli->pid);
          break;
        }
        iCli = iCli->prox;
      }
    }
    iMed = iMed->prox;
  }
}

int loginCliente(COMBALCAO* pcb){
  struct EstruturaClientes* novo = NULL;
  struct EstruturaClientes* ant = NULL;
  struct EstruturaClientes* iCli = headC;
  if (contarUtentes() == estruturas.n_clientes || contarUtEsp(pcb->especialidade) >= estruturas.n_listaespera)
      return -1;
  else{
    novo = malloc(sizeof(*pcb));
    while(iCli != NULL && pcb->prioridade >= iCli->prioridade){
      ant = iCli;
      iCli = iCli->prox;
    }
    if (ant == NULL){
      novo->prox = headC;
      headC =novo;
    }
    else{
      ant->prox = novo;
      novo->prox = iCli;
    }
    strcpy(novo->username, pcb->username);
    strcpy(novo->especialidade, pcb->especialidade);
    novo->prioridade=pcb->prioridade;
    novo->pid = pcb->pid;
    novo->estado = 0;
    return 0;
  }
}

int loginMedico(COMBALCAO* pcb){
  struct EstruturaMedicos* novo = NULL;
  if (contarMedicos() == estruturas.n_medicos){
      return -1;
  }
  else{
    novo = malloc(sizeof(*pcb));
    strcpy(novo->username, pcb->username);
    strcpy(novo->especialidade, pcb->especialidade);
    novo->pid = pcb->pid;
    novo->prox = headM;
    novo->estado = 0;
    novo->ping = 0;
    headM = novo;
    return 0;
  }
}

void mostrarUtentes(){
  struct EstruturaClientes* iCli = headC;
  printf("\nUtente\t Especialidade\t Prio\t Estado\t Especialista\n");
  while (iCli != NULL) {
    printf("%d\t %s\t %d\t", iCli->pid, iCli->especialidade, iCli->prioridade);
    if(iCli->estado==0)
    printf("Em espera\t Nenhum\n");
    else
    printf("Em consulta\t %d\n", iCli->mpid);
    iCli = iCli->prox;
  }
}

void mostrartMedicos(){
  struct EstruturaMedicos* iMed = headM;
  printf("Especialista\t Especialidade\t Estado\t Utente\n");
  while( iMed != NULL){
    printf("%d\t %s\t", iMed->pid, iMed->especialidade);
    if(iMed->estado==0)
    printf("Em espera\t Nenhum\n");
    else
    printf("Em consulta\t %d\n", iMed->cpid);
    iMed = iMed->prox;
  }
}

//sair
void sair(int s){
  system("clear");
  fecharTudo();
  printf("O balcao foi fechado!\n");
  unlink(SERV_FIFO);
  unlink(VIDA_MEDICO);
  exit(EXIT_SUCCESS);
}

//classificador
void classi(COMBALCAO* pcb){

  int pid,prio,fd_in[2], fd_out[2];
  char classif[20], diagnostico[20], input[20];
  pipe(fd_in);
  pipe(fd_out);

  pid = fork();
  if(pid > 0){ //pai
    close(fd_in[0]); //fecha extremidade de leitura do pipe
    close(fd_out[1]); //fecha extremidade de escrita do pipe
    strcpy(input,pcb->mensagem);

    write(fd_in[1],input, strlen(input));
    read(fd_out[0], &classif, sizeof(classif) - 1);		//le o que foi enviado pelo classificador
    sscanf(classif,"%s %d",diagnostico,&prio);
    strcpy(pcb->especialidade,diagnostico);
    pcb->prioridade=prio;

  }

  else if(pid == 0){ //filho

    //filho que le
    close(STDIN_FILENO);	//liberta posicao 0 (stdin)
    dup(fd_in[0]);		//dupicla extremidade de leitura do pipe para pos 0
    close(fd_in[0]);	//fecha extremidade de leitura porque ja foi duplicada
    close(fd_in[1]);	//fecha extremidade de escrita do pipe

    //filho que escreve
    close(STDOUT_FILENO);	//liberta posicao 1 (stdout)
    dup(fd_out[1]);		//duplica extremidade de escrita do pipe para pos 1
    close(fd_out[0]);	//fecha extremidade de leitura do pipe
    close(fd_out[1]);	//fecha extremidade de escrita porque ja foi duplicada
    execl("./classificador", "classificador", NULL);
  }
}

//verificacao de leitura das variaveis de ambiente
int vambiente(){

  if(getenv("MAXMEDICOS") != NULL && getenv("MAXCLIENTES") != NULL){
    estruturas.n_medicos = atoi(getenv("MAXMEDICOS"));
    estruturas.n_clientes = atoi(getenv("MAXCLIENTES"));
    return 0;
  }
  else if (getenv("MAXMEDICOS") == NULL && getenv("MAXCLIENTES") == NULL)
  printf("Nao existem variaveis de ambiente criadas\n");
  else if (getenv("MAXMEDICOS") == NULL)
  printf("Variavel de ambiente MAXMEDICOS nao existe\n");
  else
  printf("Variavel de ambiente MAXCLIENTES nao existe\n");
  unlink(SERV_FIFO);
  unlink(VIDA_MEDICO);
  exit(EXIT_SUCCESS);
}

//verificacao de existencia de ficheiro
int vfich(const char *nome){
  FILE *ficheiro;
  if ((ficheiro = fopen(nome, "r"))){
    fclose(ficheiro);
    return 0;
  }
  return 1;
}

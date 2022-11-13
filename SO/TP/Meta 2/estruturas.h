//
// Autores: Rafael Alves | Ricardo Fernandes
//

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
 #include <fcntl.h>
 #include <ctype.h>
 #include <sys/select.h>
 #include <time.h>
 #include <signal.h>
 #include <pthread.h>
#define SERV_FIFO "fifo/server"
#define VIDA_MEDICO "fifo/vida"
#define CLIENT_FIFO "fifo/cliente_%d"
#define MEDIC_FIFO "fifo/medico_%d"

typedef struct EstruturaBalcao{
	int n_especialidades;
	int n_clientes;
	int n_medicos;
	int n_listaespera;
}ESTRUTURABALCAO;

typedef struct EstruturaClientes{
	int pid;
	char username [20];
	char sintomas[50];
  int estado;
  int prioridade;
  char especialidade[20];
  int mpid;
  struct EstruturaClientes* prox;
}ESTRUTURACLIENTES;

typedef struct EstruturaMedicos{
	int pid;
	char username[20];
  int estado;
  int prioridade;
  char especialidade[20];
  int cpid;
  time_t ping;
  struct EstruturaMedicos* prox;
}ESTRUTURAMEDICOS;

typedef struct COMBalcao{
  char username[20];
  char mensagem[50];
  int estado;
  int pos;
  int medDisp;
  int pid;
  char especialidade[20];
  int prioridade;
  int novo;
  char tipo;
}COMBALCAO;
#endif //ESTRUTURAS_H

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

typedef struct{
	int n_especialidades;
	int n_clientes;
	int n_medicos;
	int n_listaespera;
} EstruturaBalcao;

typedef struct{
	int id_clientes;
	char username [20];
	char sintomas[20];
} EstruturaClientes;

typedef struct{
	int id_medicos;
	char username [20];
	char especialidades [20];
} EstruturaMedicos;

#endif //ESTRUTURAS_H

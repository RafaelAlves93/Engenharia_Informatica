#ifndef FUNCS_H
#define FUNCS_H

//structs

/*
typedef struct nomecompleto nomeabreviado;
struct nomecompleto{
    tipo nome;
    tipo[x] nome;
    estrutura nome;
}; 
*/


//functions

float return_file_average(char* filename);

int* criaVetor(char *nomeFich, int *tam);

void print_file(char* filename);

void save_below_and_above_average(char* filename,char* below,char* above);

#endif /* FUNCS_H */
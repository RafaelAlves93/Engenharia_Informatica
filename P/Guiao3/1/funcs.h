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

typedef struct paragem paragem;
struct paragem{
    char nome[50];
    int minutos;
}; 

//functions

void printFile(char* nome);

int duracao(char* nome_ficheiro,char* origem,char* destino);

#endif /* FUNCS_H */
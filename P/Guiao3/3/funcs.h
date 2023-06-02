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

typedef struct cliente cliente;
struct cliente{ 
    char nome[200]; 
    char morada[200]; 
    int conta; 
    int montante; 
}; 



//functions

void save_structs(char *filename,cliente *clist,int len);

void print_from_file(char *filename);

void print_client_with_highest_amount(char *filename);

#endif /* FUNCS_H */
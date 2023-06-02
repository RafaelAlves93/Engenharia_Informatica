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

void save_struct_to_bin(char *filename,cliente *clist,int total);

void print_bin_to_stdout(char *filename);

void print_file_size_and_entrynun(char *filename);

void print_bin_to_stdout_inverse(char *filename);

int transfere(char *filename, char *or, char *dest, int amount);

int remove_entry(char *filename,char *name);

int add_entry(char *filename,cliente novo);

int join_bin_files(char *filename1,char *filename2,char *newfile);

#endif /* FUNCS_H */
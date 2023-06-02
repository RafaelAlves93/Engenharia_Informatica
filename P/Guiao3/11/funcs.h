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

typedef struct date date;
struct date{
    int dd;
    int mm;
}; 


//functions

char* int_to_month(int mm);

int month_to_days(int mm);

void date_to_temp_bin(date date,char *filename);

void date_to_temp_txt(date date,char *filename);

#endif /* FUNCS_H */
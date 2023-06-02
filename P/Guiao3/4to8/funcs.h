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

void save_strs_to_text_file(char *filename,char *str1,char *str2,char *str3,char *str4);

void copy_txt_file(char *original_name,char *copy_name);

void show_line_from_txtfile(char *filename, int lineno);

void print_most_common_vowel(char *filename);


#endif /* FUNCS_H */
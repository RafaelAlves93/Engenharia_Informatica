// RAFAEL FILIPE MARTINS ALVES - 2014013189

#ifndef TP_2223_LINHA_H
#define TP_2223_LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ctype.h"
#include "paragem.h"


typedef struct Linha_Paragem {
    struct Paragem paragem;
    struct Linha_Paragem* prox;
    struct Linha_Paragem* ant;
} Linha_Paragem;


typedef struct Linha {
    char nome[50];
    struct Linha_Paragem* head;
} Linha;


void regista_linha(int *num_paragens, int *num_linhas, Linha** linhas, Paragem** paragens);
void visualizar_linhas(int *num_linhas, Linha** linhas);
void saveBinParagens(int *num_paragens, Paragem** paragens);
void saveBinLinhas(int *num_linhas, Linha** linhas);
void loadBinParagens(int *num_paragens, Paragem** paragens);
void loadBinLinhas(int *num_linhas, Linha** linhas);
char* cortaespaco(char* str);
void leDadostxt(char* nomeFich, Linha** linhas, Paragem** paragens, int* num_paragens, int* num_linhas);
int verificaPLinha(int *num_linhas, Linha** linhas, char cod[5]);
void atualizar_linha(int* num_linhas, Linha** linhas, Paragem** paragens, int* num_paragens);
void removeParagem(Linha* linha);
void adicionaparagens(Paragem** paragens, Linha* linhas,int *num_paragens);
void calcPercurso(Paragem* inicial, Paragem* final, int* num_linhas, Linha** linhas);
void imprimeDireto(Linha_Paragem* paragem, char* paragemFinal, Linha* linhaI, int inicio);
void imprimeSalto(int inicio,int final, Linha* linhaI, Linha* linhaF,char* paragemInicial,char* paragemFinal,char* paragemInter);
void freeLinhaParagem(Linha_Paragem* linhaParagem);
void freeLinha(Linha** linhas);

#endif //TP_2223_LINHA_H

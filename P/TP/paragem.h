// RAFAEL FILIPE MARTINS ALVES - 2014013189

#ifndef TP_2223_PARAGEM_H
#define TP_2223_PARAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Paragem {
    char nome[50];
    char codigo[5];
} Paragem;


int printaTitulos(char* nomeF);
void registar_paragem(int *num_paragens, Paragem** paragens);
void eliminar_paragem(int *num_paragens, Paragem** paragens, char codigo[5]);
void visualizar_paragens(int *num_paragens, Paragem** paragens);
void freeParagem(Paragem** paragens);

#endif //TP_2223_PARAGEM_H

//
// Created by rafaa on 25/11/2022.
//

#ifndef META1_RESERVA_H
#define META1_RESERVA_H

#include <vector>
#include <string>
#include <iostream>
#include "Animais.h"
#include "Alimentos.h"
using namespace std;

class Reserva {
    // Máxima dimensão reserva
    int linhas;
    int colunas;
    vector<Animais> animais;
    vector<Alimentos> alimentos;
    char areaVisivel [10][10]{};
    int xvisivel = 0, yvisivel= 0;
public:
    Reserva(int n_linhas, int n_colunas);
    vector<Animais> getanimais(){return animais;}
    int getlinhas() const{return linhas;}
    int getcolunas() const{return colunas;}
    int getxvisivel() const{return xvisivel;}
    int getyvisivel() const{return yvisivel;}
    void setarea(int x, int y){xvisivel=x;yvisivel=y;}
    void gerar();
    void atualizaReservaVisivel();
    void MostrarZonas();
    void verQuadrado(int l, int c);
};

#endif //META1_RESERVA_H

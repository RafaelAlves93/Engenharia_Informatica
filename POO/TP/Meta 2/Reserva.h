
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
    int maxLinhas;
    int maxColunas;
    int idunico{};
    vector<Animais> animais;
    vector<Alimentos> alimentos;
    char areaVisivel [10][10]{};
    int xvisivel = 0, yvisivel= 0;
    int saudeC = 20, saudeO = 30, saudeL = 25, saudeG = 20, saudeM = 40;
public:
    //Terminal &t = Terminal::instance();
    Reserva(int n_linhas, int n_colunas);
    vector<Animais> getanimais(){return animais;}
    int getlinhas() const{return maxLinhas;}
    int getcolunas() const{return maxColunas;}
    int getxvisivel() const{return xvisivel;}
    int getyvisivel() const{return yvisivel;}
    void setarea(int x, int y){xvisivel=x;yvisivel=y;}
    //void gerar();
    void atualizaReservaVisivel();
    void MostrarZonas();
    void verQuadrado(int l, int c);
    void gerarAnimais(const string& tipo, int linhas, int colunas);
    void gerarAlimentos(const string& tipo, int linhas, int colunas);
    void verInfo(int id);
    static int gerarRandom(int a, int b);
    bool verOcupa(int linha, int coluna);
    void listarReserva();
    void listarAreaVis();
    void killAnimalId(int id);
    void killAnimalPosicao(int linha, int coluna);
    void removAlimPosicao(int linha, int coluna);
    void removAlimID(int id);
    void empty(int linha, int coluna);
    void feedDirect(int linha, int coluna, int nutri, int toxi);
    void feedDirectId(int id, int nutri, int toxi);
    void Constantes(string tipo, string saude);
    void next();
    void movimentarRand(vector<Animais>::iterator i, int mov);
    int aproximarAli(vector<Animais>::iterator i, string cheiro, int mov);
    int fugirAni(vector<Animais>::iterator i, int peso);
    int persegueAni(vector<Animais>::iterator i);
    int persegueLobo(vector<Animais>::iterator i);
};

#endif //META1_RESERVA_H

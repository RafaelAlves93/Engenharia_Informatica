//
// Created by rafaa on 25/11/2022.
//

#ifndef META1_ANIMAIS_H
#define META1_ANIMAIS_H

#include <string>
#include <vector>
#include "Alimentos.h"
using namespace std;

class Animais {
    int id=1;
    char especie;
    int linha;
    int coluna;
    bool vivo=true;
    int idade=10;
    int saude=30;
    int movimInst=1;
    int aprox=4;
    vector<Alimentos*> historico;
public:
    Animais(char especie_n, int linha_n, int coluna_n);
    char getespecie() const{return especie;}
    int getlinha() const{return linha;}
    int getcoluna() const{return coluna;}
    bool getvivo() const{return vivo;}
    int getidade() const{return idade;}
    int getsaude() const{return saude;}
    int getmovimInst() const{return movimInst;}
    int getaprox() const{return aprox;}
    void imprimeInfoAnimais() const;
};

#endif //META1_ANIMAIS_H

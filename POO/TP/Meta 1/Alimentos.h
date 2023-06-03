//
// Created by rafaa on 25/11/2022.
//

#ifndef META1_ALIMENTOS_H
#define META1_ALIMENTOS_H

#include <string>
#include <iostream>
using namespace std;

class Alimentos {
    int id=1;
    char tipo;
    int linha;
    int coluna;
    bool consumido=false;
    int tempo=10;
    int valorNut=10;
    int valorTox=0;
    string cheiro="carne";
public:
    Alimentos(char tipo_n, int linha_n, int coluna_n);
    int getid() const{return id;}
    char gettipo() const{return tipo;}
    int getlinha() const{return linha;}
    int getcoluna() const{return coluna;}
    bool getconsumido() const {return consumido;}
    int gettempo() const {return tempo;}
    int getvalornut() const {return  valorNut;}
    int getvalortox() const {return valorTox;}
    string getcheiro() {return cheiro;}
    void imprimeInfo();
};

#endif //META1_ALIMENTOS_H


#ifndef META1_ALIMENTOS_H
#define META1_ALIMENTOS_H

#include <string>
#include <iostream>
using namespace std;

class Alimentos {
    int id;
    char tipo;
    int linha;
    int coluna;
    bool consumido;
    int tempo;
    int valorNut;
    int valorTox;
    string cheiro;
    int idadeMax;
public:
    //Alimentos(){}
    explicit Alimentos (const Alimentos&)=default;

    Alimentos(int id_n, char tipo_n, int linha_n, int coluna_n, bool consumido_n, int tempo_n, int valorNut_n, int valorTox_n, string cheiro_n, int idadeMax_n);
    int getid() const{return id;}
    char gettipo() const{return tipo;}
    int getlinha() const{return linha;}
    int getcoluna() const{return coluna;}
    bool getconsumido() const {return consumido;}
    int gettempo() const {return tempo;}
    int getvalornut() const {return  valorNut;}
    int getvalortox() const {return valorTox;}
    int getidadeMax() const {return idadeMax;}
    void setid(int n) {id=n;}
    void settipo(char n) {tipo=n;}
    void setlinha(int n) {linha=n;}
    void setcoluna(int n) {coluna=n;}
    void setconsumido(bool n) {consumido=n;}
    void settempo(int n) {tempo=n;}
    void setvalorNut(int n) {valorNut=n;}
    void setvalorTox(int n) {valorTox=n;}
    string getcheiro() {return cheiro;}
    void setidadeMax(int n) {idadeMax=n;}
    void imprimeInfo();
    virtual int getnutrinicial() {return -1;}
};

class Relva : public Alimentos{
public:
    Relva(int id, int linha, int coluna) : Alimentos(id, 'r', linha, coluna, false, 0, 3, 0, "erva verdura",20){};
};

class Cenoura : public Alimentos{
public:
    Cenoura(int id, int linha, int coluna) : Alimentos(id, 't', linha, coluna, false, 0, 4, 0, "verdura",-1){};
};

class Bife : public Alimentos{
public:
    Bife(int id, int linha, int coluna) : Alimentos(id, 'b', linha, coluna, false, 0, 10, 2, "carne ketchup",30){};
};

//VERIFICAR TEMPO DE DURAÇÃO: INFINITO-1 ------CHECK
class Corpo : public Alimentos{
    int nutrinicial;
public:
    Corpo(int id, int linha, int coluna, int valorNutri, int valorToxi) : Alimentos(id, 'p', linha, coluna, false, -1, valorNutri, valorToxi, "carne", -1){nutrinicial=valorNutri;};
    int getnutrinicial() override{return nutrinicial;}
};

class alimMist : public Alimentos{
public:
    alimMist(int id, int linha, int coluna) : Alimentos(id, 'a', linha, coluna, false, 0, 6, 1, "carne erva verdura ketchup", 10){};
};

#endif //META1_ALIMENTOS_H

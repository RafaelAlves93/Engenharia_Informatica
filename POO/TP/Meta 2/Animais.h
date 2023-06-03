
#ifndef META1_ANIMAIS_H
#define META1_ANIMAIS_H

#include <string>
#include <vector>
#include <array>
#include "Alimentos.h"
using namespace std;

class Animais {
    int id;
    char especie;
    int linha;
    int coluna;
    bool vivo;
    int idade;
    int saude;
    int movimInst;
    int aprox;
    int peso;
    int idadeMax;
    int fome;
    vector<array<string,3>> historico;
public:
    Animais(){}
    Animais(int id_n, char especie_n, int linha_n, int coluna_n, bool vivo_n, int idade_n, int saude_n, int movimInst_n, int aprox_n, int peso_n, int idadeMax_n, int fome_n);
    int getid() const{return id;}
    char getespecie() const{return especie;}
    int getlinha() const{return linha;}
    int getcoluna() const{return coluna;}
    bool getvivo() const{return vivo;}
    int getidade() const{return idade;}
    int getsaude() const{return saude;}
    int getmovimInst() const{return movimInst;}
    int getaprox() const{return aprox;}
    int getpeso() const{return peso;}
    int getidadeMax() const{return idadeMax;}
    int getfome() const{return fome;}
    void setid(int n) {id=n;}
    void setespecie(char n) {especie=n;}
    void setlinha(int n) {linha=n;}
    void setcoluna(int n) {coluna=n;}
    void setvivo(bool n) {vivo=n;}
    void setidade(int n) {idade=n;}
    void setsaude(int n) {saude=n;}
    void setmovimInst(int n) {movimInst=n;}
    void setaprox(int n) {aprox=n;}
    void setpeso(int n) {peso=n;}
    void setidadeMax(int n) {idadeMax=n;}
    void setfome(int n) {fome=n;}
    void imprimeInfoAnimais() const;
    void preencheHistorico(const string& nome, int nutri, int toxi);
    virtual int getnascimento() {return -1;}
    //DESTRUTOR ANIMAIS
    virtual ~Animais() = default;
};

class Coelho : public Animais{
public:
    Coelho(int id, int linha, int coluna, int saude, int peso) : Animais(id, 'C', linha, coluna, true, 0, saude, 2, 4, peso, 30, 0){};
};

class Ovelha : public Animais{
public:
    Ovelha(int id, int linha, int coluna, int saude, int peso) : Animais(id, 'O', linha, coluna, true, 0, saude, 2, 3,peso, 35, 0){};
};

class Lobo : public Animais{
    int nascimento;
public:                                                                                                                                                             //ASSIM QUE UM LOBO NASCE TEM DE SER DECIDIDO QUANDO VAI TER UM FILHO (APENAS 1)
    Lobo(int id, int linha, int coluna, int saude) : Animais(id, 'L', linha, coluna, true, 0, saude, 2, 5,15,40, 0){nascimento=rand()%(40-5 + 1) + 5;}//593 RESERVA É VERIFICADO SE JA ATENGIU A IDADE
    int getnascimento() override{return nascimento;}
};

class Canguru : public Animais{
public:
    Canguru(int id, int linha, int coluna, int saude) : Animais(id, 'G', linha, coluna, true, 0, saude, 2, 7,10,70,0){};
};

class AnimMist : public Animais{
public:
    AnimMist(int id, int linha, int coluna, int saude) : Animais(id, 'M', linha, coluna, true, 0, 40, 2, 4,20,30,0){};
};

#endif //META1_ANIMAIS_H

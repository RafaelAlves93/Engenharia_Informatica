#ifndef FICHA_4_AGENDASET_H
#define FICHA_4_AGENDASET_H

#include <iostream>
#include <set>

#include "Amigo.h"

using namespace std;

class AgendaSet {
public:
    AgendaSet(const string &nome);
    void adiciona(const string &nome, int tel);
    int procura(const string &nome);
    void elimina(const string &nome);
    void eliminaOsQueTem(const string &nome);
    string obtemLista();
    string obtemListaDestes(int min, int max);
    void atualizaNumero(const string &nome, int novoNumero);

private:
    string nome;
    set<Amigo> amigos;
};





#endif //FICHA_4_AGENDASET_H

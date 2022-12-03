#ifndef FICHA_4_AGENDAVECTOR_H
#define FICHA_4_AGENDAVECTOR_H

#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "Amigo.h"

using namespace std;

class AgendaVector {
public:
    AgendaVector(const string &nome);
    void adiciona(const string &nome, int tel);
    int procura(const string &nome);
    void elimina(const string &nome);
    void eliminaOsQueTem(const string &nome);
    string obtemLista();
    string obtemListaDestes(int min, int max);
    void ordena();
    void atualizaNumero(const string &nome, int novoNumero);

private:
    string nome;
    vector<Amigo> amigos;
};





#endif //FICHA_4_AGENDAVECTOR_H

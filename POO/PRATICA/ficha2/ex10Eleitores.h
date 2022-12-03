#ifndef FICHA2_EX10ELEITORES_H
#define FICHA2_EX10ELEITORES_H

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class ex10Eleitores {
public:
    ex10Eleitores(initializer_list<int> listaEleitores);
    ex10Eleitores(int eleitor1, int eleitor2);

    void adicionaEleitores(initializer_list<int> novosEleitores);
    void eliminaEleitor(int eleitorAEliminar);
    void eliminaIntervaloDeEleitores(int primeiroAEliminar, int ultimoAEliminar);

    string getAsString() const;
    string getListaEleitores() const;
private:
    static const int minNumeroEleitor = 1000;
    static const int maxNumeroEleitor = 9999;
    vector<int> eleitores;
    void ordenaEliminaDuplicados();
    void verificaEleitores();
};


#endif //FICHA2_EX10ELEITORES_H
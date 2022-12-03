#include "ex10Eleitores.h"

using namespace std;

ex10Eleitores::ex10Eleitores(initializer_list<int> listaEleitores) : eleitores(listaEleitores) {
    ordenaEliminaDuplicados();
}

ex10Eleitores::ex10Eleitores(int eleitor1, int eleitor2) {
    eleitores.push_back(eleitor1);
    eleitores.push_back(eleitor2);
    ordenaEliminaDuplicados();
}

void ex10Eleitores::adicionaEleitores(initializer_list<int> novosEleitores) {
    for(auto it = novosEleitores.begin(); it < novosEleitores.end(); ++it){
        eleitores.push_back(*it);
    }
    ordenaEliminaDuplicados();
}

void ex10Eleitores::eliminaEleitor(int eleitorAEliminar) {
    for(auto it = eleitores.begin(); it < eleitores.end(); ++it){
        if(*it == eleitorAEliminar){
            eleitores.erase(it);
            return;
        }
    }
}

void ex10Eleitores::eliminaIntervaloDeEleitores(int primeiroAEliminar, int ultimoAEliminar) {
    for(auto it = eleitores.begin(); it < eleitores.end(); ){
        if(*it>=primeiroAEliminar && *it<=ultimoAEliminar){
            it = eleitores.erase(it);
        }
        else
            ++it;
    }
}

void ex10Eleitores::ordenaEliminaDuplicados() {
    sort(eleitores.begin(), eleitores.end());
    eleitores.erase(unique(eleitores.begin(), eleitores.end()), eleitores.end());
    verificaEleitores();
}

void ex10Eleitores::verificaEleitores() {
    for(auto it = eleitores.begin(); it < eleitores.end(); ){
        if(*it < minNumeroEleitor || *it > maxNumeroEleitor){
            it = eleitores.erase(it);
        } else
            ++it;
    }
}

string ex10Eleitores::getListaEleitores() const {
    ostringstream os;

    os << "***** Eleitores: *****" << endl;
    for(auto it = eleitores.begin(); it < eleitores.end(); ++it){
        os << *it << endl;
    }
    os << endl;

    return os.str();
}

string ex10Eleitores::getAsString() const {
    ostringstream os;

    os << "Menor eleitor: " << eleitores.at(0) << endl;
    os << "Maior eleitor: " << eleitores.at(eleitores.size() - 1) << endl;
    os << "Numero de eleitores: " << eleitores.size() - 1 << endl;

    return os.str();
}
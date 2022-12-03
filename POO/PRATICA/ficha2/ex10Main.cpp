#include <iostream>
#include "ex10Eleitores.h"

int main(){
    ex10Eleitores eleitores({2500, 1000, 2000, 30000, 9999, 1000, 999});
    ex10Eleitores lista = ex10Eleitores(1, 2);
    cout << eleitores.getAsString();
    cout << eleitores.getListaEleitores();

    eleitores.adicionaEleitores({7000, 5000});
    cout << eleitores.getAsString();
    cout << eleitores.getListaEleitores();

    eleitores.eliminaEleitor(2500);
    cout << eleitores.getAsString();
    cout << eleitores.getListaEleitores();

    eleitores.eliminaIntervaloDeEleitores(2000, 7000);
    cout << eleitores.getAsString();
    cout << eleitores.getListaEleitores();
    return 0;
}
#include <iostream>
#include "ex1Ponto.h"

int main() {
    ex1Ponto a(1, 2), b(3, 4);
    cout << a.getAsString();
    cout << b.getAsString();

    const ex1Ponto c(5, 6);
    cout << c.getX() << endl;
    cout << c.getY() << endl;
    cout << c.getAsString();
    //c.setX(5); -> não dá pois o método não é constante

    cout << a.obtemDistancia(b) << endl;
    cout << b.obtemDistancia(a) << endl;
    cout << c.obtemDistancia(a) << endl;

    b.setX(0);
    b.setY(0);
    cout << b.getAsString();

    ex1Ponto matrizPontos[3]{{1, 3}, {2, 4}, {5, 7}};
    /*ex1Ponto d;
    cout << d.getAsString();*/
    return 0;
}
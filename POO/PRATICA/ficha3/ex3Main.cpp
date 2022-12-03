#include <iostream>
#include "ex3Retangulo.h"

int main() {
    ex1Ponto p1(1, 2);
    ex3Retangulo a(p1, -1, 3), b(p1, 4, 5);
    cout << a.getCantoSuperiorEsquerdo().getAsString() << endl;
    cout << a.getLargura() << endl;
    cout << a.getAltura() << endl;

    p1.setX(2);
    p1.setY(3);
    cout << "p1" << p1.getAsString() << endl;
    cout << "a" << a.getCantoSuperiorEsquerdo().getAsString() << endl;
    return 0;
}
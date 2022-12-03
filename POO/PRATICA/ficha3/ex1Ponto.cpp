#include "ex1Ponto.h"

ex1Ponto::ex1Ponto(int x, int y) : x(x), y(y){
    cout << "A construir" << getAsString();
}

ex1Ponto::~ex1Ponto() {
    cout << "destruido: " << getAsString();
}

double ex1Ponto::obtemDistancia(const ex1Ponto &p) const{
    double distancia;
    distancia = sqrt(pow(p.getX() - x, 2) + pow(p.getY() - y, 2));
    return distancia;
}

string ex1Ponto::getAsString() const {
    ostringstream os;
    os << "(" << x << "/" << y << ")" << endl;
    return os.str();
}

int ex1Ponto::getX() const {
    return x;
}

void ex1Ponto::setX(int x) {
    ex1Ponto::x = x;
}

int ex1Ponto::getY() const {
    return y;
}

void ex1Ponto::setY(int y) {
    ex1Ponto::y = y;
}
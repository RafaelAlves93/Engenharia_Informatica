#ifndef FICHA3_EX1PONTO_H
#define FICHA3_EX1PONTO_H

#include <iostream>
#include <sstream>
#include <complex>
//pow(x,y) -> potencia(base, expoente)
//sqrt(x) -> raiz quadrada de x
//ambas devolvem double
//incluir biblioteca complex

using namespace std;

class ex1Ponto {
public:
    ex1Ponto(int x, int y);
    //ex1Ponto(int x = 0, int y = 0);
    ~ex1Ponto();

    double obtemDistancia(const ex1Ponto &p) const;

    string getAsString() const;

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);
private:
    int x, y;
};

#endif //FICHA3_EX1PONTO_H
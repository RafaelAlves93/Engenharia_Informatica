#ifndef FICHA3_EX3RETANGULO_H
#define FICHA3_EX3RETANGULO_H
#include "ex1Ponto.h"

class ex3Retangulo {
public:
    ex3Retangulo(const ex1Ponto canto, int largura, int altura);
    ex3Retangulo(const ex3Retangulo &retangulo);
    ~ex3Retangulo();

    const ex1Ponto &getCantoSuperiorEsquerdo() const;

    int getLargura() const;

    int getAltura() const;

private:
    ex1Ponto cantoSuperiorEsquerdo;
    int largura;
    int altura;
};

#endif //FICHA3_EX3RETANGULO_H
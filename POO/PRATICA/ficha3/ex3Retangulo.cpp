#include "ex3Retangulo.h"

ex3Retangulo::ex3Retangulo(const ex1Ponto canto, int largura, int altura) : cantoSuperiorEsquerdo(canto), largura (largura > 0 ? largura : 0), altura (altura > 0 ? altura : 0) {
    cout << "A construir" << endl;
}

ex3Retangulo::~ex3Retangulo() {
    cout << "A destruir" << endl;
}

const ex1Ponto &ex3Retangulo::getCantoSuperiorEsquerdo() const {
    return cantoSuperiorEsquerdo;
}

int ex3Retangulo::getLargura() const {
    return largura;
}

int ex3Retangulo::getAltura() const {
    return altura;
}

ex3Retangulo::ex3Retangulo(const ex3Retangulo &retangulo) : cantoSuperiorEsquerdo(retangulo.cantoSuperiorEsquerdo), largura (retangulo.largura),
        altura (retangulo.altura) {
    cout << "A construir por copia" << endl;

}

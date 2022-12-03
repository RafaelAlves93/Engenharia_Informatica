#include "ex7MSG.h"
#include <sstream>

int ex7MSG::numero = 0;

ex7MSG::ex7MSG(char letra) : letra(letra), numMsg(++numero) {
    cout << "criado: " << getAsString();
}

ex7MSG::ex7MSG(const ex7MSG &z) : letra(z.letra), numMsg(-z.numMsg) {
    cout << "Construido por copia." << endl;
}

ex7MSG::~ex7MSG() {
    cout << "terminado: " << getAsString();
}

string ex7MSG::getAsString() const {
    ostringstream os;
    os << "letra: " << letra << " numero: " << numMsg << endl;
    return os.str();
}
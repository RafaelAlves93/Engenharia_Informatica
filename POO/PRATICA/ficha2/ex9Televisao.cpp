#include "ex9Televisao.h"

ex9Televisao::ex9Televisao(string *canais, int numCanais) : volume(5), ligada(false), quantCanais(numCanais), canalAtual(canais[0]), numCanal(1){
    for(int i = 0; i < numCanais; i++){
        //this->canais[i] = canais[i];
        this->canais.push_back(canais[i]);
    }
}

void ex9Televisao::onOff() {
    ligada = !ligada;
}

void ex9Televisao::aumentarVolume() {
    if(volume < 10)
        volume ++;
}

void ex9Televisao::diminuirVolume() {
    if(volume > 0)
        volume --;
}

void ex9Televisao::mudaCanal(int canal) {
    if(canal < quantCanais && canal >= 0)
    canalAtual = canais[canal - 1];
    numCanal = canal;
}

string ex9Televisao::getAsString() const {
    ostringstream os;
    if(!ligada){
        os << "desligada" << endl;
        return os.str();
    }
    os << "Canal: " << canalAtual << "; Numero Canal: " << numCanal << "; Volume: " << volume << endl;
    return os.str();
}

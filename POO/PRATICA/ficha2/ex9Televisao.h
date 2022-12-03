#ifndef FICHA2_EX9TELEVISAO_H
#define FICHA2_EX9TELEVISAO_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class ex9Televisao {
public:
    ex9Televisao(string canais[], int numCanais);
    ~ex9Televisao();
    void onOff();

    void aumentarVolume();
    void diminuirVolume();

    void mudaCanal(int canal);

    string getAsString() const;

private:
    int volume, quantCanais, numCanal;
    bool ligada;
    string /*canais[10],*/ canalAtual;
    vector<string> canais;
    //vector<string> canais; ->#include <vector> ->push_back coloca na última posição ->pop_back remove o ultimo
    //canais.push_back("tvi") -> copia o "tvi" para a ultima posição do vetor
};


#endif //FICHA2_EX9TELEVISAO_H
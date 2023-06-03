//
// Created by rafaa on 25/11/2022.
//

#include "Animais.h"

Animais::Animais(char especie_n, int linha_n, int coluna_n) {
    especie = especie_n;
    linha = linha_n;
    coluna = coluna_n;
}

void Animais::imprimeInfoAnimais() const {
    cout << "Id: " << id << endl;
    cout << "Especie: " << especie << endl;
    cout << "Linha: " << linha << endl;
    cout << "Coluna: " << coluna << endl;
    cout << "Estado: ";
    if (vivo)
        cout << "Vivo" << endl;
    else
        cout << "Morto" << endl;
    cout << "Idade: " << idade << endl;
    cout << "Saude: " << saude << endl;
    cout << "Movimento : " << movimInst << endl;
    cout << "Aproximacao: " << aprox << endl;
}
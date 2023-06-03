//
// Created by rafaa on 25/11/2022.
//

#include "Alimentos.h"

Alimentos::Alimentos(char tipo_n, int linha_n, int coluna_n) {
    tipo = tipo_n;
    linha = linha_n;
    coluna = coluna_n;
}

void Alimentos::imprimeInfo() {
    cout << "Id: " << id << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Linha: " << linha << endl;
    cout << "Coluna: " << coluna << endl;
    cout << "Estado: ";
    if (consumido)
        cout << "Consumido" << endl;
    else
        cout << "Nao Consumido" << endl;
    cout << "Tempo: " << tempo << endl;
    cout << "Valor Nutritivo: " << valorNut << endl;
    cout << "Valor Toxico: " << valorTox << endl;
    cout << "Cheiro: " << cheiro << endl;
}
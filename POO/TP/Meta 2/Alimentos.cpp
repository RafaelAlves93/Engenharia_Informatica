
#include "Alimentos.h"

Alimentos::Alimentos(int id_n, char tipo_n, int linha_n, int coluna_n, bool consumido_n, int tempo_n, int valorNut_n, int valorTox_n, string cheiro_n, int idadeMax_n) {
    id = id_n;
    tipo = tipo_n;
    linha = linha_n;
    coluna = coluna_n;
    consumido = consumido_n;
    tempo = tempo_n;
    valorNut = valorNut_n;
    valorTox = valorTox_n;
    cheiro = cheiro_n;
    idadeMax = idadeMax_n;
}

void Alimentos::imprimeInfo() {
    cout << "Id:" << id << endl;
    cout << "Tipo:" << tipo << endl;
    cout << "Linha:" << linha << endl;
    cout << "Coluna:" << coluna << endl;
    cout << "Estado:";
    if (consumido)
        cout << "Consumido" << endl;
    else
        cout << "Nao Consumido" << endl;
    cout << "Tempo:" << tempo << endl;
    cout << "Valor Nutritivo:" << valorNut << endl;
    cout << "Valor Toxico:" << valorTox << endl;
    cout << "Cheiro:" << cheiro << endl;
}

#include <iostream>

using namespace std;

struct Tabela{
    static const int TAM = 10;
    int mat[TAM];
};

void preenche(int valor, Tabela &tabela){
    /*
     * Foreach:
     * for(int &valor (Representa o valor do índice atual) : valores(identifica o array a percorrer))
     */
    for(int &val : tabela.mat){
        val = valor;
    }
}

void listar(const Tabela &tabela){ //forma correta seria não utilizar cin e cout, apenas return e imprimir no main()
    cout << endl << "***** Tabela *****" << endl;
    for(const int &i : tabela.mat){
        cout << i << " ";
    }
    cout << endl;
}

void obtemValor(const Tabela &tabela, int indice){
    if(indice > tabela.TAM || indice < 0){
        cout << endl << "Indice invalido." << endl;
        return;
    }
    cout << endl << "Valor no indice " << indice << "= " << tabela.mat[indice] << endl;
}

void alteraValor(Tabela &tabela, int indice, int valor){
    if(indice > tabela.TAM || indice < 0){
        cout << endl << "Indice invalido." << endl;
        return;
    }
    tabela.mat[indice] = valor;
}

int& obtemEAltera(Tabela &tabela, int indice){
    if(indice > tabela.TAM || indice < 0){
        static int error = -1;
        return error;
    }
    return tabela.mat[indice];
}


void obtemEAlteraEmExcecao (Tabela &tabela, int index) noexcept{
    try{
        obtemEAltera(tabela, index);
    } catch(int index){
        cout << "Erro ao aceder ao index " << index << endl;
    }
}

int main() {
    int valor, indice;
    Tabela tabela;

    cout << "Insira o valor com o qual pretende preencher: ";
    cin >> valor;

    preenche(valor, tabela);

    listar(tabela);

    cout << "Indique o indice cujo valor quer obter: ";
    cin >> indice;

    obtemValor(tabela, indice);

    cout << "Indique o idice do valor que pretende alterar: ";
    cin >> indice;
    cout << endl << "Indique o novo valor: ";
    cin >> valor;

    alteraValor(tabela, indice, valor);
    listar(tabela);

    cout << endl;
    cout << "ObtemEAltera: " << obtemEAltera(tabela, 25) << endl;
    cout << "ObtemEAltera: " << obtemEAltera(tabela, indice) << endl;
    obtemEAltera(tabela,indice) = 9;
    cout << "ObtemEAltera: " << obtemEAltera(tabela,indice) << endl;
    listar(tabela);
    return 0;
}

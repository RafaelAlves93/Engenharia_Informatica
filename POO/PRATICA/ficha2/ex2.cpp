#include <iostream>
#include <sstream>

using namespace std;

class Tabela{
public:
    Tabela(){
        preenche(0);
    }

    Tabela(int valor){
        preenche(valor);
    }

    void preenche(int valor){
        for(int &val : this->mat){
            val = valor;
        }
    }

    void listar(){
        cout << endl << "***** Tabela *****" << endl;
        for(const int &i : this->mat){
            cout << i << " ";
        }
        cout << endl;
    }

    int obtemValor(int indice){
        if(indice > this->TAM || indice < 0){
            return -1;
        }
        return this->mat[indice];
    }

    void alteraValor(int indice, int valor){
        if(indice > this->TAM || indice < 0){
            return;
        }
        this->mat[indice] = valor;
    }

    int& obtemEAltera(int indice){
        if(indice > this->TAM || indice < 0){
            static int error = -1;
            return error;
        }
        return this->mat[indice];
    }

    string getAsString() const{
        ostringstream os;
        os << "Obter lista de valores" << endl;
        for(int val : this->mat){
            os << val << " ";
        }
        os << endl;
        return os.str();
    }

private:
    static const int TAM = 10;
    int mat[TAM];

};

int main(){
    Tabela tabela, tabela2, tabela3(5);
    tabela.listar();
    tabela.preenche(10);
    tabela.listar();
    cout << "Valor obtido " << tabela.obtemValor(5) << endl;
    tabela.alteraValor(5, 8);
    tabela.obtemEAltera(5) = 5;

    tabela2.listar();

    tabela3.listar();

    cout << tabela.getAsString();

    return 0;
}
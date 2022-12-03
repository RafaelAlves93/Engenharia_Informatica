#include <iostream>
#include <limits>

//Ex 2 e 3 da ficha 1

using namespace std;

int main() {
    const int MAX_TAM = 100;
    char nome[MAX_TAM];
    string nome2;
    int idade;

    //>> operador de extração
    //<< operador de inserção

    cout << "*** EX2 ***" << endl;

    cout << "Nome: ";
    //cin.getline(nome, MAX_TAM); //se for array de char
    getline(cin, nome2); //se for string

    while(true){
        cout << endl << "Idade: ";
        cin >> idade;

        if(!cin.fail() && idade > 0) break;//cin.fail() = true se tipo de dados recebido incompatível com o tipo de dados da variável

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Nome: " << nome2 << endl << "Idade: " << idade << endl;
    return 0;
}
//uma função que esteja dentro duma classe e associada a uma classe chama-se um método.

//Métodos cin:
/*
 * fail() - devolve true se a conversão falhar. Nesse caso o input fica num estado de erro.
 * clear() - quando o input está num estado de erro o seu processamento é parado. Após este método podemos limpar esse estado e continuar o processamento.
 * ignore(streamsize n, int delim) - permite extrair do input N caracteres e descarta-os até ao valor de N ser atingido ou o delimitador ser encontrado
 *      para ignorar tudo utilizar: cin.ignore(numeric_limits<streamsize>::max(), '\n');
 */
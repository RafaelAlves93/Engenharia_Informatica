#include <iostream>

using namespace std;
/*
 * Funções overloaded
 *
 * Possível definir funções com o mesmo nome se diferirem nas seguintes circunstâncias:
 * -tipo de argumentos
 * -número de argumentos
 * -ambos
 *
 * O tipo de retorno não serve como critério para distinguir funções com o mesmo nome.
 *  -void func()
 *  -void func(int parâmetro)
 */

void imprime(string s){
    cout << s << endl;
}

void imprime(string s, int i){
    cout << s << i << endl;
}

void imprime(int i, string s){
    cout << i << s << endl;
}

int main() {
    imprime("ola");
    imprime("a idade e: ", 25);
    imprime(100, " euros");
    return 0;
}
#include <iostream>

/*
 * Ponteiros:
 *  -Identificados por *
 *  -Aponta para o espaço de memória ocupado por uma variável
 *  EX: int i = 5; <--*p
 *
 * Referências:
 *  -Identificados por &
 *  -Funciona como uma representação da variável (alias)
 *  EX: int i = 5;  int &r = i;
 *
 *  PONTEIROS E REFERÊNCIAS
 *  --Principais diferenças e cuidados a ter--
 *  -Referências têm que ser inicializadas no momento de criação e não podem ser alteradas no futuro.
 *  -Referências têm que ter sempre um valor não nulo.
 *  -Ponteiros têm que ser desreferenciados usando *.
 */

using namespace std;
//c
void troca(int *primeiro, int *segundo){
    int aux = *primeiro;
    *primeiro = *segundo;
    *segundo = aux;
}

int main(){
    int a = 5, b = 10;
    troca(&a,&b);
    cout << "\na = " << a << "\nb = " << b;
} // deve aparecer a = 10 e b = 5

//cpp
/*
void troca(int &primeiro, int &segundo){
    int aux = primeiro;
    primeiro = segundo;
    segundo = aux;
}

int main(){
    int a = 5, b = 10;
    troca(a,b);
    cout << "\na = " << a << "\nb = " << b;
} // deve aparecer a = 10 e b = 5*/
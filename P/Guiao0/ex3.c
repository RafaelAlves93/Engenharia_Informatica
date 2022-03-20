#include <stdio.h>
#include <stdlib.h>
#define TAM 5

int maiorn(int tabela[], int tam) {
    int max = 0, cont = 0;
    for(int i = 0; i < tam; i++) {
        if(tabela[i] > max)
            cont=0;
        if(tabela[i] >= max) {
            max = tabela[i];
            cont++;
        }
    }
    return cont;
}

void main() {
    int tabela[TAM] = {1,5,2,4,5};
    printf("\nNumero de vezes que o maior numero aparece : %d\n", maiorn(tabela, TAM));
}
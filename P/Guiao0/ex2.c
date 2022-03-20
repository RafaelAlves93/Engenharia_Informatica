#include <stdio.h>
#include <stdlib.h>
#define TAM 5

int maior(int tabela[], int tam){
    int max = tabela[0];
    int posi;
    for(int i = 0; i < tam; i++) {
        if(tabela[i] > max) {
            max = tabela[i];
            posi = i;
        }
    }
    return posi+1;
}

void main() {
    int tabela[TAM] = {1,2,2,4,5};
    printf("\nPosicao do maior numero: %d\n", maior(tabela, TAM));
}
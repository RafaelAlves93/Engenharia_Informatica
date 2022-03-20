#include <stdio.h>
#include <stdlib.h>
#define TAM 5

int vezesmaior(int tabela[], int tam) {
    int max = 0, cont[TAM], j = 0, contador = 0, maior = 0, num;
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(tabela[j] == tabela[i]){
                contador++;
                num = tabela[j];
            }
        }
        if(contador >= max && num > maior) {
            max = contador;
            maior = num;
        }
        contador = 0;
    }
    return maior;
}

void main() {
    int tabela[TAM] = {1,6,6,5,5};
    printf("\nNumero que mais vezes aparece: %d\n", vezesmaior(tabela, TAM));
}
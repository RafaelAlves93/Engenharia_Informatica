#include <stdio.h>
#include <stdlib.h>
#define TAM 5

int pesquisa(int tabela[], int tam, int num){
    for(int i = 0; i < tam; i++) {
        if(tabela[i] == num)
            return 1;
    }
    return 0;
}

void main() {
    int tabela[TAM] = {1,2,3,4,5};
    if(pesquisa(tabela, TAM, 5))
        printf("\nO numero aparece\n");
    else
        printf("\nO numero NAO aparece\n");
}
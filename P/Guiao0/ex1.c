#include <stdio.h>
#include <stdlib.h>
#define TAM 5

int maiorNum(int vetor[], int tam){
    int maior = vetor[0];
    for(int i = 1; i < tam; i++){
        if(vetor[i] > maior)
            maior = vetor[i];
    }
    return maior;
}

void main(void) {

    int vetor[TAM], i;

    for(i = 0; i < TAM; i++){
        printf("Numero %d: ", i+1);
        scanf("%d", &vetor[i]);
    }
    printf("\nO maior numero do seu array e o %d\n", maiorNum(vetor, TAM));
}
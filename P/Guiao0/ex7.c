#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM 5

float desvioPadrao(int vetor[]) {

    float media = 0, somatorio = 0, desvio, r;

    for(int i = 0; i < TAM; i++)
        media += vetor[i];
    media /= TAM;
    for(int i = 0; i < TAM; i++) {
        somatorio += pow((media-vetor[i]), 2);
    }
    desvio =sqrt(((float)1/(float)TAM)*somatorio);
    return desvio;

}

void main(void) {
    int vetor[TAM];
    for(int i = 0; i < TAM; i++){
        printf("%d elemento: ", i+1);
        scanf(" %d", &vetor[i]);
    }
    printf("O desvio vai ser de %.3f",desvioPadrao(vetor));
}
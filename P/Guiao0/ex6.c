#include <stdio.h>
#include <stdlib.h>

void calculaSoma(int tab[], int dim, int valor);

void main(void) {
    int tam, valor;
    do{
        printf("Qual o tamanho do seu array (maior que 3): ");
        scanf("%d", &tam);
    }while(tam <= 3);
    int vetor[tam];
    for(int i = 0; i < tam; i++) {
        printf("Elemento %d: ", i+1);
        scanf("%d", &vetor[i]);
    }
    printf("Valor a verificar combinacoes: ");
    scanf("%d", &valor);
    calculaSoma(vetor, tam, valor);
}

void calculaSoma(int tab[], int dim, int valor) {

   for(int i = 0; i < dim; i++){
       for(int j = i+1; j < dim; j++){
          for(int x = j+1; x < dim; x++){
            if(tab[i] + tab[j] + tab[x] == valor){
                printf("%d %d %d\n", tab[i], tab[j], tab[x]);
            }
          }
       }
   }
}
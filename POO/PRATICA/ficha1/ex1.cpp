#include <stdio.h>

int main() {
    char nome[50];
    int idade;

    printf("*** EX1 ***\n");

    printf("Nome: ");
    scanf("%s", nome); //so aceita primeiro nome
    printf("\nIdade: ");
    scanf("%d", &idade);

    printf("\n%s\n", nome);
    printf("%d", idade);
    return 0;
}
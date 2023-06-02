#include <stdio.h>
#include <string.h>
#define TAM 100


int verifica(char* frase1, char* frase2);

int main(void) {
	char frase1[TAM], frase2[TAM];

	printf("\nPrimeira Frase: ");
	gets(frase1);
	printf("Segunda Frase: ");
	gets(frase2);
	if(verifica(frase1, frase2))
		printf("\n\tAs frases sao iguais\n");
	else
		printf("\n\tAs frases NAO sao iguais\n");
}

///Maneira mais simples e rapida

// int verifica(char* frase1, char* frase2) { 
// 	if(strcmp(frase1,frase2))
// 		return 0;
// 	else
// 		return 1;
// }
 
 // Outra forma de verificar
 int verifica(char* frase1, char* frase2) {
 	if(strlen(frase1) != strlen(frase2))return 0;
 	int cont = 0;
 	for(int i = 0; i < strlen(frase1) ; i++)
 		cont += *(frase1+i) == *(frase2+i);
 	if(cont == strlen(frase1))return 1;
 	return 0;
 }
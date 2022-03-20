#include <stdio.h>
#include <string.h>
#define TAM 500

void iguais(char fr1[], char fr2[], char fr3[]);

void main(void) {
	char fr1[TAM], fr2[TAM], fr3[TAM];

	printf("Frase 1: ");
	gets(fr1);
	printf("Frase 2: ");
	gets(fr2);
	iguais(fr1, fr2, fr3);

}

void iguais(char fr1[], char fr2[], char fr3[]) {
	char tamIgual[] = "Tamanho Igual!";
	char contIgual[] = "Conteudo Igual!";

	if(strcmp(fr1, fr2) == 0)
		strcpy(fr3, contIgual);
	else if(strlen(fr1) == strlen(fr2))
		strcpy(fr3, tamIgual);
	else if(strlen(fr1) < strlen(fr2)){
		strcat(fr1, fr2);
		strcpy(fr3, fr1);
	}
	else{
		strcat(fr2, fr1);
		strcpy(fr3, fr2);
	}
	puts(fr3);

}
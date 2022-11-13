#include <stdio.h>
#include <string.h>
#define TAM 100

void obtemFrase(char frase[]);
int capicua(char frase[]);

void main(void) {
	char frase[TAM];

	obtemFrase(frase);
	if(capicua(frase))
		printf("\nE uma capicua\n");
	else
		printf("\nNAO e uma capicua\n");
}

void obtemFrase(char frase[]) {
	printf("Frase: ");
	gets(frase);
}

int capicua(char frase[]) {
	for(int i = 0; i < strlen(frase)/2 ; i++){
		if(frase[i] != frase[strlen(frase)-(i+1)])
			return 0;
	}
	return 1;
	
}
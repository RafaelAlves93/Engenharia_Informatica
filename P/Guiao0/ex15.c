#include <stdio.h>
#include <string.h>
#define TAM 100

void apagarEsp(char frase[]);

void main(void) {
	char frase[TAM];
	printf("Frase: ");
	gets(frase);
	apagarEsp(frase);
}

void apagarEsp(char frase[]) {
	int x = 0;
	char fraseSemEsp[TAM];

	for(int i = 0; frase[i] != '\0'; i++){
		if(frase[i] != ' '){
			while(frase[i] != ' ' && frase[i] != '\0'){
				fraseSemEsp[x++] = frase[i++];
			}
			fraseSemEsp[x++] = ' ';
			if(frase[i] == '\0'){
				i--;
				x--;
			}
		}
	}
	fraseSemEsp[x] = '\0';
	puts(fraseSemEsp);
}
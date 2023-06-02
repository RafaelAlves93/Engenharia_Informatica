#include <stdio.h>
#include <ctype.h>
#define NUM 9
void verifica(char *tel, char *c);

int main(void) {
	char telefone[NUM], car;
	
	printf("Numero a verificar se e da PT: ");
	gets(telefone);
	verifica(telefone, &car);
	if(car == 'V') 
		printf("\nE um numero da PT\n");
	else
		printf("\nNAO e um numero da PT\n");
}

void verifica(char *tel, char *c) {
	for(int i = 0; i < 9; i++) {
		if(isdigit(*(tel+i)) && *(tel) == '2'){
			*c = 'V';
		}
		else
			*c = 'I';
	}
}
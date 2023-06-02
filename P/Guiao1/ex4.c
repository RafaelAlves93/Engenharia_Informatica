#include <stdio.h>

void f(int *t, int tam, int *np, int *ni, int *maior, int *pos) {
	for(int i = 0; i < tam; i++) {
		if(*(t+i) % 2 == 0)
			(*np)++;
		else
			(*ni)++;
		if(*(t+i) > *maior){
			*maior = *(t+i);
			*pos = i;
		}
	}
}

void main() {
	int tab[10] = {1,3,7,5,2,10,9,7,7,1}, p = 0, i = 0, maior = 0, pos;
	f(tab, 10, &p, &i, &maior, &pos);
	printf("\nExistem %d numeros pares, %d numeros impares. O maior numero e o %d e esta na posicao %d.\n", p, i, maior, pos);
}
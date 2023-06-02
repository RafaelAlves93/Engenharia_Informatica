#include <stdio.h>

void zeros(int *tab, int tam) {
	float media = 0;
	for(int i = 0; i < tam; i++)
		media += *(tab + i);
	media /= tam;
	for(int i = 0; i < tam; i++){
		if(*(tab + i) < media)
			*(tab + i) = 0;
		printf(" %d ", *(tab + i));
	}


}

void main() {
	int tab[5] = {1,2,3,4,5};
	zeros(tab, 5);
}
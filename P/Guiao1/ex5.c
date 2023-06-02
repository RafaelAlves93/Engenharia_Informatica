#include <stdio.h>

int comuns(int *tabA, int tamA, int *tabB, int tamB);

void main(void) {
	int tab1[5] = {1,3,5,7,9}, tab2[7] = {3,5,7,9,11,13,15};
	printf("\nA tabela vai ter %d elementos em comum\n",comuns(tab1, 5, tab2, 7));

}

int comuns(int *tabA, int tamA, int *tabB, int tamB) {
	int cont = 0;
	for(int i = 0; i < tamA; i++) {
		for(int j = 0; j < tamB; j++) {
			if(*(tabA + i) == *(tabB + j))
				cont++;
		}
	}
	return cont;
}
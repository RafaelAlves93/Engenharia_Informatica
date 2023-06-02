#include <stdio.h>

void vizinhos(int *tab, int dim, int *igual);

void main(void) {
	int tab[] = {1,2,3,3,3,6,8,9,8}, igual;
	vizinhos(tab, 9, &igual);
	printf("\nO numero de elementos igual a media dos seus 2 vizinhos: %d\n", igual);
}

void vizinhos(int *tab, int dim, int *igual) {
	for(int i = 0; i < dim; i++){
		if(i < dim - 2){
			if(*(tab+i) == (*(tab+(i+1))+*(tab+(i+2)))/(float)2)
				(*igual)++;
		}
	}
}
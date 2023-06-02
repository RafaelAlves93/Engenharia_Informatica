#include <stdio.h>

void procura_dupla(int *tab, int tam, int *prim, int *seg);

void main(void) {
	int tab[] = {1,8,9,10,9,8,0}, prim = *tab, seg = *(tab+1);
	procura_dupla(tab, 7, &prim, &seg);
	printf("\nPrimeiro maior numero: %d\tSegundo maior numero: %d\n", prim, seg);
}

void procura_dupla(int *tab, int tam, int *prim, int *seg) {
	for(int i = 2; i < tam; i++){
		if(*(tab+i) != *prim && *(tab+i) != *seg){
			if(*(tab+i) > *prim){
				*prim = *(tab+i);
				i++;
			}
			if(*(tab+i) > *seg)
				*seg = *(tab+i);
		}
	}
	if(*prim > *seg){
		int a = *seg;
		*seg = *prim;
		*prim = a;
	}
}
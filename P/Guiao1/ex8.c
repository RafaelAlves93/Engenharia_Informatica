#include <stdio.h>

int maior_subida(int *tab, int dim);

void main(void){ // Funçao main - Nao pedida no exercicio //
	int tam;
	printf("\nTamanho do seu array: ");
	scanf("%d", &tam);
	int tab[tam]; 
	for(int i = 0; i < tam; i++) // Inicializa a tabela toda a zeros
	 	*(tab+i) = 0;
	for(int i = 1; i <= tam; i++) { 
		printf("\nValor na posicao %d :",i);
		scanf("%d", tab+i-1);
		for(int x = 0; x < tam; x++) { // Printa toda a tabela
			printf(" %d ", *(tab+x));
		}
	}
	printf("\nO numero que apresenta maior subida em relacao ao seu anterior esta na posicao : %d\n",maior_subida(tab, tam)+1);
}

int maior_subida(int *tab, int dim) {
	int maiorsub = *(tab+1)-*tab, pos = 0;
		for(int i = 2; i < dim-1; i++) {
			if(*(tab+i) > *(tab+i-1) && *(tab+i) - *(tab+i-1) > maiorsub){
				maiorsub = *(tab+i) - *(tab+(i-1));
				pos = i;
			}
		}	
	return pos;
}
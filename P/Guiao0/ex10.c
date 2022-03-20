#include <stdio.h>
#define N 3

void iniciaTabela(int a[][N]);
void printaTabela(int a[][N]);
int verificaQuadMagico(int a[][N]);

void main(void) {
	int a[N][N], pos = 1;

	iniciaTabela(a);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printaTabela(a);
			printf("\nValor Posicao %d: ", pos);
			scanf("%d", &a[i][j]);
			pos++;
		}
	}
	printaTabela(a);
	if(verificaQuadMagico(a))
		printf("\nE um cubo magico\n");
	else
		printf("\nNAO e um cubo magico\n");
}

void iniciaTabela(int a[][N]) { //Inicia uma tabela 3x3 tudo a 0 (opcional)
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			a[i][j] = 0;
}

void printaTabela(int a[][N]) { // vai printardo a tabela com os valores que vao sendo escolhidos (opcional)
	printf("\n");
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf(" %d ",a[i][j]);
		}
		printf("\n");
	}

}

int verificaQuadMagico(int a[][N]) { //Verifica se é um quadrado magico
	int valorLinhas = 0, valorColunas = 0, val = a[0][0]+a[1][1]+a[2][2]+a[0][2]+a[1][1]+a[2][0]; //val = valor da soma das 2 diagonais

	for(int i = 0; i < N; i++){ // ciclo que verifica o resultado das linhas e das colunas com o resultado da diagonal
		for(int j = 0; j < N; j++){
			valorLinhas += a[i][j];
			valorColunas += a[j][i];
		}
		if(valorLinhas != val-valorLinhas && valorColunas != val-valorColunas)
			return 0;
		valorLinhas = 0;
		valorColunas = 0;
	}
	return 1;
}
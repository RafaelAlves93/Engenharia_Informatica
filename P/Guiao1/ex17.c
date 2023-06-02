#include <stdio.h>
#define N 3

int transposicao(int (*mat)[N]) { 
	int new[N][N], j = 0, i = 0, x = 0;
	for(int* p = *mat; p <= &mat[N-1][N-1]; p++, i++){
		*(new[i]+j) = *p;
		if(i == N-1){
			j++;
			i = -1;
		}
	}
	for(int* p = *new; p <= &new[N-1][N-1]; p++){
		printf("%d ", *p);
		if(p == new[x]+N-1){
			printf("\n");
			x++;
		}
	}
	

}

int main(void) {
	int mat[N][N] = {{1,2,3},{4,5,6},{7,8,9}}, x = 0; /*transposiçao  	1 2  	1 3
												  				3 4		2 4    */
	printf("\nMatriz Transposta: \n");
	transposicao(mat);
}
#include <stdio.h>
#define N 3
void somaMatriz(int (*mat1)[N], int (*mat2)[N]) {
	int* p2 = *mat2;
	int i = 0;

	for(int* p1 = *mat1; p1 <= &mat1[N-1][N-1]; p1++, p2++){
		*p1 += *p2;
		printf("%d ", *p1);
		if(p1 == *(mat1+i)+N-1){
			printf("\n");
			++i;
		}

	}
}

int main(void) {
	int mat2[N][N] = {{10,20,30},{10,20,30}, {10,20,30}};
	int mat1[N][N] = {{10,20,30},{10,20,30}, {10,20,30}};

	somaMatriz(mat1,mat2);
}
#include <stdio.h>

#define L1	3
#define C1	2

#define L2	4
#define C2	3


void escreve(int n_lin, int n_col, int (*p)[n_col])
{
	int i = 1;
	for(int* x = *p; x <= *(p+n_lin-1)+n_col-1; x++, i++){
		printf("%d ", *x);
		if(i== n_col){
			printf("\n");
			i = 0;
		}
	}
}


int main()
{

	int mat1[L1][C1] = {{1,2}, {3,4}, {5,6}};
	
	int mat2[L2][C2] = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
	
	printf("Matriz 1:\n");
	escreve(L1, C1, mat1);
	
	printf("Matriz 2:\n");
	escreve(L2, C2, mat2);
	
	return 0;
}
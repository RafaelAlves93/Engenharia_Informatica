#include <stdio.h>

#define L1	3
#define C1	2
#define L2	4
#define C2	3

int unicaMat(int nLin, int nCol, int mat[][nCol]);

int main(void) {
	
	int mat1[L1][C1] = {{1,2}, {3,4}, {5,6}};	
	if(unicaMat(L1, C1, mat1))
		printf("\nA matriz E unica\n");
	else
	 	printf("\nA matriz NAO e unica\n");
}

int unicaMat(int nLin, int nCol, int mat[][nCol]) {
	int i = 0, x = 0;
	while(i != nLin){
		for(int* p = *mat; p <= &mat[nLin-1][nCol-1]; p++)
			if(*(&mat[i][x]) == *p && p != &mat[i][x])
				return 0;
		x++;
		if(x == nCol){
			x = 0;
			i++;
		}
	}
	return 1;
		
}
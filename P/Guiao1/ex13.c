#include <stdio.h>
#define N 3

double produto_escalar (double* a, double* b, int n) {
	double escal = 0; 
	for(int i = 0; i < n; i++)
		escal += (*(a+i))*(*(b+i));
	return escal;
}

int main(void) {
	double v1[N] = {1,2,3};
	double v2[N] = {1,5,7};

	printf("O produto escalar entre os 2 vetores vai ser de %.2lf",produto_escalar(v1, v2, N));

}
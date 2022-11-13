#include <stdio.h>
int main()
{
	int a, b, total, *p = &a, *q = &b, *r = &total;
	/* completar */
	printf("Variavel a: ");
	scanf("%d", p);
	printf("Variavel b: ");
	scanf("%d", q);
	*r = *p + *q;
	/* Fim completar */
	printf("a= %d \t b= %d \t total= %d\n", a, b, total);
	return 0;
}
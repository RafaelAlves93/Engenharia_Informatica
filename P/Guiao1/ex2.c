#include <stdio.h>

void troca(float* pa, float* pb, float* pc) {
	float a = *pa, b = *pb, c = *pc;
	*pa = b;
	*pb = c;
	*pc = a;
}

void main(void) {
	float a, b, c;
	printf("Variavel a: ");
	scanf("%f", &a);
	printf("Variavel b: ");
	scanf("%f", &b);
	printf("Variavel c: ");
	scanf("%f", &c);
	troca(&a, &b, &c);
	printf("a = %.2f\tb = %.2f\tc = %.2f", a, b, c);
}
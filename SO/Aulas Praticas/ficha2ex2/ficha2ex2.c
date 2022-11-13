#include <stdio.h>

int main(){
	int num,quad;
	char c;

	printf("Insira um numero: \n");
	scanf("%d", &num);


	quad= num * num;

	printf("O quadrado do numero inserido e: %d.\n", quad);
	printf("Introduza um caracter para sair!\n");
	scanf("%s", &c);

	return 0;
}

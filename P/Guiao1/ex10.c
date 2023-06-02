#include <stdio.h>
#define TAM 100

int tres_consecutivos(char *frase);

int main(void) {
	
	char fr[TAM];
	printf("\nFrase: ");
	gets(fr);
	if(tres_consecutivos(fr))
		printf("\n Existem 3 caracteres consecutivos na frase\n");
	else
		printf("\n NAO existem 3 caracteres consecutivos OU somente 3 consecutivos na frase\n");
}

int tres_consecutivos(char *frase) {
	for(int i = 0; *(frase+i) != '\0'; i++){
		char car = *(frase+i); //guarda o caracter a analisar
		int cont = 0; // vai contar o numero de caracteres que aparecem consecutivamente
		while(*(frase+i) == car && *(frase+i) != '\0'){
			cont ++;
			i++;
		}	
		if(cont == 3)
			return 1;
		i--;
	}
	return 0;
}
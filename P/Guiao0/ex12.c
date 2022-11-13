/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void separaString(char str[]){
    int i;

    for(i=0;i<strlen(str);i++){
        if(str[i] != ' ')
            printf("%c", str[i]);
        else{
            printf("\n");
            while(str[i+1] == ' ')
                i++;
        }
    }
    printf("\n");
    return;
}

/*
void escreve_separado(char *s){
int  i;
for(i=0; i<strlen(s);++i){
  for(; s[i]==' ';++i);
  if(s[i]!='\0'){ //só para escrever o '\n' quando necessario
    for(; s[i]!=' ' && s[i]!='\0';++i)
      putchar(s[i]);
    putchar('\n');
  }
 }
}
*/

/*int main(void){
    char nome[]= "Hoje e        Domingo!";

    separaString(nome);
    return(0);
}*/


//OUTRA RESOLUÇAO


#include <stdio.h>
#define TAM 100

void obtemFrase(char frase[]);
void separaFrase(char frase[]);

void main(void) {
	char frase[TAM];
	
	obtemFrase(frase);
	separaFrase(frase);
}

void obtemFrase(char frase[]) { //obtem a frase do utilizador
	printf("Digite a frase: ");
	gets(frase);
}

void separaFrase(char frase[]) { //separa a frase por palavras em linhas diferentes
	for(int i = 0; frase[i] != '\0'; i++) {
		if(frase[i] != ' ') {
			while(frase[i]!= ' ' && frase[i] != '\0'){
				printf("%c", frase[i]);
				i++;
			}
			putchar('\n');
		}
	}
}
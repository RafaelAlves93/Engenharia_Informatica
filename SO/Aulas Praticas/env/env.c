#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//argv[0] -- nome
//argv[1] -- parametro que eu quero procurar
int main(int argc, char **argv){
	printf("%s - %s\n",argv[1], getenv(argv[1]));
}

//com environ

//	extern char **environ;
//	int i=0;
//	while(environ[i]!=NULL){
//		if(strstr(envp[i], argv[1]))
//		printf("%s\n", environ[i]);
//		i++;
//	}
//}




//vai utilizar a operacao receber as
//variaveis ambiente pelo argumento envp
//o envp e um vetor de strings, que contrem todas as
//variaveis amvbiente

//int main(int argc, char **argv, char **envp){
//	char *ponteiro=envp[0];
//	int i=0;
//	while(ponteiro!=NULL){
//		if(strstr(envp[i],argv[1]))
//			printf("%s", envp[i]);
//		ponteiro=envp[i++];
//	}
//}


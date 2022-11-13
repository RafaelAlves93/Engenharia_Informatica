#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
	setbuf(stdout,NULL);
	char prog[100];
	printf("O meu PID é :[%d]\n",getpid());
	printf("Introduza o programa a executar: \n");
	fflush(stdout);
	scanf("%s",prog);
		if(strcmp(prog,"port")==0){
			printf("\n *** port - execl ***\n");
			execl(prog,prog,NULL);
		}else if (strcmp(prog,"ing")==0){
			printf("\n *** ing - execlp ***\n");
			execlp("./ing","ing",NULL);}
		printf("Missao Cumprida\n");

return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){
	int f;
	if (argc<3){
		printf("\n\nFaltam parametros: texto ficheiro\n\n");
		exit(1);
	}
	close(STDOUT_FILENO);
	f = open(argv[2], O_WRONLY | O_CREAT,
		S_IRWXU | S_IRGRP | S_IROTH);
	if (f==-1){
		perror("\n\nNao foi possivel criar o ficheiro");
		exit(2);
	}
	printf("%s\n", argv[1]);
	return 0;
}

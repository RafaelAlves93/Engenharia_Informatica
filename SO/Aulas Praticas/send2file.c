#


int main(int argc, char * argv[]){
	int f;
	if (argc<3){
		printf("\n\nFaltam parametros\n\n");
		exit(1);
	}
	close(STDOUT_FILENO);
	f = open(argv[2], O_WRONLY | O_CREAT,
		S_IRWXU | S_IRGRP | S_IROTH);
	if(f==-1){
		printf("\n\nNao foi possivel criar o ficheiro");
		exit(2);
	}
	execlp(argv[1],argv

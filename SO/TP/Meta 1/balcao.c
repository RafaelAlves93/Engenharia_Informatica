//
// Autores: Rafael Alves | Ricardo Fernandes
//

#include "estruturas.h"

EstruturaBalcao estruturas;
int vambiente();
int vfich();

int main(int argc, char **argv) {
	int pid,prio,fd_in[2], fd_out[2];
	char input[100], classif[20], diagnostico[20];

	estruturas.n_especialidades = 5;
	estruturas.n_listaespera = 5;

    	if (vambiente() == 1)
    	exit(1);
    	else{
      	printf("Numero MAXMEDICOS: %d\n", estruturas.n_medicos);
      	printf("Numero MAXCLIENTES: %d\n", estruturas.n_clientes);
    	}
    	if(vfich("classificador") == 1){
      		printf("O ficheiro classificador não existe!\n");
      	exit(1);
    	}

    	pipe(fd_in);
 	pipe(fd_out);

    	pid = fork();

   	if(pid > 0){ //pai
     		close(fd_in[0]); //fecha extremidade de leitura do pipe
      		close(fd_out[1]); //fecha extremidade de escrita do pipe


	printf("\n---------------------------\n");
	printf("Para sair digite a tecla x\n");
	printf("---------------------------\n");


      	while(strcmp(input, "x") != 0){
        	printf("\nSintoma: ");
       		fgets(input,99,stdin);
		if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n'))		//substitui a ultima posicao do que foi escrito pelo espaco
        		input[strlen (input) - 1] = '\0';
       	 	if(strcmp(input, "x") != 0){
          	write(fd_in[1],input, strlen(input));		//envia o que foi escrito para o classificador
          	write(fd_in[1], "\n", 1);
          	read(fd_out[0], &classif, sizeof(classif) - 1);		//le o que foi enviado pelo classificador
     		sscanf(classif,"%s %d",diagnostico,&prio);
          	printf("Diagnostico: %s \nPrioridade: %d\n",diagnostico,prio);
        	}
      	}
      	printf("Fim de diagnostico\n");
    	}

    	else if(pid == 0){ //filho

	//filho que le
      	close(STDIN_FILENO);	//liberta posicao 0 (stdin)
      	dup(fd_in[0]);		//dupicla extremidade de leitura do pipe para pos 0
      	close(fd_in[0]);	//fecha extremidade de leitura porque ja foi duplicada
      	close(fd_in[1]);	//fecha extremidade de escrita do pipe

	//filho que escreve
      	close(STDOUT_FILENO);	//liberta posicao 1 (stdout)
     	dup(fd_out[1]);		//duplica extremidade de escrita do pipe para pos 1
      	close(fd_out[0]);	//fecha extremidade de leitura do pipe
      	close(fd_out[1]);	//fecha extremidade de escrita porque ja foi duplicada
      	execl("./classificador", "classificador", NULL);
    	}
    return 0;
}


//verificacao de leitura das variaveis de ambiente
int vambiente(){

    if(getenv("MAXMEDICOS") != NULL && getenv("MAXCLIENTES") != NULL){
    	estruturas.n_medicos = atoi(getenv("MAXMEDICOS"));
    	estruturas.n_clientes = atoi(getenv("MAXCLIENTES"));
    return 0;
    }
    else if (getenv("MAXMEDICOS") == NULL && getenv("MAXCLIENTES") == NULL)
    	printf("Nao existem variaveis de ambiente criadas\n");
    else if (getenv("MAXMEDICOS") == NULL)
    	printf("Variavel de ambiente MAXMEDICOS nao existe\n");
    else
    	printf("Variavel de ambiente MAXCLIENTES nao existe\n");
    return 1;
}

//verificacao de existencia de ficheiro
int vfich(const char *nome){
	FILE *ficheiro;
    	if ((ficheiro = fopen(nome, "r"))){
        	fclose(ficheiro);
        	return 0;
    	}
    return 1;
}

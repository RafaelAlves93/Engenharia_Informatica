#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcs.h"

void printFile(char* nome){
    FILE *f;
   paragem a;

    f = fopen(nome,"rb");
    if(f==NULL)return;
    while(fread(&a,sizeof(paragem),1,f)==1)
        printf("%s\t%d\n",a.nome,a.minutos);
    fclose(f);
}

int duracao(char* nome_ficheiro,char* origem,char* destino){
    FILE *f;
   paragem a;
   int durtotal = 0,

       flag     = 0;

    f = fopen(nome_ficheiro,"rb");
    if(f==NULL)return -1;

    while(fread(&a,sizeof(paragem),1,f)==1){
        if((flag == 0) && (strcmp(origem,a.nome) == 0)){
            flag = 1; //encontramos a origem
            durtotal -= a.minutos;
        }
        if((flag == 1) && strcmp(destino,a.nome) == 0){
            durtotal += a.minutos;
            flag = 2; //encontramos o destino depois da origem
        }
        if(flag == 1)durtotal += a.minutos; //adicionamos minutos so entre encontrarmos a origem e nao encontrarmos o destino
    }
    printf("flag == %d\n",flag);
    printf("durtotal == %d\n",durtotal);
    fclose(f);
    if(flag == 2){
        return durtotal;
    }else{
        return -1;
    }
}

/*

resolucao

int ligcaao(char*fnomeF,char*or,char*dest){
    FILE*f;
    paragem a;
    int flag = 0; Esta flag passa a 1 quando estava a zero, e so passa a 2 quando estava a 1
    f=fopen(nomeF,"rb");
    if(f==null)return -1;
    while(fread(&a,sizeof(paragem),1,f) == 1){
        if(flag == 0 && strcmp(a.nome,or) == 0)
            flag = 1;
        if(flag == 1 && strcmp(a.nome,dest) == 0)
            flag = 2;
    }
    flcose(f)
    if(flag==2)return 1;else return -1;
}


*/
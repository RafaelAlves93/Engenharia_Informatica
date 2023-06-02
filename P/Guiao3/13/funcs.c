#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "funcs.h"

#define N 100

void print_txt_to_stdout(char *filename){
    FILE *f;
    int i;
    int a[6];
    char nome[N];

    f = fopen(filename,"r");
    if(f==NULL){
        fclose(f);
        return;
    }

    while(feof(f)==0){
        fgets(nome,N,f);printf("%s",nome);
        for(i=0; i<6; i++){
            fscanf(f, "%d", &a[i]);
            printf("%d ", a[i]);
        }
        fgets(nome,N,f);
        puts("");
    }

    fclose(f);
}

void cpy_txt(char *dest,char *or){
    
}









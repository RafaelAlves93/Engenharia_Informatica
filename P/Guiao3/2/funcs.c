#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "funcs.h"


/*
void printFile(char* nome){
    FILE *f;
   paragem a;

    f = fopen(nome,"rb");
    if(f==NULL)return;
    while(fread(&a,sizeof(paragem),1,f)==1)
        printf("%s\t%d\n",a.nome,a.minutos);
    fclose(f);

}
*/

float return_file_average(char* filename){
    FILE *f;
    int a,
        sum = 0,
        i = 0;
    float average;

    f = fopen(filename,"rb");
    if(f==NULL){
        fclose(f);
        return 0;
    }
    while(fread(&a,sizeof(int),1,f)==1){
        sum += a;
        i++;
    }
    //printf("soma = %d\n",sum);
    average = (float)sum/(float)i;
    fclose(f);
    return average;

}

int* criaVetor(char *nomeFich, int *tam){
    FILE    *f;
    int     *intlist = NULL,
            *temp    = NULL;

    int     a,
            i;

    f = fopen(nomeFich,"rb");
    if(f==NULL){
        fclose(f);
        return NULL;
    }

    while(fread(&a,sizeof(int),1,f)==1){
        if(!(a%2)){
            temp = realloc(intlist,sizeof(int)*(*tam+1));
            if(temp != NULL){
                intlist = temp;
                intlist[*tam]=a;
                (*tam)++;
            }else{
                puts("Realloc Error");
            }
        }
    }
    fclose(f);

    puts("printing test...");
    for(i=0;i<(*tam);i++){
        printf("%d\n",intlist[i]);
    }

    return intlist;
}

void print_file(char* filename){
    FILE *f;
    int a;

    f = fopen(filename,"rb");
    if(f==NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        return;
    }
    while(fread(&a,sizeof(int),1,f)==1)
        printf("%d\n",a);
    fclose(f);
}

void save_below_and_above_average(char* filename,char* below,char* above){
    FILE    *f,
            *g,
            *h;
    int     a;
    float   average;

    average = return_file_average(filename);
    
    f = fopen(filename,"rb");
    g = fopen(below,"wb");
    h = fopen(above,"wb");
    if(f==NULL && g==NULL && h==NULL){
        fclose(f);
        fclose(g);
        fclose(h);
        return;
    }

    while(fread(&a,sizeof(int),1,f)==1){
        if(a<average){
            fwrite(&a,sizeof(int),1,g);
        }else{
            fwrite(&a,sizeof(int),1,h);
        }
    }
    fclose(f);
    fclose(g);
    fclose(h);
    return;
}

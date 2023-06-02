#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "funcs.h"

#define MAXLEN 100

/*
void printFile(char* nome){
    FILE *f;
   paragem a;

    f = fopen(nome,"rb");
    if(f==NULL){
            printf("Error: %s\n", strerror(errno));
            fclose(f);
            return;
        }

    while(fread(&a,sizeof(paragem),1,f)==1)
        printf("%s\t%d\n",a.nome,a.minutos);
    fclose(f);
}
*/

void save_strs_to_text_file(char *filename,char *str1,char *str2,char *str3,char *str4){
    FILE *f;

    f = fopen(filename,"w");
    if(f == NULL)
        printf("Error: %s\n", strerror(errno));
    else
        fprintf(f,"%s\n%s\n%s\n%s",str1,str2,str3,str4);
    fclose(f);
    return;
}

void copy_txt_file(char *original_name,char *copy_name){
    FILE    *f,
            *g;
    char    str1[MAXLEN],
            str2[MAXLEN],
            str3[MAXLEN],
            str4[MAXLEN];
    int     i=1;

    f = fopen(original_name,"r");
    g = fopen(copy_name,"w");
    if(f==NULL || g==NULL){
        printf("Error: %s\n", strerror(errno));
    }else{
        fgets(str1,MAXLEN,f);
        fgets(str2,MAXLEN,f);
        fgets(str3,MAXLEN,f);
        fgets(str4,MAXLEN,f);

        fprintf(g,"%d. ",i++);fputs(str1,g);
        fprintf(g,"%d. ",i++);fputs(str2,g);
        fprintf(g,"%d. ",i++);fputs(str3,g);
        fprintf(g,"%d. ",i);fputs(str4,g);
    }
    fclose(f);
    fclose(g);
    return;
}

//como é que posso ler uma string de um ficheiro de texto e saber o tamanho da string?
//ou melhor, se ela vai caber no espaço reservado?



/*
7. Escreva uma função que mostre no monitor uma determinada linha de um ficheiro de texto. O 
nome do ficheiro e o número da linha são passados como parâmetros da função. 
*/

void show_line_from_txtfile(char *filename, int lineno){
    FILE    *f;
    int     comp;
    char    buff[20];

    f = fopen(filename,"r");
    if(f==NULL)
        printf("Error: %s\n", strerror(errno));
    else
        while(fgets(buff,20,f) != NULL)
            if(buff[0] == (lineno+'0'))
                printf("%s",buff);
}


int isvowel(char v){
    switch (v)
    {
    case 'a':
        return 1;
    case 'e':
        return 1;
    case 'i':
        return 1;
    case 'o':
        return 1;
    case 'u':
        return 1;
    case 'A':
        return 1;
    case 'E':
        return 1;
    case 'I':
        return 1;
    case 'O':
        return 1;
    case 'U':
        return 1;
    default:
        return 0;
    }
}

void print_most_common_vowel(char *filename){
    FILE    *f;
    char    most_common_vowel,
            buffconcat[1000]="",
            buff[20]="";
    int     vcount = 0,
            vcountmax = 0,
            i,j,
            len;

    f = fopen(filename,"r");
    if(f==NULL){
        printf("Error: %s\n", strerror(errno));
    }else{
        while(fscanf(f,"%s",buff) == 1){
            strcat(buffconcat,buff);
        }
        len = strlen(buffconcat);
        most_common_vowel = buffconcat[0];
        for(i=0;i<len;i++){
            for(j=0;j<len;j++){
                if(buffconcat[i] == buffconcat[j]){
                    vcount++;
                }
            }
            if((vcount > vcountmax) && isvowel(buffconcat[i])){
                vcountmax = vcount;
                most_common_vowel = buffconcat[i];
            }
            vcount = 0;

        }
        printf("vogal mais comum = %c\n",most_common_vowel);
        //puts(buffconcat);
    }
}





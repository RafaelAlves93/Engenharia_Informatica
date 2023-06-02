#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "funcs.h"




void print_file(char *filename){
    FILE    *f;
    int     i,
            nalunos,
            nprovas,
            pesoprovas[4],
            notasaluno[4];
    char    buff[100];

    f = fopen(filename,"r");
    if(f==NULL){
        printf("Error: %s\n", strerror(errno));
    }else{
        fscanf(f,"Numero de alunos: %d\n",&nalunos);
        fscanf(f,"Numero de provas: %d\n",&nprovas);
        fscanf(f,"Peso das provas: %d %d %d %d\n",
            pesoprovas,
            pesoprovas+1,
            pesoprovas+2,
            pesoprovas+3
        );
        puts("");

        printf("Numero de alunos: %d\n",nalunos);
        printf("Numero de provas: %d\n",nprovas);
        printf("Peso das provas: %d %d %d %d\n",
            pesoprovas[0],
            pesoprovas[1],
            pesoprovas[2],
            pesoprovas[3]
        );
        fscanf(f,"\n");
        puts("");

        for(i=0;i<nalunos;i++){
            fscanf(f,"Aluno %*d: %d %d %d %d\n",
                notasaluno,
                notasaluno+1,
                notasaluno+2,
                notasaluno+3
            );
            printf("Aluno %d: %d %d %d %d\n",
                i+1,
                notasaluno[0],
                notasaluno[1],
                notasaluno[2],
                notasaluno[3]
            );
        }
    }
    fclose(f);
    return;
}

void output_student_grade(char *filename,char *outputname){
FILE        *f,
            *g;
    int     i,
            nalunos,
            nprovas;
    float   h=0.01,
            pesoprovas[4],
            notasaluno[4];
    char    buff[100];


    f = fopen(filename,"r");
    g = fopen(outputname,"w");

    if(f==NULL || g== NULL){
        printf("Error: %s\n", strerror(errno));
    }else{
        fscanf(f,"Numero de alunos: %d\n",&nalunos);
        fscanf(f,"Numero de provas: %d\n",&nprovas);
        fscanf(f,"Peso das provas: %f %f %f %f\n",
            pesoprovas,
            pesoprovas+1,
            pesoprovas+2,
            pesoprovas+3
        );

        fscanf(f,"\n");

        for(i=0;i<nalunos;i++){
            fscanf(f,"Aluno %*f: %f %f %f %f\n",
                notasaluno,
                notasaluno+1,
                notasaluno+2,
                notasaluno+3
            );
            fprintf(g,"Aluno %d: %.0f\n",
                i+1,
                round(
                    h*(
                        notasaluno[0]*pesoprovas[0]+
                        notasaluno[1]*pesoprovas[1]+
                        notasaluno[2]*pesoprovas[2]+
                        notasaluno[3]*pesoprovas[3]
                    )
                )
            );
        }
    }
    fclose(f);
    fclose(g);
    return;
}

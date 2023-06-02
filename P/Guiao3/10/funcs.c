#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "funcs.h"



void save_struct_to_bin(char *filename,cliente *clist,int total){
    FILE    *f;
    cliente a;
    int     i;

    f = fopen(filename,"wb");
    if(f == NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        return;
    }

    for(i=0;i<total;i++){
        fwrite(clist+i,sizeof(cliente),1,f);
    }
    
    fclose(f);
    return;
}

void print_bin_to_stdout(char *filename){
    FILE    *f;
    cliente a;
    int i,
        total;

    f = fopen(filename,"rb");
    if(f == NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        return;
    }

    //checks number of entries
    fseek(f, 0, SEEK_END);
    total = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);


    puts("");
    printf("Nome\t\t\tMorada\t\t\tNum Conta\tMontante\n");
    puts("-------------------------------------------------------------------");
    for(i=0;i<total;i++){
        fread(&a,sizeof(cliente),1,f);
        printf("%-20s\t%-20s\t%-3d\t\t%-3d\n",
               a.nome,
               a.morada,
               a.conta,
               a.montante 
        );
    }
    puts("");

    fclose(f);
    return;
}

void print_file_size_and_entrynun(char *filename){
    FILE         *f;
    long int     len;
    float        clientno;

    f = fopen(filename,"r");
    if(f==NULL){
        printf("Error: %s\n",strerror(errno));
        fclose(f);
        return;
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);

    clientno = (float)len / (float)sizeof(cliente);


    printf("Size of file = %ld bytes\n",len);
    printf("# of list entries = %.0f\n", clientno);

    fclose(f);
    return;
}

void print_bin_to_stdout_inverse(char *filename){
    FILE    *f;
    cliente *dyn = NULL,
            *temp;
    cliente a;
    int i,
        total;

    //opens file
    f = fopen(filename,"rb");
    if(f == NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        return;
    }

    //checks number of entries
    fseek(f, 0, SEEK_END);
    total = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);


    //uses fseek to read structs in reverse
    for(i=total-1;i>=0;i--){
        fseek(f,i*sizeof(cliente),SEEK_SET);
        fread(&a,sizeof(cliente),1,f);
        printf("%-20s\t%-20s\t%-3d\t\t%-3d\n",
               a.nome,
               a.morada,
               a.conta,
               a.montante 
        );
    }

    //creates a dynamic array to temporarily store the file
    //three times longer than the previous approach
    /*
    temp = realloc(dyn,sizeof(cliente)*total);
    if(temp==NULL){
        puts("Realloc Error");
        fclose(f);
        return;
    }
    dyn = temp;

    //copies from file and into the dynamic array
    for(i=0;i<total;i++){
        fread(&a,sizeof(cliente),1,f);
        dyn[i]=a;
    }

    //prints the dynamic array in reverse
    puts("");
    printf("Nome\t\t\tMorada\t\t\tNum Conta\tMontante\n");
    puts("-------------------------------------------------------------------");
    for(i=total-1;i>=0;i--){
        printf("%-20s\t%-20s\t%-3d\t\t%-3d\n",
               dyn[i].nome,
               dyn[i].morada,
               dyn[i].conta,
               dyn[i].montante 
        );
    }
    free(dyn);
    */

    puts("");

    fclose(f);
    return;
}

int transfere(char *filename, char *or, char *dest, int amount){
    FILE    *f;
    cliente a;

    f = fopen(filename,"rb+");
    if(f==NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        return 0;
    }
    //updates trannsfer origin account
    while(fread(&a,sizeof(cliente),1,f)==1){
        if(strcmp(a.nome,or)==0){ //finds account owner
            if(a.montante < amount)
                return 0;
            else
                a.montante-=amount;   //withdraws amount from buffer      
            fseek(f,-sizeof(cliente),SEEK_CUR); //has the file poiter go back one place
            fwrite(&a,sizeof(cliente),1,f); //has the buffer overwrite the struct ponted by f with the new value;
            break; //leaves loop when the updating is done; otherwise it will loop forever
        }
    }
    
    fseek(f,0,SEEK_SET); //takes f back to 0
    while(fread(&a,sizeof(cliente),1,f)==1){ //starts looping the file
        if(strcmp(a.nome,dest)==0){ //finds dest account
            a.montante+=amount;
            fseek(f,-sizeof(cliente),SEEK_CUR);
            fwrite(&a,sizeof(cliente),1,f);
            fclose(f);
            return 1;
        }
    }

    //lines to be executed if function fails
    fclose(f);
    return 0;
}

int remove_entry(char *filename,char *name){
    FILE    *f,
            *g;
    cliente a;
    int     i,
            total;

     //opens file
    f = fopen(filename,"rb");
    g = fopen("testfile.bin","wb");
    if(f==NULL || g==NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        fclose(g);
        return 0;
    }

    //checks number of entries
    fseek(f, 0, SEEK_END);
    total = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);

    //finds account to delete and skips it when writing the new one
    while(fread(&a,sizeof(cliente),1,f)==1){
        if(strcmp(a.nome,name)==0){ //finds account owner
            fseek(f,sizeof(cliente),SEEK_CUR);
        }
        fwrite(&a,sizeof(cliente),1,g);
    }

    fclose(f);
    fclose(g);
    //remove(filename); //supposed to delete the old file, but I prefer to keep it this way to make testing easier
    return 1;
}

int add_entry(char *filename,cliente novo){
    FILE    *f,
            *g;
    cliente a;
    int     total,
            flag=1;

    //opens file
    f = fopen(filename,"rb");
    g = fopen("testfile.bin","wb");
    if(f==NULL || g==NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        fclose(g);
        return 0;
    }

    //checks number of entries
    fseek(f, 0, SEEK_END);
    total = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);

    //finds where the new client will go,
    //moves a step forward and writes new entry
    
    while(fread(&a,sizeof(cliente),1,f)==1){
        if(strcmp(novo.nome,a.nome)<0 && flag){
            fwrite(&novo,sizeof(cliente),1,g);
            flag=0;
        }
        fwrite(&a,sizeof(cliente),1,g);
    }
    if(flag)fwrite(&novo,sizeof(cliente),1,g);

    fclose(f);
    fclose(g);
    return 1;
}

/*
int join_bin_files(char *filename1,char *filename2,char *newfile){
    FILE    *f,
            *g,
            *h;
    cliente *dyn = NULL,
            *temp = NULL;
    cliente a,
            b;
    int     total1,
            total2,
            repts=0,
            dynlen,
            i,
            j,
            u,
            flag;

    //opens file
    f = fopen(filename1,"rb");
    g = fopen(filename2,"rb");
    
    if(g==NULL || f==NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        fclose(g);
        return 0;
    }

    //checks number of entries in f
    fseek(f, 0, SEEK_END);
    total1 = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);

    //checks number of entries in g
    fseek(g, 0, SEEK_END);
    total2 = ftell(g) / sizeof(cliente);
    fseek(g,0,SEEK_SET);

    //counts number of common acounts
    while(fread(&b,sizeof(cliente),1,g)==1){
        while(fread(&a,sizeof(cliente),1,f)==1){
            if(strcmp(a.nome,b.nome)==0){
                repts++;
            }
        }
        fseek(f,0,SEEK_SET);
    }
    fseek(f,0,SEEK_SET);
    fseek(g,0,SEEK_SET);

    //determines size of the dynamic array
    dynlen = total1+total2-repts;

    //creates dynamic array
    dyn = malloc(sizeof(cliente)*dynlen);
    if(dyn==NULL){
        puts("Malloc Error");
        fclose(f);
        fclose(g);
        return 0;
    }

    //copies f to dyn
    fread(dyn,sizeof(cliente),total1,f);
    fclose(f);


    //reads g and puts each struct in dyn, keeping alphabetical order
    u=total1;
    while(fread(&b,sizeof(cliente),1,g)==1){
        for(i=0;i<u;i++){
            //printf("%s\n",dyn[i].nome);
            flag=1;
            if(strcmp(b.nome,dyn[i].nome)<0){
                u++;
                dyn[u-1]=dyn[u-2];
                for(j=u-1;j>i;j--){
                    dyn[j]=dyn[j-1];
                }
                dyn[i]=b;
                flag=0;
                break;
            }else if(strcmp(b.nome,dyn[i].nome)==0){
                u++;
                dyn[u-1]=dyn[u-2];
                dyn[i].montante += b.montante;
                flag=0;
                break;
            }
        }
        if(flag){
            u++;
            dyn[u-1]=dyn[i];
        }
        //test
        puts("oooooooooooooooooooooooooo");
        for(u=0;u<dynlen;u++){
            printf("%s\n",dyn[u].nome);
        }
        puts("000000000000000000000000000");
        printf("end loop--------------------\n");
        //testend
    }
    puts("here1---------------------------------------------------");

    puts("");
    for(i=0;i<dynlen;i++){
        printf("%-20s\t%-20s\t%-3d\t\t%-3d\n",
               dyn[i].nome,
               dyn[i].morada,
               dyn[i].conta,
               dyn[i].montante 
        );
    }
    puts("");

    h = fopen(newfile,"wb");
    if(h==NULL){
        fclose(h);
        return 0;
    }

    printf("dynlen = %d\n",dynlen);
    printf("%d\n",sizeof(cliente));



    printf("size of dyn = %ld\n",sizeof(cliente)*12);
    

    //copies dyn to the output file
    fwrite(dyn,sizeof(cliente),dynlen,h);
    
    puts("here2---------------------------------------------------");


    free(dyn);
    fclose(g);
    fclose(h);
    return 1;
}
*/

int join_bin_files(char *filename1,char *filename2,char *newfile){

    FILE    *f,
            *g,
            *h;
    cliente a,
            b;
    int     total1,
            total2;
    //opens files safely
    f = fopen(filename1,"rb");
    g = fopen(filename2,"rb");
    h = fopen(newfile,"wb");
    if(f==NULL || g==NULL || h==NULL){
        printf("Error: %s\n", strerror(errno));
        fclose(f);
        fclose(g);
        fclose(h);
        return 0;
    }

    //checks total entries in f
    fseek(f, 0, SEEK_END);
    total1 = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);

    //checks total of entries in g
    fseek(f, 0, SEEK_END);
    total2 = ftell(f) / sizeof(cliente);
    fseek(f,0,SEEK_SET);

    //reads from f and g at the same time and writes to h
    fread(&a,sizeof(cliente),1,f);
    fread(&b,sizeof(cliente),1,g);
    while(!(feof(f) && feof(g))){
        if(feof(f)){
            while(fread(&b,sizeof(cliente),1,g)==0){
                fwrite(&b,sizeof(cliente),1,h);
                break;
            }
        }else if(feof(g)){
            while(fread(&a,sizeof(cliente),1,f)==0){
                fwrite(&a,sizeof(cliente),1,h);
                break;
            }
        }else if(strcmp(a.nome,b.nome)<0){
            fwrite(&a,sizeof(cliente),1,h);
            fread(&a,sizeof(cliente),1,f);
        }else if(strcmp(a.nome,b.nome)>0){
            fwrite(&b,sizeof(cliente),1,h);
            fread(&b,sizeof(cliente),1,g);
        }else if(strcmp(a.nome,b.nome)==0){
            a.montante += b.montante;
            fwrite(&a,sizeof(cliente),1,h);
            fread(&b,sizeof(cliente),1,g);
            fread(&a,sizeof(cliente),1,f);
        }
    }
   
    fclose(f);
    fclose(g);
    fclose(h);
    return 1;
}


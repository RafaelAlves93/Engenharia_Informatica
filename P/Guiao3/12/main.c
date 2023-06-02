#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "funcs.h"

void main( int argc, char **argv )  {
   FILE  *f,
         *g;
   char  filename[100],
         name[100],
         nametemp[100];
   int   key[6],
         a[6];
   int   i,
         j,
         flag;

   for(i=2;i<8;i++)
      key[i-2]=atoi(argv[i]);

   f = fopen("apostas.txt","r");
   g = fopen("temp.txt","w");
   if(f==NULL||g==NULL){
      fclose(f);
      fclose(g);
      return;
   }

   while(feof(f)==0){
      flag=0;
      fgets(name,100,f);
      for(i=0; i<6; i++){
         fscanf(f, "%d", &a[i]);
         for(j=0;j<6;j++){
            if(key[j]==a[i]){
               flag++;
            }
         }
      }
      strcpy(nametemp,name);
      fgets(name,100,f);
      if(flag>2){
         fputs(nametemp,g);
         for(i=0; i<6; i++){
            fprintf(g,"%d ",a[i]);
         }
         fprintf(g,"\n");
      }
    }
   puts("done");
   fclose(f);
   fclose(g);
   remove("apostas.txt");
   rename("temp.txt","apostas.txt");
   return;
}
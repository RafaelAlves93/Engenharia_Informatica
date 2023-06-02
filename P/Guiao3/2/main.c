#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"


int main(){
    int* elist = NULL;
    int total=0;
    

    //print_file("valoresEx2.bin");

    puts("");
    
    //printf("media = %.2f\n",return_file_average("valoresEx2.bin"));

    //elist = criaVetor("valoresEx2.bin",&total);

    save_below_and_above_average("valoresEx2.bin","below_av.bin","above_av.bin");

    puts("");
    puts("Reading above_av.bin");
    print_file("above_av.bin");

    puts("");
    puts("Reading below_av.bin");
    print_file("below_av.bin");
}
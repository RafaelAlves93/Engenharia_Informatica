#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"



int main(){
    
    print_file("notas.txt");

    puts("");
    puts(".");
    puts("");

    output_student_grade("notas.txt","medias.txt");

}
#include <stdio.h>
#include <stdlib.h>


#include "funcs.h"

#define N 5


int main(){
    cliente clist[N] = {
        {"joao","rua do bife",123456,1000},
        {"ana","rua das batatas",222222,2},
        {"raquel","rua dos broculos",131313,4444},
        {"filipe","rua do arroz",464646,-5},
        {"samuel da massa","rua do molho",989898,9999},
    };
    
    save_structs("lista_clientes.bin",clist,N);

    //print_from_file("lista_clientes.bin");

    print_client_with_highest_amount("lista_clientes.bin");
}
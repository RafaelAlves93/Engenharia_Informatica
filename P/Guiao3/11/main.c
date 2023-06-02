#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"

void main(){
    date dat={20,12};

    puts("read binary");
    date_to_temp_bin(dat,"temperaturas_ex11.bin");
    puts("div------------------------------------------");
    puts("read text");
    date_to_temp_txt(dat,"temperaturas_ex11.txt");

}
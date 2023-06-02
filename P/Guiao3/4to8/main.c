#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"



int main(){
    char str1[20] = "Batatas";
    char str2[20] = "Bife";
    char str3[20] = "Salada";
    char str4[20] = "Agua";

    save_strs_to_text_file("strings.txt",str1,str2,str3,str4);

    copy_txt_file("strings.txt","copy.txt");

    //show_line_from_txtfile("copy.txt",3);

    print_most_common_vowel("copy.txt");


}
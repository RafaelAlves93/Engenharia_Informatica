#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"



int main(){
    
    cliente clist[10] = {
            {"ana","rua 1",123,11},
            {"beatriz","rua 2",987,-50},
            {"cesar","rua 3",614,9239},
            {"diogo","rua 5",112,888},
            {"elisa","rua 4",587,-1220},
            {"filipa","rua 6",483,2000},
            {"hermes","rua 7",323,78},
            {"inacia","rua 8",898,0},
            {"joao","rua 9",666,999},
            {"xavier","rua 10",100,2},
        },
            c2list[4] ={
            {"alexandre","rua b",152,83},
            {"elisa","rua 4",112,888},
            {"hermes","rua 7",323,78},
            {"joaquim","rua a",134,557}
        };
    cliente novo = {"ines","rua c",341,50};
    int total = 10,
        total2 = 4;

    save_struct_to_bin("data.bin",clist,total);
    save_struct_to_bin("data2.bin",c2list,total2);

    puts("");
    print_bin_to_stdout("data.bin");
    puts("");
    print_bin_to_stdout("data2.bin");
    puts("");

    join_bin_files("data.bin","data2.bin","newfile.bin");

    //remove_entry("data.bin","mario joao");

    //add_entry("data.bin",novo);

    //transfere("data.bin", "eufrazio", "alexandre",111);

    //print_file_size_and_entrynun("data.bin");
    //print_bin_to_stdout_inverse("data.bin");
    //print_bin_to_stdout("testfile.bin");
    print_bin_to_stdout("newfile.bin");
    puts("");

    
}
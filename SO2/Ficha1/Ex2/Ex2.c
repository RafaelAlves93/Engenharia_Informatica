#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h> 
#define MAX 256

int main(int argc, char* argv[]) {
    char result[MAX] = "Olá! Este programa ainda não representa UNICODE\n";
    printf("Frase:%s Tamanho:%d\n", result, strlen(result));
    getchar();
    return 0;
}
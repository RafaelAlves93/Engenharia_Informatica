#include <iostream>

using namespace std;

/*
int soma(){
    return 0;
}

int soma(int primeiro){
    return primeiro;
}

int soma(int primeiro, int segundo){
    return primeiro + segundo;
}

int soma(int primeiro, int segundo, int terceiro){
    return primeiro + segundo + terceiro;
}
 */

int soma(int a = 0, int b = 0, int c = 0){
    return a + b + c;
}

int main(){
    cout << "\n" << soma() << soma(1);
    cout << soma(1,2) << soma(1,2,3);
    return 0;
}
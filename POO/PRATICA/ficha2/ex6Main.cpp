#include <iostream>

#include "ex6Automovel.h"

using namespace std;

int main(){
    ex6Automovel automovel("matricula", "combustivel", "marca", "modelo", 5, 20);
    cout << automovel.getAsString();
    automovel.acelera();
    cout << automovel.getAsString();
    automovel.trava();
    cout << automovel.getAsString();
    return 0;
}
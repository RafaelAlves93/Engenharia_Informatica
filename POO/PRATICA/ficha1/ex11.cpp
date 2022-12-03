#include <iostream>
#include <sstream>

using namespace std;

namespace DataStore{
    bool dadosSaoValidos(string dadosDS){
        return dadosDS.length() >= 5 && dadosDS.length() <=10;
    }
}

namespace UserInterface{
    bool dadosSaoValidos(string dadosUI){

        return true;
    }
}

int main(){
    string dados
    cout << DataStore::dadosSaoValidos(dados);
    return 0;
}
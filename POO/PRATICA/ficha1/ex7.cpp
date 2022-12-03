#include <iostream>
#include <sstream>

using namespace std;

int main(){
    string nome, aux;
    int conheco = 0;

    cout << "Insira o nome completo" << endl;

    getline(cin, nome);

    istringstream ss(nome);
    while(ss >> aux){
        cout << aux << endl;
        if(aux == "silva"){
            conheco =  1;
        }
    }

    /*for(int i = 0; i < nome.length(); i++){
        if(nome[i] == ' '){
            cout << endl;
            aux.clear();
        }
        else{
            cout << nome[i];
            aux += tolower(nome[i]);
        }
        if(aux == "silva"){
            conheco = 1;
        }
    }*/
    if(conheco){
        cout << endl << "Conheco alguem com esse nome" << endl;
    }
    return 0;
}

/*
 * isstringstream
 * -Permite transformar uma string num stream, facilitando assim a sua extração em componentes individuais.
 * -É possível extrair uma string do stream e inseri-la numa variável atraves do operador >>
 * -#include <sstream>
 * */
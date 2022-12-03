#include <iostream>

using namespace std;

int main(){
    string palavra, contrario;
    do{
        contrario = "";
        cout << "Palavra: " << endl;
        cin >> palavra;

        if(palavra == "fim") break;

        int j = palavra.length();
        for(int i = 0; i < palavra.length(); i++) {
            cout << palavra[i] << endl;
            contrario[--j]+=palavra[i];
            cout << contrario[j];
        }

        cout << "length" << contrario.length();

        for(int i = 0; i < contrario.length(); i++){
            cout << contrario[i];
        }

        cout << "palavra ao contrário: " << contrario << endl;

        if(palavra == contrario){
            cout << "palíndromo" << endl;
        }
    }while(palavra != "fim");
    return 0;
}
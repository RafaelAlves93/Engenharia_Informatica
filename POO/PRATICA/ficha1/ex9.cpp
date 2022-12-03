#include <iostream>
#include <sstream>
#include <limits>

using namespace std;
string extenso[11] = {"zero", "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};

string converteIntParaString(int numero){
    if(numero <= 0 || numero > 10){
        return "Numero invalido";
    } else{
        return extenso[numero-1];
    }
}

int converteStringParaInt(string numero){
    for(int i = 0; i < 10; i++){
        if(extenso[i] == numero) return i+1;
    }
    return -1;
}

int main(){
    string input;
    while(true){
        cout << "Input: ";
        cin >> input;

        istringstream ss(input);
        int numero;
        if(ss >> numero){
            cout << converteIntParaString(numero);
        } else{
            if(input == "fim") break;
            cout << converteStringParaInt(input);
        }

        cout << endl << "Carregue no enter...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    };
    /*
    string extenso[11] = {"zero", "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};
    int decimal[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool aux;

    string texto;
    int number;

    do{
        aux = false;
        cout << endl << "Insira um numero" << endl;
        cin >> texto;
        if(texto == "fim") break;

        for(int i = 0; i < 11; i++ && !aux){
            if(extenso[i] == texto){
                cout << endl << decimal[i];
                aux = true;
            }
        }

        if (!aux) number = stoi(texto);

        for(int i = 0; i < 11; i++ && !aux){
            if(decimal[i] == number){
                cout << endl << extenso[i];
                aux = true;
            }
        }
    }while(texto != "fim");
*/
    return 0;
}
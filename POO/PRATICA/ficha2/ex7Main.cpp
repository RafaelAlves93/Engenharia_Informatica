#include <iostream>
#include "ex7MSG.h"

/*void teste(){
    ex7MSG aux('y');
}*/

/*void teste(ex7MSG mensagem){
    ex7MSG aux('z');
}*/

/*void teste(ex7MSG &mensagem){
    ex7MSG aux('w');
}*/

/*ex7MSG teste(){
    ex7MSG aux('k');
    return aux;
}*/

ex7MSG& teste(){
    //ex7MSG aux('k');
    static ex7MSG aux('k');
    return aux;
}

int main(){
    ex7MSG msgA('a'), msgB;
    ex7MSG msgD = msgB;
    /*ex7MSG &msgC = msgB;
    msgA = msgB;
    ex7MSG msgMatriz[2]={'e', 'f'};*/
    //ex7MSG msgTeste = teste();
    //teste(msgA);
    ex7MSG msgTesteRef = teste();
    cin.get();
    return 0;
}
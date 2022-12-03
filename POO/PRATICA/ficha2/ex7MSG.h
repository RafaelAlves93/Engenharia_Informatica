#ifndef FICHA2_EX7MSG_H
#define FICHA2_EX7MSG_H

#include <iostream>

using namespace std;

class ex7MSG {
public:
    ex7MSG(char letra = 'X');
    ex7MSG(const ex7MSG & z); //construtor por copia usado por variaveis construidas por copia
    ~ex7MSG();

    string getAsString() const;

private:
    //ex7MSG(const ex7MSG & z){};
    char letra;
    int numMsg;
    static int numero;
};


#endif //FICHA2_EX7MSG_H
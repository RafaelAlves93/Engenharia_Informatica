#ifndef FICHA2_EX6AUTOMOVEL_H
#define FICHA2_EX6AUTOMOVEL_H

#include <iostream>

using namespace std;

class ex6Automovel {
public:
    ex6Automovel(const string &matricula, const string &combustivel, const string &marca, const string &modelo, const int &ano, const int &velocidade);

    static bool validaMatricula(const string &matricula);

    const string &getMatricula() const;
    void setMatricula(const string &matricula);

    const string &getCombustivel() const;
    void setCombustivel(const string &combustivel);

    const string &getMarca() const;
    void setMarca(const string &marca);

    const string &getModelo() const;
    void setModelo(const string &modelo);

    int getAno() const;

    void setAno(int ano);

    void acelera();
    void trava();

    string getAsString() const;

private:
    int velocidadeAtual, ano;
    string matricula, combustivel, marca, modelo;
};

#endif //FICHA2_EX6AUTOMOVEL_H
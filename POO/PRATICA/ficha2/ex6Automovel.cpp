#include "ex6Automovel.h"

#include <iostream>
#include <sstream>

/*ex6Automovel::ex6Automovel(const string &matricula, const string &combustivel, const string &marca, const string &modelo, const int &ano, const int &velocidade) {
    this->matricula = matricula;
    this->combustivel = combustivel;
    this->marca = marca;
    this->modelo = modelo;
    this->ano = ano;
    this->velocidadeAtual = velocidade;
}*/

ex6Automovel::ex6Automovel(const string &matricula, const string &combustivel, const string &marca,
                           const string &modelo, const int &ano, const int &velocidade) : matricula(matricula), combustivel(combustivel), marca(marca),
                           modelo(modelo), ano(ano), velocidadeAtual(velocidade){}

//getter
const string &ex6Automovel::getMatricula() const {
    return matricula;
}

const string &ex6Automovel::getCombustivel() const {
    return combustivel;
}

const string &ex6Automovel::getMarca() const {
    return marca;
}

const string &ex6Automovel::getModelo() const {
    return modelo;
}

int ex6Automovel::getAno() const {
    return ano;
}

//setter
void ex6Automovel::setMatricula(const string &matricula) {
    this->matricula = matricula;
}

void ex6Automovel::setCombustivel(const string &combustivel) {
    this->combustivel = combustivel;
}

void ex6Automovel::setMarca(const string &marca) {
    this->marca = marca;
}

void ex6Automovel::setModelo(const string &modelo) {
    this->modelo = modelo;
}

void ex6Automovel::setAno(int ano) {
    this->ano = ano;
}


void ex6Automovel::acelera() {
    velocidadeAtual++;
}

void ex6Automovel::trava() {
    if(velocidadeAtual>0)
        velocidadeAtual--;
}

string ex6Automovel::getAsString() const {
    ostringstream os;
    os << "***Automovel***" << endl;
    os << "Matricula: " << matricula << endl;
    os << "Combustivel: " << combustivel << endl;
    os << "Marca: " << marca << endl;
    os << "Modelo: " << modelo << endl;
    os << "Velocidade: " << velocidadeAtual << endl;
    os << "Velocidade: " << velocidadeAtual << "." << endl;
    return os.str();
}
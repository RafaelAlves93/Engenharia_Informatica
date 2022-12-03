#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#include "Automovel.h"

int Automovel::nAutomoveisCriados = 0;

Automovel::Automovel( const Automovel & ob){
	cout << "Construtor por copia\n";
	matricula = ob.matricula;
	marca = ob.marca;
	modelo = ob.modelo;
	ano = ob.ano;
	++nAutomoveisCriados; // tambem por copia
}
Automovel::Automovel(string matricula1, string marca1, string modelo1, int ano1){
	cout << "Construtor com parametros\n";
	matricula = matricula1;
	marca = marca1;
	modelo = modelo1;
	ano = ano1;
	++nAutomoveisCriados;
}
Automovel::~Automovel(){
	cout << "Destruindo\n";
}

string Automovel::getMatricula()const{
	return matricula;
}
string Automovel::getMarca()const{
	return marca;
}
string Automovel::getModelo()const{
	return modelo;
}
int Automovel::getAno()const{
	return ano;
}

void Automovel::setMatricula(string matricula1){
	matricula = matricula1;
}
void Automovel::setMarca( string marca1){
	marca = marca1;
}
void Automovel::setModelo(string modelo1){
	modelo = modelo1;
}
void Automovel::setAno( int ano1){
	ano = ano1;
}

string Automovel::getAsString()const{
	ostringstream oss;
	oss << "Automovel: "
		 << matricula  << "   "  << marca 
		 << "   " << modelo << "   " << ano;
	return oss.str();
}

Automovel & Automovel::operator=( const Automovel & ob){
	if(this != &ob){
		cout << "Operador atribuicao\n";
		// a matricula nao se altera no objecto destino da atribuicao
		marca = ob.marca;
		modelo = ob.modelo;
		ano = ob.ano;
	}
	return *this;
}
//definicao do operador binario << como funcao global
ostream & operator<<( ostream & saida, const Automovel & ob){
	saida << ob.getAsString() << endl;
	return saida;
}
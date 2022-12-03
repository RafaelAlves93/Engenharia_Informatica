#include <sstream>
#include <iostream>
#include <cmath>
#include "Fraccao.h"

Fraccao::Fraccao( int n , int d ):num(n){
	setDenom(d);
//	cout << "Fraccao( int n , int d ) " << getAsString() << endl;
}
void Fraccao::setDenom( int d){
	if ( d > 0){
		denom = d;
	}else if (d == 0) {
		num = 0;
		denom = 1;
	} else { // d < 0
		num = -num;
		denom = -d;
	}
	simplifica();
}

void Fraccao::simplifica(){
	int sinal = num >= 0 ? 1 : -1;// guarda o sinal da fraccao
	num = abs(num);
	// calcula o m. d. c. de num e denom, n�o negativos
	int a = num, b = denom;
	while (b){
		int aux = b;
		b = a % b;
		a = aux;
	}
	// a : o m. d. c. de num e denom, calculado pelo algoritmo de Euclides
	num = num / a * sinal;
	denom = denom / a;
}
string Fraccao::getAsString()const{
	ostringstream oss;
	oss << "(" << num << " / " << denom << ")" ;
	return oss.str();
}
Fraccao & Fraccao::operator*=( const Fraccao & ob){
		num = num * ob.num;
		denom = denom * ob.denom;
//		*this = Fraccao(num * ob.num, denom * ob.denom);
//                simplifica();
		return *this;
}

Fraccao & Fraccao::operator++(){
		num += denom; // a fraccao aumenta uma unidade
		simplifica();
		return *this; // retorna o objecto depois de incrementado
}

Fraccao Fraccao::operator++(int n){
		Fraccao aux = *this; // grava para esta variavel auxiliar o objecto antes de incrementar
		num += denom; // a fraccao aumenta uma unidade
		simplifica();
		return aux;// nao pode ser por referencia, retorna-se uma variavel local
}




//definicao do operador binario + como funcao global
Fraccao operator+(const Fraccao & a, const Fraccao & b){
	Fraccao soma( a.getNum() * b.getDenom() + b.getNum() * a.getDenom(),
		a.getDenom() * b.getDenom() );
        soma.simplifica();
	return soma;
}
//definicao do operador binario - como funcao global
Fraccao operator-(const Fraccao & a, const Fraccao & b){
	Fraccao sub( a.getNum() * b.getDenom() - b.getNum() * a.getDenom(),
		a.getDenom() * b.getDenom() );
        sub.simplifica();
	return sub;
}
//definicao do operador binario * como funcao membro
//Fraccao Fraccao::operator*( const Fraccao & b){
//	cout << "Fraccao::operator*( const Fraccao & b) \n";
//	Fraccao aux( num * b.num, denom * b.denom );
//        aux.simplifica();
//    
//        return aux;
//        
//}
//definicao do operador binario * como funcao global
Fraccao operator*(const Fraccao & a, const Fraccao & b){
	cout << "operator*(const Fraccao & a, const Fraccao & b) \n";
	Fraccao aux( a.getNum() * b.getNum(),a.getDenom() * b.getDenom() );
        aux.simplifica();
	return aux;
}
//definicao do operador binario / como funcao global
Fraccao operator/(const Fraccao & a, const Fraccao & b){
	Fraccao aux( a.getNum() * b.getDenom() ,b.getNum() * a.getDenom());
        aux.simplifica();
	return aux;
}

//definicao do operador binario == como funcao global
bool operator==(const Fraccao & a, const Fraccao & b){
	return (a.getNum() * b.getDenom() == b.getNum() * a.getDenom());
}

//definicao do operador binario != como funcao global
bool operator!=(const Fraccao & a, const Fraccao & b){
	return (a.getNum() * b.getDenom() != b.getNum() * a.getDenom());
}
//definicao do operador binario << como funcao global
ostream & operator<<( ostream & saida, const Fraccao & ob){
	saida << ob.getAsString();

	return saida;
}

//definicao do operador binario >> como funcao global
istream & operator>>( istream & entrada, Fraccao & ob){
    int num, denom;
    entrada >> num >> denom;
    ob.setNum(num);
    ob.setDenom(denom);
    return entrada;
}
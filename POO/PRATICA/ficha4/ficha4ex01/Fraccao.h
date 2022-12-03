#ifndef FRACCAO_H
#define FRACCAO_H

#include <iostream>
#include <string>

using namespace std;

class Fraccao{
	int num;	// numerador
	int denom;	// denominador
public:
	explicit Fraccao( int n = 0, int d = 1);
	// funcoes get
	int getNum()const{ return num; }
	int getDenom()const{ return denom; }

	// funcoes set
	void setNum( int n ){ num = n; }
	void setDenom( int d );

	void simplifica();

	string getAsString()const;

	//declaracao do operador binario *= como membro da classe Fraccao
	Fraccao & operator*=( const Fraccao & ob);

//	Fraccao operator*( const Fraccao & y);  // operador * membro

	Fraccao & operator++(); // operador incremento pre-fixado
	Fraccao operator++(int n); // operador incremento pos-fixado, tem o parametro int para se distinguir do pre fixado

        // operador de conversao
	explicit operator int()const{ return num/denom; }

};


Fraccao operator+(const Fraccao & x, const Fraccao & y);
Fraccao operator-(const Fraccao & x, const Fraccao & y);


Fraccao operator*(const Fraccao & x, const Fraccao & y);
Fraccao operator/(const Fraccao & x, const Fraccao & y);

bool operator==(const Fraccao & x, const Fraccao & y);
bool operator!=(const Fraccao & x, const Fraccao & y);

//declaracao do operador binario << como funcao global
ostream & operator<<( ostream & saida, const Fraccao & ob);

//declaracao do operador binario >> como funcao global
istream & operator>>( istream & entrada, Fraccao & ob);


#endif
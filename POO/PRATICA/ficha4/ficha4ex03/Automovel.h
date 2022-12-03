#ifndef AUTOMOVEL_H
#define AUTOMOVEL_H


#include <string>

using namespace std;

class Automovel {
	static int nAutomoveisCriados;
	string matricula;
	string marca;
	string modelo;
	int ano;

public:
	Automovel( const Automovel & ob);
	Automovel(string matricula, string marca, string modelo, int ano);
	~Automovel();

	string getMatricula()const;
	string getMarca()const;
	string getModelo()const;
	int getAno()const;

	static int getNAutomoveisCriados(){ return nAutomoveisCriados; }

	void setMatricula( string matricula);	
	void setMarca(string marca);
	void setModelo( string modelo);
	void setAno( int ano);

	string getAsString()const;

	Automovel & operator=( const Automovel & ob);
};

ostream & operator<<( ostream & saida, const Automovel & ob);
#endif

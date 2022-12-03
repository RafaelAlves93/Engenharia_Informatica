#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

#include "Automovel.h"

void f(Automovel  x);

int main(){
	Automovel a1("11-11-AA","OPEL", "OMEGA", 2010);
	Automovel a2("22-22-BB","FIAT", "PUNTO", 2011);

	Automovel a3 = a1;

//	a1 = a2;
	f(a1);
//	cout << "a1: " << a1 << endl << "a2: " << a2 << endl;

	cout << " Foram criados ao todo " << Automovel::getNAutomoveisCriados() << " automoveis\n";
	
	//int n = 2;
	//ostringstream oss;
	//oss<<"A"<<setw(2)<<setfill('0')<<n;
	//cout<<oss.str()<<endl;


}

void f(Automovel  x){
	cout << x << endl;
}
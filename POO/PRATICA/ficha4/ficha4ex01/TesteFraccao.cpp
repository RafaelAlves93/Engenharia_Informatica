#include <iostream>

using namespace std;

#include "Fraccao.h"


//int main(){
//	Fraccao a(1,2), b(3);
//////	const Fraccao c(3,4);

//        c.getNum();
//	cout << c.getAsString();
////	c.setNum(4);  // a)

     
//	a = b*c;  // b)
//        cout << b.getAsString() << "  * " 
//	     << c.getAsString() << "  = "
//            << a.getAsString() << endl;
//          cout << "________________\n";
//       a= b * Fraccao(5);
//       a= Fraccao(5) * c;
//	// membro   a = b.operator*(c)
//	//global  operator*(b,c)

//	cout << (a * b * c).getAsString() << endl;  // c) 
//
//	a = b * 4;  // d) // a = b * Fraccao(4)
//	a = b * Fraccao(4);  // e)
//	a = 4 * b;  // f)
//
	//cout << a.getAsString() << endl;

	
//        cout << a << b << c;  // g) h) i)

//	a *= b;  // p2


//	cout << a;  // j)
//	a *= b *= c;
//	cout << a;  // k)



//	Fraccao a(1,2),b(2,3),c(3,4);
//	cout << ((a *= b) *= c) << endl;
//	cout << a;		// l)

//	cout << ++a << endl;
//	cout << a;

//	cout << a++ << endl;
//	cout << a;
	//++c;c++; erro    // m)
//}

//void func(Fraccao f) {
//	cout << f; // aparece 2
//}


void func(int n) {
	cout << n << endl; // aparece 2
}
int main() {
	const Fraccao f(7,3); 
//        Fraccao a, b, c; 
//	func(f); // passado automaticamente o valor inteiro de 7/3
        func(static_cast<int>(f));
//        a = 4+c;
//	 arredondado para baixo
//	func(Fraccao(4));
//        func(4);
	return 0;
}


//n) precisa de ser feito o operador int que converte Fraccao em int, membro da classe Fraccao
// acrescenta-se a funcao membro: operator int()const{ return num/denom; }

//int main(){  
////o)
// //acrescenta-se o operador global:	bool operator==(const Fraccao & x, const Fraccao & y);
//	Fraccao a(1,2), b(3);
//	const Fraccao c(2,4);
//
//	if(a == b){
//		cout << "iguais\n";
//	}else {
//		cout << "diferentes\n";
//	}
//	if(a == c){
//		cout << "iguais\n";
//	}else {
//		cout << "diferentes\n";
//	}
//        
//        cin >> a;
//        cout << a << endl;
//}

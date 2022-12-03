#include <iostream>
//#include "AgendaVector.h"
#include "AgendaSet.h"
//#include "AgendaMap.h"

int main() {
    AgendaSet a("a");

    for (int i = 0; i < 5; ++i) {
        a.adiciona("T" + to_string(i), i);
    }

    try {
        a.adiciona("T1", 2);
    } catch (string nome) {
        cout << "Impossivel adicionar contacto com o nome " << nome << endl;
    }

    try {
        cout << "Encontrei numero " << a.procura("T1") << endl;
    } catch (string nome) {
        cout << "Impossivel encontrar contacto com o nome " << nome << endl;
    }

    cout << "Lista" << endl;
    cout << a.obtemLista() << endl;

    a.atualizaNumero("T1", 10);
    cout << "Atualiza" << endl;
    cout << a.obtemLista() << endl;

    a.elimina("T1");
    a.eliminaOsQueTem("4");
    cout << "Elimina" << endl;
    cout << a.obtemLista() << endl;

    cout << "Lista desde" << endl;
    cout << a.obtemListaDestes(2, 5) << endl;

    cout << "Ordena " << endl;
    a.adiciona("T1", 3);
//    a.ordena();
    cout << a.obtemLista() << endl;

    cout << "Elimina desde" << endl;
    a.eliminaOsQueTem("T");
    cout << a.obtemLista() << endl;

    return 0;
}

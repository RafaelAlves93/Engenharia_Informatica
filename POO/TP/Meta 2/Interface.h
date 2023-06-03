
#ifndef META1_INTERFACE_H
#define META1_INTERFACE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Reserva.h"
#include "Animais.h"
#include "Alimentos.h"
#include <windows.h>
#include <unistd.h>


class Interface {

public:
    static void lerinput(istringstream& iss, Reserva * r);
    static void lerconstantes(istringstream &iss, Reserva * r);
    static void ui();
};


#endif //META1_INTERFACE_H

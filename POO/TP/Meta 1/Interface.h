//
// Created by rafaa on 25/11/2022.
//

#ifndef META1_INTERFACE_H
#define META1_INTERFACE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Reserva.h"
#include "Animais.h"
#include "Alimentos.h"
using namespace std;

class Interface {

public:
    void ui();
    void lerinput(istringstream& iss, Reserva * r);
    void lerconstantes(istringstream &iss);
};

#endif //META1_INTERFACE_H

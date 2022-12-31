//
// Created by rafaa on 25/11/2022.
//

#include "Reserva.h"

Reserva::Reserva(int n_linhas, int n_colunas) {
    linhas=n_linhas;
    colunas=n_colunas;
}

void Reserva::gerar() {

    Animais a1('C',3,1);
    Animais a2('O',2,2);
    Animais a3('M',1,3);
    animais.push_back(a1);
    animais.push_back(a2);
    animais.push_back(a3);

    Alimentos a4('r',5,5);
    Alimentos a5('b',6,7);
    Alimentos a6('t',8,9);
    alimentos.push_back(a4);
    alimentos.push_back(a5);
    alimentos.push_back(a6);
}

void Reserva::atualizaReservaVisivel() {
    // 10x10
    for (int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            areaVisivel[i][j] = ' ';
        }
    }

    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if(i->getlinha()>=xvisivel && i->getcoluna()>=yvisivel && i->getlinha()<=xvisivel+9 && i->getcoluna()<=yvisivel+9)
        {
            areaVisivel[i->getlinha()-xvisivel][i->getcoluna()-yvisivel] = i->gettipo();
        }
    }

    for (auto i = animais.begin(); i < animais.end(); ++i) {
        if(i->getlinha()>=xvisivel && i->getcoluna()>=yvisivel && i->getlinha()<=xvisivel+9 && i->getcoluna()<=yvisivel+9)
        {
            areaVisivel[i->getlinha()-xvisivel][i->getcoluna()-yvisivel] = i->getespecie();
        }
    }
}

void Reserva::MostrarZonas(){

    // 10x10
    cout << "\nRESERVA:" << endl;
    cout << "-----------------------------------------";
    cout << '\n';
    for (int i = 0; i < 10; ++i)
    {
        cout << "| " ;
        for(int j = 0; j < 10; ++j)
        {
            cout << areaVisivel[i][j];
            cout << " | " ;
        }
        cout << '\n';
        cout << "-----------------------------------------";
        cout << '\n';
    }
    cout << endl;
}

void Reserva::verQuadrado(int l, int c) {       //informações do comando see
    l = l + xvisivel;
    c = c + yvisivel;
    int flagani=0, flagali=0;
    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if(i->getlinha() == l && i->getcoluna() == c && !i->getconsumido())
        {
            flagali++;
            i->imprimeInfo();
        }
    }

    for (auto i = animais.begin(); i < animais.end(); ++i) {
        if(i->getlinha() == l && i->getcoluna() == c)
        {
            flagani++;
            i->imprimeInfoAnimais();
        }
    }
    if(flagali ==0  && flagani == 0) {
        cout << "Nao existem alimentos ou animais neste posicao!" << endl;
    }
}
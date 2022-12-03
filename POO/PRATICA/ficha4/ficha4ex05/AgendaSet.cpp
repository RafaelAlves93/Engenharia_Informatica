#include "AgendaSet.h"

AgendaSet::AgendaSet(const string &nome) : nome(nome) {}

void AgendaSet::adiciona(const string &nome, int tel)  {
    Amigo tmp(nome,tel);
    //TODO: 1
    auto pair = amigos.insert(tmp);
    if (!pair.second) {
        throw nome;
    }
}

int AgendaSet::procura(const string &nome) {
    Amigo tmp(nome,0);
    //TODO: 2
    set<Amigo>::iterator it;
    it = find(amigos.begin(), amigos.end(), tmp);
    if (it!=amigos.end())
        return it->getTel();
    else
        throw nome;
}

void AgendaSet::elimina(const string &nome) {
    Amigo tmp(nome,0);
    //TODO: 3
    amigos.erase(tmp);
}

void AgendaSet::eliminaOsQueTem(const string &nome) {
    //TODO: 4
    erase_if(amigos, [&] (const Amigo &a) {
        return a.getNome().find(nome) != string::npos;
    });
}

string AgendaSet::obtemLista() {
    string aux = "AgendaSet " + nome + "\n";
    for_each(amigos.begin(), amigos.end(), [&aux] (const Amigo &a) {
        aux += a.getNome() + "\n";
    });
    //for (auto x : amigos)
    // aux += x.getDesc() += "\n";
    return aux;
}

string AgendaSet::obtemListaDestes(int min, int max) {
    string aux;                                     // default capture: por ref p/ min,max, aux
    for_each(amigos.begin(), amigos.end(), [&] (const Amigo &a) {
        if (a.getTel()>= min && a.getTel() <= max)
            aux += a.getNome() + "\n";
    });

    //for (auto a : amigos)
    //   if (a.getTel() >= min && a.getTel() >= max)
    //      aux += x.getDesc() += "\n";
    return aux;
}

void AgendaSet::atualizaNumero(const string &nome, int novoNumero) {
    Amigo tmp(nome,0);
    auto it = find(amigos.begin(), amigos.end(), tmp);
    //TODO: 5
    if (it != amigos.end()) {
        amigos.erase(it);
        amigos.insert({nome, novoNumero});
    }
}



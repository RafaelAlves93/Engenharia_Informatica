#include "AgendaMap.h"

AgendaMap::AgendaMap(const string &nome) : nome(nome) {}

void AgendaMap::adiciona(const string &nome, int tel)  {
    Amigo tmp(nome,tel);
    //TODO: 1
    auto pair = amigos.insert({nome, tmp});
    if (!pair.second) {
        throw nome;
    }
}

int AgendaMap::procura(const string &nome) {
    Amigo tmp(nome,0);
    map<string, Amigo>::iterator it;
    //TODO: 2
    it =  amigos.find(nome);
    if (it!=amigos.end())
        return it->second.getTel();
    else
        throw nome;
}

void AgendaMap::elimina(const string &nome) {
    amigos.erase(nome);
}

void AgendaMap::eliminaOsQueTem(const string &nome) {
    //TODO: 3
    erase_if(amigos, [&] (const auto &a) {
        a.first;
        return a.second.getNome().find(nome) != string::npos;
    });
}

string AgendaMap::obtemLista() {
    string aux = "AgendaMap " + nome + "\n";
    //TODO: 4
    for_each(amigos.begin(), amigos.end(), [&aux] (const auto &kv) {
        aux += kv.second.getNome() + "\n";
    });

    //TODO: 5
//    for (const auto& kv : amigos)
//     aux += kv.second.getDesc() += "\n";
    return aux;
}

string AgendaMap::obtemListaDestes(int min, int max) {
    string aux;                                     // default capture: por ref p/ min,max, aux
    //TODO: 6
    for_each(amigos.begin(), amigos.end(), [&] (const auto &kv) {
        if (kv.second.getTel()>= min && kv.second.getTel() <= max)
            aux += kv.second.getNome() + "\n";
    });

    //TODO: 7
    for (const auto& [key, value] : amigos)
       if (value.getTel() >= min && value.getTel() >= max)
          aux += value.getDesc() += "\n";
    return aux;
}

void AgendaMap::atualizaNumero(const string &nome, int novoNumero) {
    Amigo tmp(nome,0);
    auto it = amigos.find(nome);
    if (it != amigos.end()) {
        amigos.erase(it);
        //TODO: 8
        amigos.insert_or_assign(nome, Amigo(nome, novoNumero));
    }
}



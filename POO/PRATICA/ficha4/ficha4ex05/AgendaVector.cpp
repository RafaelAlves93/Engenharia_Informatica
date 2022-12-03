#include "AgendaVector.h"

AgendaVector::AgendaVector(const string &nome) : nome(nome) {}

void AgendaVector::adiciona(const string &nome, int tel)  {
    Amigo tmp(nome,tel);
    auto it = find(amigos.begin(), amigos.end(), tmp);
    if (it==amigos.end()) {
        amigos.push_back(tmp);
    } else {
        throw nome;
    }
}

int AgendaVector::procura(const string &nome) {
    Amigo tmp(nome,0);
    vector<Amigo>::iterator it;
    it = find(amigos.begin(), amigos.end(), tmp);
    if (it!=amigos.end())
        return it->getTel();
    else
        throw nome;
}

void AgendaVector::elimina(const string &nome) {
    Amigo tmp(nome,0);
    auto it = remove(amigos.begin(), amigos.end(), tmp); // requer op== por nome em Amigo
    amigos.erase(it, amigos.end());
}

void AgendaVector::eliminaOsQueTem(const string &nome) {
    auto it = remove_if(amigos.begin(), amigos.end(), [&] (const Amigo &a) {
        return a.getNome().find(nome) != string::npos;
    });
//  auto it = remove_if(amigos.begin(), amigos.end(),AmigoDiscriminator(nome));
    amigos.erase(it, amigos.end());
}

string AgendaVector::obtemLista() {
    string aux = "AgendaVector " + nome + "\n";
    for_each(amigos.begin(), amigos.end(), [&aux] (const Amigo &a) {
        aux += a.getNome() + "\n";
    });
//    for (auto x : amigos)
//     aux += x.getDesc() += "\n";
    return aux;
}

string AgendaVector::obtemListaDestes(int min, int max) {
    string aux;                                     // default capture: por ref p/ min,max, aux
    for_each(amigos.begin(), amigos.end(), [&] (const Amigo &a) {
        if (a.getTel()>= min && a.getTel() <= max)
            aux += a.getNome() + "\n";
    });

//    for (auto a : amigos)
//       if (a.getTel() >= min && a.getTel() >= max)
//          aux += a.getDesc() += "\n";
    return aux;
}

void AgendaVector::atualizaNumero(const string &nome, int novoNumero) {
    Amigo tmp(nome,0);
    replace(amigos.begin(), amigos.end(), tmp, {nome, novoNumero});
}








//TODO: Não necessário para set e maps porque já estão ordenados
void AgendaVector::ordena() {
    //TODO: Ordena por nome através de op< em Amigo
    sort(amigos.begin(), amigos.end());
    //TODO: Ordena por telefone através lambda
    sort(amigos.begin(), amigos.end(), [&] (const Amigo &a, const Amigo & b) {
        return a.getTel() < b.getTel();
    });
    //TODO: Ordena por nome através callableObject
    sort(amigos.begin(), amigos.end(), AmigoComparator());
}
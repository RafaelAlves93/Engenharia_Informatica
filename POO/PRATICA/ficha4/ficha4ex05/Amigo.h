#ifndef FICHA_4_AMIGO_H
#define FICHA_4_AMIGO_H

#endif //FICHA_4_AMIGO_H

#include <iostream>
#include <sstream>

using namespace std;

class Amigo {
    string nome;
    int tel;
public:
    Amigo(string nome, int tel): nome(nome), tel(tel) {}
    string getNome() const noexcept { return nome; }
    int getTel() const noexcept { return tel; }
    string getDesc() const noexcept {
        ostringstream oss;
        oss << nome << " - " << tel;
        return oss.str();
    }

    // necessário para o find, replace, erase e sort no vector
    bool operator==(const Amigo &a) const noexcept {
        return nome == a.nome;
    }









    // necessário para o sort do vector e insert no set/map
    bool operator<(const Amigo &a) const noexcept {
        return nome < a.nome;
    }
};


// Compara dois amigos. Predicado binário. Os parametros são so dois amigos
// O callable objet não precisa de armazenar nada - os parametros tem tudo o que é preciso
class AmigoComparator {
public:
    bool operator()(const Amigo &a, const Amigo & b) {
        return a.getNome() < b.getNome();
    }
};

// Identifica um Amigo. O predicado é unário e o parametro é o amigo
// por isso a palavra a encontrar no nome tem que ser armazenado no callable object
class AmigoDiscriminator {
    string palavra; // palavra a usar como critério de identificação
public:
    AmigoDiscriminator(string pal) : palavra(pal) {}
    bool operator()(const Amigo &a) {
        return a.getNome().find(palavra) != string::npos;
    }
};



#include "Animais.h"

Animais::Animais(int id_n, char especie_n, int linha_n, int coluna_n, bool vivo_n, int idade_n, int saude_n, int movimInst_n, int aprox_n, int peso_n, int idadeMax_n, int fome_n) {
    id = id_n;
    especie = especie_n;
    linha = linha_n;
    coluna = coluna_n;
    vivo = vivo_n;
    idade = idade_n;
    saude = saude_n;
    movimInst = movimInst_n;
    aprox = aprox_n;
    peso = peso_n;
    idadeMax = idadeMax_n;
    fome = fome_n;
}

void Animais::imprimeInfoAnimais() const {
    cout << "Id:" << id << endl;
    cout << "Especie:" << especie << endl;
    cout << "Linha:" << linha << endl;
    cout << "Coluna:" << coluna << endl;
    cout << "Estado:";
    if (vivo)
        cout << "Vivo" << endl;
    else
        cout << "Morto" << endl;
    cout << "Idade:" << idade << endl;
    cout << "Saude:" << saude << endl;
    cout << "Movimento:" << movimInst << endl;
    cout << "Aproximacao:" << aprox << endl;
    cout << "Peso:" << peso << endl;
    cout << "\n";

    if(!historico.empty()) {
        cout << "\nHistorico de alimentacao:"<<endl;
        cout << "Nome: \tNutricao: \tToxicidade:"<<endl;
        for (auto i = 0; i < historico.size(); i++) {
            cout << historico[i][0] << "\t";
            cout << historico[i][1] << "\t\t";
            cout << historico[i][2] << "\t";
            cout << endl;
        }
    }
}

//PREENCHE VETOR HISTORICO COM O QUE COMEU
void Animais::preencheHistorico(const string& nome, int nutri, int toxi){
    array<string,3> a = {nome, to_string(nutri), to_string(toxi)};
    historico.push_back(a);
}

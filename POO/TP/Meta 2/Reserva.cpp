#include "Reserva.h"


Reserva::Reserva(int n_linhas, int n_colunas) {
    maxLinhas=n_linhas;
    maxColunas=n_colunas;
}

void Reserva::gerarAnimais(const string& tipo, int linhas, int colunas) {
    idunico=idunico+1;
    Animais a;

    //Funcao a verificar se maxLinhas=-1 gera posicoes random!!
    if(linhas==-1){
        linhas=gerarRandom(0,maxLinhas);
        colunas=gerarRandom(0,maxColunas);
        cout << "Animal " <<tipo<< " criado na posicao [" <<linhas+1<< "," <<colunas+1<< "]!" << endl;
    }
    else {                //XVISIVEL YVISIVEL É O CANTO DA AREA VISIVEL
        linhas = linhas + xvisivel;
        colunas = colunas + yvisivel;
    }

    if(tipo == "C")
    {
        a = Coelho(idunico, linhas, colunas, saudeC, gerarRandom(1,4));
        animais.push_back(a);
    }
    else if(tipo == "O")
    {
        a = Ovelha(idunico, linhas, colunas, saudeO, gerarRandom(4,8));
        animais.push_back(a);
    }
    else if(tipo == "L")
    {
        a = Lobo(idunico, linhas, colunas, saudeL);
        animais.push_back(a);
    }
    else if(tipo == "G")
    {
        a = Canguru(idunico, linhas, colunas, saudeG);
        animais.push_back(a);
    }
    else if(tipo == "M")
    {
        a = AnimMist(idunico, linhas, colunas, saudeM);
        animais.push_back(a);
    }
}

void Reserva::gerarAlimentos(const string& tipo, int linhas, int colunas){
    idunico=idunico+1;
    Alimentos a;
    //Funcao a verificar se maxLinhas=-1 gera posicoes random!!
    if(linhas==-1){
        do{
            linhas=gerarRandom(0,maxLinhas);
            colunas=gerarRandom(0,maxColunas);
        } while (verOcupa(linhas, colunas));
        cout << "Alimento " <<tipo<< " criado na posicao [" <<linhas+1<< "," <<colunas+1<< "]!" << endl;
    }

    else {
        linhas = linhas + xvisivel;
        colunas = colunas + yvisivel;
        if(verOcupa(linhas, colunas)){
            cout << "Posicao ja contem alimento!" << endl;
            return;
        }
        cout << "Alimento " <<tipo<< " criado com sucesso!" << endl;
    }

    if(tipo == "r")
    {
        //Alimentos& operator = (const Alimentos&);
        a = Relva(idunico, linhas, colunas);
        alimentos.push_back(a);
    }
    else if(tipo == "t")
    {
        a = Cenoura(idunico, linhas, colunas);
        alimentos.push_back(a);
    }
    else if(tipo == "b")
    {
        a = Bife(idunico, linhas, colunas);
        alimentos.push_back(a);
    }
    else if(tipo == "a")
    {
        a = alimMist(idunico, linhas, colunas);
        alimentos.push_back(a);
    }
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

//todos os i sao objetos da area visivel
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

    cout << "\nRESERVA:" <<endl;
    cout << "  1   2   3   4   5   6   7   8   9   10" << endl;
    cout << "-----------------------------------------" << endl;
    for (int i = 0; i < 10; ++i)
    {
        cout << "| ";
        for(int j = 0; j < 10; ++j)
        {
            cout << areaVisivel[i][j];
            cout << " | " ;
        }
        cout << i+1;
        cout << '\n';
        cout << "-----------------------------------------";
        cout << '\n';
    }
    cout << "A area visivel encontra-se na posicao [" << xvisivel+1 << "," << yvisivel+1
         << "] ate [" <<xvisivel+10 << "," << yvisivel+10 <<"]!";
    cout << endl;
}

void Reserva::verQuadrado(int l, int c) {       //Informações do comando see
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

void Reserva::verInfo(int id) {       //informações do Comando para ver info de um id concreto
    int flagani=0, flagali=0;
    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if(i->getid() == id)
        {
            flagali++;
            i->imprimeInfo();
        }
    }

    for (auto i = animais.begin(); i < animais.end(); ++i) {
        if(i->getid() == id)
        {
            flagani++;
            i->imprimeInfoAnimais();
        }
    }
    if(flagali ==0  && flagani == 0) {
        cout << "Nao existem alimentos ou animais com o ID introduzido!" << endl;
    }
}

bool Reserva::verOcupa(int linha, int coluna){
    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if(i->getlinha() == linha && i->getcoluna() == coluna && !i->getconsumido())
        {
            return true;
        }
    }
    return false;
}

int Reserva::gerarRandom(int a, int b) {
    srand((unsigned) time(nullptr));

    return a + (rand() % (b-a+1));
}

void Reserva::listarReserva() {
    int flaglist=0;

    cout << "ID: " << "Especie: " << "Saude: " << endl;
    for (auto i = animais.begin(); i < animais.end(); ++i) {
        flaglist++;
        cout << i->getid() << "      " << i->getespecie() << "       " << i->getsaude() << endl;
    }

    if (flaglist==0)
        cout << "Nao existem animais disponiveis na reserva!";
}

void Reserva::listarAreaVis() {
    int flagareavis=0;
    cout << "ID: " << "Especie: " << "Saude: " << endl;

    for (auto i = animais.begin(); i < animais.end(); ++i) {
        if(i->getlinha()>=xvisivel && i->getcoluna()>=yvisivel && i->getlinha()<=xvisivel+9 && i->getcoluna()<=yvisivel+9) {
            flagareavis++;
            cout << i->getid() << "      " << i->getespecie() << "       " << i->getsaude() << endl;
        }
    }
    if(flagareavis==0)
        cout << "Nao existem animais disponiveis na area visivel!";
}

void Reserva::killAnimalPosicao(int linha, int coluna) {
    Alimentos a;
    linha = linha + xvisivel;
    coluna = coluna + yvisivel;
    int flagkill=0, l, c;

    //auto i = animais.begin(); i <= animais.end(); ++i
    for (auto i = animais.end()-1; i >= animais.begin(); --i) {
        if (i->getlinha() == linha && i->getcoluna() == coluna) {
            idunico=idunico+1;

            //VERIFICA OCUPACAO DAS POSICOES ADJACENTES PARA CRIAR CORPO
            if(!verOcupa(i->getlinha(),(i->getcoluna())+1)){
                l=i->getlinha();
                c=(i->getcoluna())+1;
            }
            else if(!verOcupa(i->getlinha(),(i->getcoluna())-1)){
                l=i->getlinha();
                c=(i->getcoluna())-1;
            }
            else if(!verOcupa((i->getlinha())+1,i->getcoluna())){
                l=(i->getlinha())+1;
                c=i->getcoluna();
            }
            else if(!verOcupa((i->getlinha())-1,i->getcoluna())){
                l=(i->getlinha())-1;
                c=i->getcoluna();
            }
            else
                cout<<"Falta de espaco para criar um corpo!!";

            //VERIFICA O TIPO DE ANIMAL PARA DAR VALOR NUTRITIVO E TOXICIDADE DIFERENTES
            if(i->getespecie() == 'O')
            {
                a = Corpo(idunico, l, c, i->getpeso(), 0);
                alimentos.push_back(a);
            }
            else if(i->getespecie() == 'L')
            {
                a = Corpo(idunico, l, c, 10, 0);
                alimentos.push_back(a);
            }
            else if(i->getespecie() == 'G')
            {
                a = Corpo(idunico, l, c, 15, 5);
                alimentos.push_back(a);
            }
            else if(i->getespecie() == 'M')
            {
                a = Corpo(idunico, l, c, 10, 0);
                alimentos.push_back(a);
            }

            animais.erase(i);
            flagkill++;
        }
    }

    if(flagkill==0)
        cout<<"Nao existem animais disponiveis nesta posicao!!" <<endl;
    else if(flagkill>1)
        cout << "Animais mortos na posicao: [" <<linha+1<< "," <<coluna+1<< "] inserida!" << endl;
    else
        cout << "Animal morto na posicao: [" <<linha+1<< "," <<coluna+1<< "] inserida!" << endl;
}

void Reserva::killAnimalId(int id) {
    Alimentos a;
    int l, c;

    for (auto i = animais.begin(); i < animais.end(); ++i) {
        if (i->getid() == id) {
            i->setvivo(false);
            idunico=idunico+1;

            //VERIFICA OCUPACAO DAS POSICOES ADJACENTES PARA CRIAR CORPO
            if(!verOcupa(i->getlinha(),(i->getcoluna())+1)){
                l=i->getlinha();
                c=(i->getcoluna())+1;
            }
            else if(!verOcupa(i->getlinha(),(i->getcoluna())-1)){
                l=i->getlinha();
                c=(i->getcoluna())-1;
            }
            else if(!verOcupa((i->getlinha())+1,i->getcoluna())){
                l=(i->getlinha())+1;
                c=i->getcoluna();
            }
            else if(!verOcupa((i->getlinha())-1,i->getcoluna())){
                l=(i->getlinha())-1;
                c=i->getcoluna();
            }
            else
                cout<<"Falta de espaco para criar um corpo!!";


            //VERIFICA O TIPO DE ANIMAL PARA DAR VALOR NUTRITIVO E TOXICIDADE DIFERENTES
            if(i->getespecie() == 'O')
            {
                a = Corpo(idunico, l, c, i->getpeso(), 0);
                alimentos.push_back(a);
            }
            else if(i->getespecie() == 'L')
            {
                a = Corpo(idunico, l, c, 10, 0);
                alimentos.push_back(a);
            }
            else if(i->getespecie() == 'G')
            {
                a = Corpo(idunico, l, c, 15, 5);
                alimentos.push_back(a);
            }
            else if(i->getespecie() == 'M')
            {
                a = Corpo(idunico, l, c, 10, 0);
                alimentos.push_back(a);
            }
            animais.erase(i);
        }
    }
}

void Reserva::removAlimPosicao(int linha, int coluna) {
    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if (i->getlinha() == linha && i->getcoluna() == coluna && i->getconsumido()== false) {
            alimentos.erase(i);
        }
    }
}

void Reserva::removAlimID(int id){
    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if (i->getid() == id) {
            //i->setvivo(false);
            alimentos.erase(i);
        }
    }
}

void Reserva::empty(int linha, int coluna){
    int flagempty=0;
    //Remove alimento
    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        if (i->getlinha() == linha && i->getcoluna() == coluna && i->getconsumido()== false) {
            alimentos.erase(i);
            flagempty++;
        }
    }

    //Remove animais
    for (auto i = animais.end()-1; i >= animais.begin(); --i) {
        if (i->getlinha() == linha && i->getcoluna() == coluna) {
            animais.erase(i);
            flagempty++;
        }
    }
    if(flagempty==0)
        cout<<"Nao existem elementos nesta posicao para remover!";
    else
        cout<<"Elementos removidos na posicao [" <<linha+1<< "," <<coluna+1<<"]!";
}

void Reserva::feedDirect(int linha, int coluna, int nutri, int toxi){
    for (auto i = animais.end()-1; i >= animais.begin();--i){
        if (i->getlinha() == linha && i->getcoluna() == coluna) {
            i->preencheHistorico("user", nutri, toxi);

            // Atualiza Saude
            int updSaude = nutri - toxi;
            i->setsaude(i->getsaude() + updSaude);
            i->setfome(0);
        }
    }
}

void Reserva::feedDirectId(int id, int nutri, int toxi){
    for (auto i =animais.begin();i < animais.end();++i){
        if (i->getid() == id ) {
            i->preencheHistorico("user", nutri, toxi);

            // Atualiza Saude
            int updSaude = nutri - toxi;
            i->setsaude(i->getsaude() + updSaude);
            i->setfome(0);
        }
    }
}

void Reserva::Constantes(string tipo, string saude) {

    if (tipo == "SCoelho")
        saudeC = stoi(saude);
    else if (tipo == "SOvelha")
        saudeO = stoi(saude);
    else if (tipo == "SLobo")
        saudeL = stoi(saude);
    else if (tipo == "SCanguru")
        saudeG = stoi(saude);
}

void Reserva::next() {
    Animais a;
    int linhas, colunas;

    for (auto i = animais.begin(); i < animais.end(); ++i) {
        char tipo = i->getespecie();

        i->setidade(i->getidade() + 1);

        if (tipo == 'C') {
            // Mata coelho aos 30 instantes ou se a saude chegar a 0
            if (i->getidade() == i->getidadeMax() || i->getsaude() == 0) {
                killAnimalId(i->getid());
            } else {

                // Condição Alimentação
                for (auto a = alimentos.begin(); a < alimentos.end(); ++a) {
                    if (a->getlinha() == i->getlinha() && a->getcoluna() == i->getcoluna() &&
                        a->getcheiro().find("verdura") != string::npos) {
                        i->preencheHistorico(to_string(a->gettipo()), a->getvalornut(), a->getvalortox());
                        // Diferença entre soma o subtrai saude
                        int updSaude = a->getvalornut() - a->getvalortox();
                        i->setsaude(i->getsaude() + updSaude);
                        alimentos.erase(a);
                        i->setfome(0);
                    }
                }

                // Nascimento de novo coelho a cada 8 instantes (50% prob de nascer e num raio de 10 posições)
                if (i->getidade() % 8 == 0 && (rand() % 2) == 0) {
                    idunico = idunico + 1;
                    linhas = gerarRandom(i->getlinha() - 10, i->getlinha() + 10);
                    colunas = gerarRandom(i->getcoluna() - 10, i->getcoluna() + 10);
                    a = Coelho(idunico, linhas, colunas, saudeC, gerarRandom(1, 4));
                    animais.push_back(a);
                }

                // Aumenta a fome a cada instante
                i->setfome(i->getfome() + 1);
                // (fome > 10 perde 1 ponto de saude e desloca-se entre 1 a 3 posições aleatoriamente de cada vez)
                if (i->getfome() > 10 && i->getfome() < 20) {
                    i->setsaude(i->getsaude() - 1);
                    i->setmovimInst(3);
                    // (fome > 20 perde 2 pontos de saude e desloca-se entre 1 a 4 posições aleatoriamente de cada vez)
                } else if ((i->getfome() > 20)) {
                    i->setsaude(i->getsaude() - 2);
                    i->setmovimInst(4);
                }
                    //Normaliza o movimento quando não tem fome ou seja < 10
                else {
                    i->setmovimInst(2);
                }

                // Se encontrar um animal com mais de 10KG num raio de 4 posições de desloca-se na posição oposta
                int movimento = fugirAni(i, 10);
                // Caso se se apercebe de cheiro a verdura nas redondezas vai ao seu encontro
                if (movimento == 0) {
                    movimento = aproximarAli(i, "verdura", 1);
                    // Caso contrário continua numa direção random
                    if (movimento == 0)
                        movimentarRand(i, 1);
                }
            }
        }
        else if (tipo == 'O') {
            // Mata ovelha aos 35 instantes ou se a saude chegar a 0
            if (i->getidade() == i->getidadeMax() || i->getsaude() == 0) {
                killAnimalId(i->getid());
            }

            // Condição Alimentação
            for (auto a = alimentos.begin(); a < alimentos.end(); ++a) {
                //COMPARA A POSICAO COM O ALIMENTO
                if (a->getlinha() == i->getlinha() && a->getcoluna() == i->getcoluna() &&
                    a->getcheiro().find("erva") != string::npos) {
                    i->preencheHistorico(to_string(a->gettipo()), a->getvalornut(), a->getvalortox());
                    // Diferença entre soma ou subtrai saude
                    int updSaude = a->getvalornut() - a->getvalortox();
                    i->setsaude(i->getsaude() + updSaude);
                    alimentos.erase(a);
                    i->setfome(0);
                }
            }

            // Nascimento de nova ovelha a cada 15 instantes (num raio máximo de 12 posições)
            if (i->getidade() % 15 == 0) {
                idunico = idunico + 1;
                linhas = gerarRandom(i->getlinha() - 12, i->getlinha() + 12);
                colunas = gerarRandom(i->getcoluna() - 12, i->getcoluna() + 12);
                // Saude da nova ovelha igual ao da ovelha original, e peso gerado entre 4 e 8Kg
                a = Ovelha(idunico, linhas, colunas, i->getsaude(), gerarRandom(4, 8));
                animais.push_back(a);
            }

            // Aumenta a fome
            i->setfome(i->getfome() + 1);
            // (fome > 15 perde 1 ponto de saude e desloca-se entre 1 a 2 posições aleatoriamente de cada vez)
            if (i->getfome() > 15 && i->getfome() < 20) {
                i->setsaude(i->getsaude() - 1);
                i->setmovimInst(2);
            }
                // (fome > 20 perde 2 pontos de saude e desloca-se entre 1 a 2 posições aleatoriamente de cada vez)
            else if ((i->getfome() > 20)) {
                i->setsaude(i->getsaude() - 2);
                i->setmovimInst(2);
            }
                // Normaliza o movimento quando não tem fome ou seja < 15
            else {
                i->setmovimInst(1);
            }

            // Se encontrar um animal com mais de 15KG num raio de 3 posições de desloca-se na posição oposta
            int movimento = fugirAni(i, 15);
            if (movimento == 0) {
                // Caso se se apercebe de cheiro a erva nas redondezas vai ao seu encontro
                movimento = aproximarAli(i, "erva", 1);
                // Caso contrário continua numa direção random
                if (movimento == 0)
                    movimentarRand(i, 1);
            }

        }
        else if (tipo == 'L') {
            // Mata Lobo se a saude chegar a 0
            if (i->getsaude() == 0) {
                killAnimalId(i->getid());
            }

            // Condição lutar numa posição adjacente
            for (auto m = animais.begin(); m < animais.end(); ++m) {
                if (m->getespecie() != 'L' && (m->getlinha() == i->getlinha() && m->getcoluna() == i->getcoluna() ||    //na posicao atual
                                               m->getlinha() == i->getlinha() && m->getcoluna() == i->getcoluna() + 1 || //direita
                                               m->getlinha() == i->getlinha() && m->getcoluna() == i->getcoluna() - 1 || //esquerda
                                               m->getlinha() == i->getlinha() + 1 && m->getcoluna() == i->getcoluna() || //baixo
                                               m->getlinha() == i->getlinha() - 1 &&    //cima
                                               m->getcoluna() == i->getcoluna())) {
                    if (m->getpeso() < i->getpeso())
                        killAnimalId(m->getid());
                        // condição para random 50 50 para lutas
                    else if ((rand() % 2) == 0)
                        killAnimalId(i->getid());
                    else killAnimalId(m->getid());
                }
            }

            // Condição Alimentação
            for (auto a = alimentos.begin(); a < alimentos.end(); ++a) {
                if (a->getlinha() == i->getlinha() && a->getcoluna() == i->getcoluna() &&
                    a->getcheiro().find("carne") != string::npos) {
                    i->preencheHistorico(to_string(a->gettipo()), a->getvalornut(), a->getvalortox());
                    // Diferença entre soma ou subtrai saude
                    int updSaude = a->getvalornut() - a->getvalortox();
                    i->setsaude(i->getsaude() + updSaude);
                    alimentos.erase(a);
                    i->setfome(0);
                }
            }

            // Nascimento de novo Lobo uma única vez aleatoriamente (num raio máximo de 15 posições)
            if (i->getidade() == i->getnascimento()) {
                idunico = idunico + 1;
                linhas = gerarRandom(i->getlinha() - 15, i->getlinha() + 15);
                colunas = gerarRandom(i->getcoluna() - 15, i->getcoluna() + 15);
                a = Lobo(idunico, linhas, colunas, saudeL);
                animais.push_back(a);
            }

            // Aumenta a fome em 2 por cada instante
            i->setfome(i->getfome() + 2);
            // (fome > 15 perde 1 ponto de saude e a 2 posições de cada vez)
            if (i->getfome() > 15 && i->getfome() < 25) {
                i->setsaude(i->getsaude() - 1);
                i->setmovimInst(2);
            }
                // (fome > 25 perde 2 pontos de saude e a 2 posições de cada vez)
            else if ((i->getfome() > 25)) {
                i->setsaude(i->getsaude() - 2);
                i->setmovimInst(2);
            }
                // Normaliza o movimento quando não tem fome ou não deteta um animal nas proximidades
            else {
                i->setmovimInst(1);
            }

            // Se encontrar um animal nas redondezas vai ao seu encontro 2 posições de cada vez 3 se fome > 15
            int movimento = persegueAni(i);
            if (movimento == 0) {
                // Se sentir um alimento com cheiro a carne vai ao encontro dele
                movimento = aproximarAli(i, "carne", i->getmovimInst());
                // Caso contrário continua a deslocar-se de uma forma random
                if (movimento == 0)
                    movimentarRand(i, i->getmovimInst());
            }

        }
        else if (tipo == 'G') {
            // Condição morte
            if (i->getidade() == i->getidadeMax()) {
                killAnimalId(i->getid());
            }

            // Não come nem tem fome **

            // Condição Nascimento
            if (i->getidade() % 30 == 0) {
                idunico = idunico + 1;
                linhas = gerarRandom(i->getlinha() - 3, i->getlinha() + 3);
                colunas = gerarRandom(i->getcoluna() - 3, i->getcoluna() + 3);
                a = Canguru(idunico, linhas, colunas, saudeG);
                animais.push_back(a);
            }

        }
        else if (tipo == 'M') {
            if (i->getsaude() == 0) {
                killAnimalId(i->getid());
            }

            for (auto m = animais.begin(); m < animais.end(); ++m) {
                if (m->getespecie() == 'L' && (m->getlinha() == i->getlinha() && m->getcoluna() == i->getcoluna() ||
                                               m->getlinha() == i->getlinha() &&
                                               m->getcoluna() == i->getcoluna() + 1 ||
                                               m->getlinha() == i->getlinha() &&
                                               m->getcoluna() == i->getcoluna() - 1 ||
                                               m->getlinha() == i->getlinha() + 1 &&
                                               m->getcoluna() == i->getcoluna() ||
                                               m->getlinha() == i->getlinha() - 1 &&
                                               m->getcoluna() == i->getcoluna())) {

                    //condição para random 50 50 para lutas
                    if ((rand() % 2) == 0)
                        killAnimalId(i->getid());
                    else killAnimalId(m->getid());
                }
            }

            // Condição Alimentação
            for (auto a = alimentos.begin(); a < alimentos.end(); ++a) {
                if (a->getlinha() == i->getlinha() && a->getcoluna() == i->getcoluna() &&
                    a->getcheiro().find("carne") != string::npos) {
                    i->preencheHistorico(to_string(a->gettipo()), a->getvalornut(), a->getvalortox());
                    // Diferença entre soma ou subtrai saude
                    int updSaude = a->getvalornut() - a->getvalortox();
                    i->setsaude(i->getsaude() + updSaude);
                    alimentos.erase(a);
                    i->setfome(0);
                }
            }


            // Aumenta a fome em 2 por cada instante
            i->setfome(i->getfome() + 2);
            // (fome > 15 perde 1 ponto de saude e a 2 posições de cada vez)
            if (i->getfome() > 15 && i->getfome() < 20) {
                i->setsaude(i->getsaude() - 1);
                i->setmovimInst(1);
            }
                // (fome > 25 perde 2 pontos de saude e a 2 posições de cada vez)
            else if ((i->getfome() > 20)) {
                i->setsaude(i->getsaude() - 2);
                i->setmovimInst(2);
            }
                // Normaliza o movimento quando não tem fome ou não deteta um animal nas proximidades
            else {
                i->setmovimInst(1);
            }

            // Se encontrar lobo
            int movimento = persegueLobo(i);
            if (movimento == 0) {
                // Caso contrário continua a deslocar-se de uma forma random
                if (movimento == 0)
                    movimentarRand(i, i->getmovimInst());
            }
        }
    }

    for (auto i = alimentos.begin(); i < alimentos.end(); ++i) {
        char tipo = i->gettipo();

        i->settempo(i->gettempo() + 1);

        if (tipo == 'r') {
            // Duração de 20 Instantes
            if (i->gettempo() == i->getidadeMax()) {
                removAlimID(i->getid());
            }

            //Aparece 75% da sua duração de vida numa posição próxima entre 4 e 8
            if (i->gettempo() == 15) {
                int seguralinha = 0;
                int seguracoluna = 0;
                while ((seguralinha > -3 && seguralinha < 3) && (seguracoluna > -3 && seguracoluna < 3)) {//gera linhas e colunas random entre 4 e 8
                    seguralinha = gerarRandom(-8, 8);
                    seguracoluna = gerarRandom(-8, 8);
                }
                gerarAlimentos("r", linhas, colunas);
            }
        }
        else if (tipo == 't') {
            if (i->gettempo() % 10 == 0 && i->getvalortox() <= 3) {
                i->setvalorTox(i->getvalortox() + 1);
            }
        }
        else if (tipo == 'p') {
            i->settempo(i->gettempo() + 1);
            if (i->getvalortox() < i->getnutrinicial() * 2) {
                i->setvalorTox(i->getvalortox() + 1);
            }
            if (i->getvalornut() > 0) {
                i->setvalorNut(i->getvalornut() - 1);
            }

        }
        else if (tipo == 'b') {
            if (i->gettempo() == i->getidadeMax()) {
                removAlimID(i->getid());
            }

            if (i->getvalornut() > 0) {
                i->setvalorNut(i->getvalornut() - 1);
            }

        }
        else if (tipo == 'a') {
            // 10 Instantes
            if (i->gettempo() == i->getidadeMax()) {
                removAlimID(i->getid());
            }

            i->settempo(i->gettempo() + 1);

            // Ganha 1 valor nut por instante
            if (i->getvalornut() > 0) {
                i->setvalorNut(i->getvalornut() + 1);
            }
        }
    }
}

//VERIFICA SE ALGUM ANIMAL COM MAIS PESO QUE ELE NAS POSIÇOES TODAS QUE ELE CONSEGUE VER
int Reserva::fugirAni(vector<Animais>::iterator i, int peso){
    int random = 0;
    for (auto j = animais.begin(); j < animais.end(); ++j) {    //PERCORRE O VETOR DOS ANIMAIS
        if (j->getpeso() > peso) {                          //SE TIVER MAIS MESO QUE ELE FOGE
            int posx = i->getlinha();
            int posy = i->getcoluna();
            if (posy == j->getcoluna() && j->getlinha() < posx && //APROXIMACAO - VERIFICA A DIRECAO CIMA! SE UM DOS IF ACONTECER ELE FOGE DO ANIMAL
                j->getlinha() >= (posx - i->getaprox()))
            {
                //geram uma posiçao random, depois verifica se a posiçao cai fora do tabuleiro e faz a conta para ir para o outro lado
                random = (posx + gerarRandom(1, i->getmovimInst()));
                if (random >= maxLinhas) {
                    random = random - maxLinhas;
                    i->setlinha(random);
                } else
                    i->setlinha(random);
                return 1;
                break;
            } else if (posy == j->getcoluna() && j->getlinha() > posx &&        //BAIXO
                       j->getlinha() <= (posx + i->getaprox()))
            {
                random = (posx - gerarRandom(1, i->getmovimInst()));
                if (random < 0) {
                    random = maxLinhas  + random;
                    i->setlinha(random);
                } else
                    i->setlinha(random);
                return 1;
                break;
            } else if (posx == j->getlinha() && j->getcoluna() > posy &&        //DIREITA
                       j->getcoluna() <= (posy + i->getaprox()))
            {
                random = (posy - gerarRandom(1, i->getmovimInst()));
                if (random < 0) {
                    random = maxColunas + random;
                    i->setcoluna(random);
                } else
                    i->setcoluna(random);
                return 1;
                break;
            } else if (posx == j->getlinha() && j->getcoluna() < posy &&        //ESQUERDA
                       j->getcoluna() >= (posy - i->getaprox()))
            {
                random = (posy + gerarRandom(1, i->getmovimInst()));
                if (random >= maxColunas) {
                    random = random - maxColunas;
                    i->setcoluna(random);
                } else
                    i->setcoluna(random);
                return 1;
                break;
            }
        }
    }
    return 0;
}

//FUNCAO PARA VERIFICAR A APROXIMACAO ALIMENTO
int Reserva::aproximarAli(vector<Animais>::iterator i, string cheiro, int mov){ //mov (minimo movimento)
    for (auto j = alimentos.begin(); j < alimentos.end(); ++j) {
        if(j->getcheiro().find(cheiro) != string::npos)//VERIFICA SE O CHEIRO É DIFERENTE
        {
            int posx = i->getlinha();
            int posy = i->getcoluna();//PEGA NA POSICAO DO ANIMAL (i)
            if (posy == j->getcoluna() && j->getlinha() < posx && j->getlinha() >= (posx - i->getaprox())) //VERIFICA SE EXISTE UM ALIMENTO CIMA
            {
                i->setlinha(posx - gerarRandom(mov, i->getmovimInst()));
                return 1;
                break;
            }
            else if (posy == j->getcoluna() && j->getlinha() > posx && j->getlinha() <= (posx + i->getaprox())) //BAIXO
            {
                i->setlinha(posx + gerarRandom(mov, i->getmovimInst()));
                return 1;
                break;
            }
            else if (posx == j->getlinha() && j->getcoluna() > posy && j->getcoluna() <= (posy + i->getaprox())) //DIREITA
            {
                i->setcoluna(posy + gerarRandom(mov, i->getmovimInst()));
                return 1;
                break;
            }
            else if (posx == j->getlinha() && j->getcoluna() < posy && j->getcoluna() >= (posy - i->getaprox())) //ESQUERDA
            {
                i->setcoluna(posy - gerarRandom(mov, i->getmovimInst()));
                return 1;
                break;
            }
        }
    }
    return 0;
}

void Reserva::movimentarRand(vector<Animais>::iterator i, int mov){
    int random = 0;
    int posx = i->getlinha();
    int posy = i->getcoluna();

    int direcao = rand() % 4; //GERA UM RANDOM DE 0 A 3, DEPOIS GERA SE UMA POSICAO RANDOM E VAMOS PARA LA NA DIRECAO QUE JA FOI DECIDIDA
    if (direcao == 0)
    {
        random = (posx - gerarRandom(mov, i->getmovimInst())); //CIMA
        if (random < 0) {
            random = maxLinhas  + random;
            i->setlinha(random);
        } else
            i->setlinha(random);
    }
    else if (direcao == 1)
    {
        random = (posx + gerarRandom(mov, i->getmovimInst())); //BAIXO
        if (random >= maxLinhas) {
            random = random - maxLinhas;
            i->setlinha(random);
        } else
            i->setlinha(random);
    }
    else if (direcao == 2)
    {
        random = (posy + gerarRandom(mov, i->getmovimInst())); //DIREITA
        if (random >= maxColunas) {
            random = random - maxColunas;
            i->setcoluna(random);
        } else
            i->setcoluna(random);
    }
    else if (direcao == 3)
    {
        random = (posy - gerarRandom(mov, i->getmovimInst()));  //ESQUERDA
        if (random < 0) {
            random = maxColunas + random;
            i->setcoluna(random);
        } else
            i->setcoluna(random);
    }
}

int Reserva::persegueAni(vector<Animais>::iterator i){ //SO O LOBO PERCEGUE ANIMAIS
    int maior = 0;
    int posx = i->getlinha();
    int posy = i->getcoluna();

    for (auto j = animais.begin(); j < animais.end(); ++j){
        if(j->getespecie() != 'L')
        {
            if (posy == j->getcoluna() && j->getlinha() < posx && j->getlinha() >= (posx - i->getaprox()) && i->getpeso()>maior) //cima
            {
                i->setlinha(posx - i->getmovimInst());
                i->setcoluna(posy);
                maior=i->getpeso();
            }
            else if (posy == j->getcoluna() && j->getlinha() > posx && j->getlinha() <= (posx + i->getaprox()) && i->getpeso()>maior) //baixo
            {
                i->setlinha(posx + i->getmovimInst());
                i->setcoluna(posy);
                maior=i->getpeso();
            }
            else if (posx == j->getlinha() && j->getcoluna() > posy && j->getcoluna() <= (posy + i->getaprox()) && i->getpeso()>maior) //direita
            {
                i->setcoluna(posy + i->getmovimInst());
                i->setlinha(posx);
                maior=i->getpeso();
            }
            else if (posx == j->getlinha() && j->getcoluna() < posy && j->getcoluna() >= (posy - i->getaprox()) && i->getpeso()>maior) //esquerda
            {
                i->setcoluna(posy - i->getmovimInst());
                i->setlinha(posx);
                maior=i->getpeso();
            }
        }
    }
    if (maior==0)
        return 0;
    else
        return 1;
}

int Reserva::persegueLobo(vector<Animais>::iterator i){
    int posx = i->getlinha();
    int posy = i->getcoluna();

    for (auto j = animais.begin(); j < animais.end(); ++j){
        if(j->getespecie() == 'L')
        {
            if (posy == j->getcoluna() && j->getlinha() < posx && j->getlinha() >= (posx - i->getaprox())) // Verifica lobo em cima
            {
                i->setlinha(posx - i->getmovimInst());
                i->setcoluna(posy);
                return 1;
            }

            else if (posy == j->getcoluna() && j->getlinha() > posx && j->getlinha() <= (posx + i->getaprox())) // Verifica lobo em baixo
            {
                i->setlinha(posx + i->getmovimInst());
                i->setcoluna(posy);
                return 1;
            }
            else if (posx == j->getlinha() && j->getcoluna() > posy && j->getcoluna() <= (posy + i->getaprox())) // Verifica lobo à direita
            {
                i->setcoluna(posy + i->getmovimInst());
                i->setlinha(posx);
                return 1;
            }
            else if (posx == j->getlinha() && j->getcoluna() < posy && j->getcoluna() >= (posy - i->getaprox())) // Verifica lobo à esquerda
            {
                i->setcoluna(posy - i->getmovimInst());
                i->setlinha(posx);
                return 1;
            }
        }
    }
    return 0;
}

#include "Interface.h"


void Interface::lerinput(istringstream& iss, Reserva * r) {
    string input;
    iss >> input;
    int linha = (*r).getlinhas();
    int coluna = (*r).getcolunas();
    string nome,tipo,direcao;
    int linhaU=0,colunaU=0,id=0,valor=0,pnutri=0,ptoxi=0,instantes=0,segundos=0;

//-------------Comando criar animal-------------
    if (input == "animal") {
        if (iss >> tipo) {
            //linhaU--;colunaU--;
            if (tipo == "C" || tipo == "O" || tipo == "L" || tipo == "G" || tipo == "M") {
                if (iss >> linhaU && iss >> colunaU){
                    linhaU--;colunaU--;
                    if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                        r->gerarAnimais(tipo, linhaU, colunaU);
                        cout << "Animal " <<tipo<< " criado com sucesso!" << endl;
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }
                }
                else{
                    r->gerarAnimais(tipo, -1, -1);
                }
            }
            else cout << "Tipo de animal invalido!" << endl;
        }else cout << "Parametros de animal invalidos!" << endl;
    }


//-------------Comando matar animal por posicao-------------
    else if (input == "kill") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                r->killAnimalPosicao(linhaU, linhaU);
                r->atualizaReservaVisivel();
                r->MostrarZonas();
            }
            else
                cout << "Posicoes fora da dimensão da reserva!" << endl;
        }else cout << "Parametros de Kill invalidos!" << endl;
    }


//-------------Comando matar animal por id-------------
    else if (input == "killid") {
        if (iss >> id) {
            r->killAnimalId(id);
            cout << "Animal com o id selecionado morto!" << endl;
            r->atualizaReservaVisivel();
            r->MostrarZonas();
        }else cout << "Parametros de Kill invalidos!" << endl;
    }


//-------------Comando colocar alimento-------------
    else if (input == "food") {
        if (iss >> tipo) {
            //linhaU--;colunaU--;
            if (tipo == "r" || tipo == "t" || tipo == "b" || tipo == "a") {
                if (iss >> linhaU && iss >> colunaU){
                    linhaU--;colunaU--;
                    if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                        r->gerarAlimentos(tipo, linhaU, colunaU);
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }
                }
                else{
                    r->gerarAlimentos(tipo, -1, -1);
                    r->atualizaReservaVisivel();
                    r->MostrarZonas();
                }
            }
            else cout << "Tipo de alimento invalido!" << endl;
        }else cout << "Parametros de alimentos invalidos!" << endl;
    }


//-------------Comando alimentar diretamente animais-------------
    else if (input == "feed") {
        if (iss >> linhaU && iss >> colunaU && iss >> pnutri && iss >> ptoxi) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0)
                if(pnutri>0)
                    if(ptoxi>=0){
                        r->feedDirect(linhaU, colunaU, pnutri, ptoxi);
                        cout << "Animal alimentado!" << endl;
                    }
                    else cout << "Valor de toxicidade tem de ser um numero inteiro maior ou igual a 0!" << endl;
                else cout<< "Valor nutritivo tem de ser um numero inteiro maior que 0!" << endl;
            else cout << "Posicoes fora da dimensão da reserva!" << endl;
        }else cout << "Parametros de alimentacao invalidos!" << endl;
    }


//-------------Comando matar animal por id-------------
    else if (input == "feedid") {
        if (iss >> id && iss >> pnutri && iss >> ptoxi) {
            if(pnutri>0)
                if(ptoxi>=0) {
                    r->feedDirectId(id, pnutri, ptoxi);
                    cout << "Animal alimentado!" << endl;
                }
                else cout << "Valor de toxicidade tem de ser um numero inteiro maior ou igual a 0!" << endl;
            else cout<< "Valor nutritivo tem de ser um numero inteiro maior que 0!" << endl;
        }else cout << "Parametros de alimentacao invalidos!" << endl;
    }


//-------------Comando remover alimento-------------
    else if (input == "nofood") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                r->removAlimPosicao(linhaU,colunaU);
                cout << "Alimento removido!" << endl;
                r->atualizaReservaVisivel();
                r->MostrarZonas();
            }
            else
                cout << "Posicoes fora da dimensao da reserva!" << endl;
        }else if(linhaU>0){
            r->removAlimID(linhaU);
            r->atualizaReservaVisivel();
            r->MostrarZonas();
            cout << "Alimento com o id: " <<linhaU<< " removido!" << endl;
        }else cout << "Parametros de alimentacao invalidos!" << endl;
    }


//-------------Comando remover o que estiver dentro de uma posicao-------------
    else if (input == "empty") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                r->empty(linhaU,colunaU);
                r->atualizaReservaVisivel();
                r->MostrarZonas();
            }
            else
                cout << "Posicoes fora da dimensao da reserva!" << endl;
        }else cout << "Parametros de eliminacao invalidos!" << endl;
    }


//-------------Comando para ver o que estiver dentro de uma posicao-------------
    else if (input == "see") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                cout << "Informacao sobre a posicao inserida:" << endl;
                r->verQuadrado(linhaU, colunaU);
                cout << "\n";
            }
            else
                cout << "Posicoes fora da dimensao da reserva!" << endl;
        }else cout << "Parametros para informacoes invalidos!" << endl;
    }


//-------------Comando para ver info de um id concreto-------------
    else if (input == "info") {
        if (iss >> id) {
            cout << "Informacao sobre o id inserido: " << endl;
            r->verInfo(id);
        }else cout << "Parametros de informacao invalidos!" << endl;
    }


//-------------Comando p/ next-------------
    else if (input == "n") {
        if (iss >> instantes && iss >> segundos) {

            if (instantes > 0 && segundos > 0) {
                for (int i = 0; i < instantes; i++)  {
                    r->next();
                    sleep(10);
                    r->atualizaReservaVisivel();
                    r->MostrarZonas();
                }
                cout << "Vai avancar " << instantes << "instantes com uma pausa de " << segundos << "segundos entre eles!" << endl;

            } else if (instantes > 0) {
                for (int i = 0; i < instantes; i++)  {
                    r->next();
                    r->atualizaReservaVisivel();
                    r->MostrarZonas();
                }
                cout << "Vai avancar" << instantes << "instantes!" << endl;
            }
        }
        else {
            r->next();
            cout << "Vai avancar um instante!"<< endl;
            r->atualizaReservaVisivel();
            r->MostrarZonas();
        }
    }


//-------------Comando para listar o id de animais na reserva-------------
    else if (input == "anim") {                       //IMPRIMIR VETOR
        r->listarReserva();
    }


//-------------Comando para listar ID dos animais na área visível da reserva-------------
    else if (input == "visanim") {                    //IMPRIMIR VETOR MAS DA POSICAO ATE A POSICAO (AREA VISIVEL)
        r->listarAreaVis();
    }


//-------------Armazenar o estado da reserva em memória-------------
    else if (input == "store") {
        if (iss >> nome) {
            cout << "Comando a ser implementado" << endl;
        }
        else cout << "Parametros para guardar a reserva invalidos!" << endl;
    }


//-------------Reativa um estado da reserva antigo-------------
    else if (input == "restore") {
        if (iss >> nome) {
            cout << "Comando a ser implementado" << endl;
        }
        else cout << "Parametros para reativaro estado da reserva invalidos!" << endl;
    }


//-------------Encerra a simulacao-------------
    else if (input == "exit") {
        cout << "Simulador encerrado" << endl;
        exit(1);
    }

//-------------Comando para slides-------------
    else if (input == "slide") {
        int xvisivel = r->getxvisivel();
        int yvisivel = r->getyvisivel();
        if (iss >> direcao && iss >> valor) {
            if (direcao == "right") {
                //Restrição de 10 lin/col (relatório decidimos que o user não pode mover mais de 10 casas)
                if (valor > 0 && valor <= 10){
                    //cout << coluna;
                    if (yvisivel+valor <= coluna) {
                        r->setarea(xvisivel, valor + yvisivel);
                        cout << "Janela movida para a direita!" << endl;
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }else cout << "O valor introduzido leva-o para fora da reserva! Introduza um valor mais baixo!" << endl;
                }
                else cout << "Numero de casas a mover tem de ser entre 0 e 10!" << endl;
            } else if (direcao == "left") {
                if (valor > 0 && valor <= 10){
                    if (yvisivel-valor >= 0) {
                        r->setarea(xvisivel,  yvisivel - valor);
                        cout << "\nJanela movida para a esquerda!" << endl;
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }else cout << "O valor introduzido leva-o para fora da reserva! Introduza um valor mais baixo!" << endl;
                }
                else cout << "Numero de casas a mover tem de ser entre 0 e 10!" << endl;
            } else if (direcao == "up") {
                if (valor > 0 && valor <= 10){
                    if (xvisivel-valor >= 0) {
                        r->setarea(valor - xvisivel, yvisivel);
                        cout << "Janela movida para cima!" << endl;
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }else cout << "O valor introduzido leva-o para fora da reserva! Introduza um valor mais baixo!" << endl;
                }
                else cout << "Numero de casas a mover tem de ser entre 0 e 10!" << endl;
            } else if (direcao == "down") {
                if (valor > 0 && valor <= 10){
                    if (xvisivel+valor <= linha) {
                        r->setarea(xvisivel + valor, yvisivel);
                        cout << "Janela movida para baixo!" << endl;
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }else cout << "O valor introduzido leva-o para fora da reserva! Introduza um valor mais baixo!" << endl;
                }
                else cout << "Numero de casas a mover tem de ser entre 0 e 10!" << endl;
            }
            else cout << "Direcao inserida invalida!" << endl;
        } else cout << "Parametro invalido!!" << endl;
    }
    else cout << "Comando invalido!" << endl;
}

void Interface::lerconstantes(istringstream& iss,  Reserva * r) {
    string var, valor;
    iss >> var >>  valor;
    r->Constantes(var, valor);
}

void Interface::ui(){
    string input, nomeF,text, aux;
    // Dimensões para inicialização da reserva
    int linhas, colunas;



    while(1){
        cout << "Introduza a dimensao da reserva:\n";
        getline(cin, aux);
        istringstream iss(aux);
        iss >> linhas >> colunas;
        if((linhas<16 || colunas<16) || (linhas>500 || colunas>500))
            cout << "Insira dois valores entre 16 e 500!\n";
        else
            break;
    }

    Reserva r(linhas, colunas);
    r.atualizaReservaVisivel();
    r.MostrarZonas();

    // Ler ficheiro constantes.txt ao iniciar
    ifstream ficheiro("../constantes.txt");
    if(ficheiro.fail())
        cout << "O ficheiro constantes.txt nao foi encontrado!\n" << endl;
    else {
        while (getline(ficheiro, text)) {
            istringstream fss;
            fss.str(text);
            lerconstantes(fss, &r);
        }
        cout << "\nFicheiro constantes carregado c/ Sucesso!\n" << endl;
    }

    do {
        cout << "\nIntroduza um comando:" << endl;
        getline(cin, input);
        istringstream iss(input);
        istringstream ess(input);
        if (iss >> input) {
            if (input == "load") {                                 //load de ficheiro comandos
                if (iss >> nomeF) {
                    cout << nomeF << endl;
                    ifstream ficheiro("../"+nomeF);
                    while (getline(ficheiro, text)) {
                        istringstream fss;
                        fss.str(text);
                        lerinput(fss, &r);
                    }
                }
                else cout << "Insira o nome do ficheiro correto!" << endl;
            }
            else lerinput(ess,&r);
        }
    } while (1);
}
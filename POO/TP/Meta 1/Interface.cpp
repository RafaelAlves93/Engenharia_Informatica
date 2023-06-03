//
// Created by rafaa on 25/11/2022.
//

#include "Interface.h"

void Interface::lerinput(istringstream& iss, Reserva * r) {
    string input;
    iss >> input;
    int linha = (*r).getlinhas();
    int coluna = (*r).getcolunas();
    string nome,tipo, direcao;
    int linhaU=0,colunaU=0,id=0,valor=0,pnutri=0,ptoxi=0, instantes=0, segundos=0;

    // Comando criar animal
    if (input == "animal") {
        if (iss >> tipo && iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (tipo == "C") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Coelho criado com sucesso!" << endl;
                }else cout << "Coelho criado numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "O") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Ovelha criada com sucesso!" << endl;
                }else cout << "Ovelha criada numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "L") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Lobo criado com sucesso!" << endl;
                }else cout << "Lobo criado numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "G") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Canguru criado com sucesso!" << endl;
                }else cout << "Canguru criado numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "M") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Animal aleatorio criado com sucesso!" << endl;
                }else cout << "Animal aleatorio criado numa posicao aleatoria dentro da reserva!" << endl;
            }
            else cout << "Tipo de animal invalido!" << endl;
        }else cout << "Parametros de animal invalidos!" << endl;
    }
        // Comando matar animal por posição
    else if (input == "kill") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0)
                cout << "Animal morto na linha x coluna inseridas" << endl;
            else
                cout << "Posicoes fora da dimensão da reserva!" << endl;
        }else cout << "Parametros de Kill invalidos!" << endl;
    }

        // Comando matar animal por id
    else if (input == "killid") {
        if (iss >> id) {
                cout << "Animal com o id selecionado morto!" << endl;
        }else cout << "Parametros de Kill invalidos!" << endl;
    }

        // Comando colocar alimento
    else if (input == "food") {
        if (iss >> tipo && iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (tipo == "r") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Relva adcionada com sucesso!" << endl;
                }else cout << "Relva adcionada numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "t") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Cenoura adicionada com sucesso!" << endl;
                }else cout << "Cenoura adicionada numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "b") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Bife adicionado com sucesso!" << endl;
                }else cout << "Bife adicionado numa posicao aleatoria dentro da reserva!" << endl;
            } else if (tipo == "a") {
                if ( linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0){
                    cout << "Alimento misterio adicionado com sucesso!" << endl;
                }else cout << "Alimento misterio adicionado numa posicao aleatoria dentro da reserva!" << endl;
            }
            else cout << "Tipo de alimento invalido!" << endl;
        }else cout << "Parametros de alimentos invalidos!" << endl;
    }
        // Comando alimentar diretamente animais
    else if (input == "feed") {
        if (iss >> linhaU && iss >> colunaU && iss >> pnutri && iss >> ptoxi) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0)
                if(pnutri>0)
                    if(ptoxi>=0)
                        cout << "Animal alimentado!" << endl;
                    else cout << "Valor de toxicidade tem de ser um numero inteiro maior ou igual a 0!" << endl;
                else cout<< "Valor nutritivo tem de ser um numero inteiro maior que 0!" << endl;
            else cout << "Posicoes fora da dimensão da reserva!" << endl;
        }else cout << "Parametros de alimentacao invalidos!" << endl;
    }

        // Comando matar animal por id
    else if (input == "feedid") {
        if (iss >> id && iss >> pnutri && iss >> ptoxi) {
                if(pnutri>0)
                    if(ptoxi>=0)
                        cout << "Animal alimentado!" << endl;
                    else cout << "Valor de toxicidade tem de ser um numero inteiro maior ou igual a 0!" << endl;
                else cout<< "Valor nutritivo tem de ser um numero inteiro maior que 0!" << endl;
        }else cout << "Parametros de alimentacao invalidos!" << endl;
    }
        // Comando remover alimento
    else if (input == "nofood") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0)
                cout << "Alimento removido" << endl;
            else
                cout << "Posicoes fora da dimensao da reserva!" << endl;
        }else cout << "Parametros de alimentacao invalidos!" << endl;
    }
        // Comando remover alimento por id
    else if (input == "nofeedid") {
        if (iss >> id) {
                cout << "Alimento com o id removido" << endl;
        }else cout << "Parametros de alimentacao invalidos!!" << endl;
    }
        // Comando remover o que estiver dentro de uma posicao
    else if (input == "empty") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0)
                cout << "Posicao limpa!" << endl;
            else
                cout << "Posicoes fora da dimensao da reserva!" << endl;
        }else cout << "Parametros de eliminacao invalidos!" << endl;
    }

        // Comando para ver o que estiver dentro de uma posicao
    else if (input == "see") {
        if (iss >> linhaU && iss >> colunaU) {
            linhaU--;colunaU--;
            if (linhaU < linha && colunaU < coluna && colunaU >= 0 && linhaU >= 0) {
                cout << "Informacao sobre a posicao inserida:" << endl;
                cout << "Informacao sobre a posicao inserida:" << endl;
                r->verQuadrado(linhaU, colunaU);
                cout << "\n";
            }
            else
                cout << "Posicoes fora da dimensao da reserva!" << endl;
        }else cout << "Parametros para ver informacoes invalidos!" << endl;
    }

        // Comando para ver info de um id concreto
    else if (input == "info") {
        if (iss >> id) {
                cout << "Informacao sobre o id inserido: " << endl;
        }else cout << "Parametros de ver informacao invalidos!" << endl;
    }

        // Comando p/ prox instante
    else if (input == "n") {
        if (iss >> instantes && iss >> segundos) {
            cout << "Comando a ser implementado!" << endl;

            if (instantes > 0 && segundos > 0) {
                cout << "Vai avancar" << instantes << "instantes com uma pausa de" << segundos << "segundos entre eles!"
                     << endl;
            } else if (instantes > 0)
                cout << "Vai avancar" << instantes << "instantes!" << endl;
            else cout << "Vai avancar um instante!";
        }
    }

        // comando para listar o id nos animais na reserva
    else if (input == "anim") {
        cout << "Comando a ser implementado" << endl;
    }
    // comando para listar ID dos animais na área visível da reserva
    else if (input == "visanim") {
        cout << "Comando a ser implementado" << endl;
    }

        // Armazenar o estado da reserva em memória
    else if (input == "store") {
        if (iss >> nome) {
            cout << "Comando a ser implementado" << endl;
        }
        else cout << "Parametros para guardar a reserva invalidos!" << endl;
    }

        // Reativa um estado da reserva antigo
    else if (input == "restore") {
        if (iss >> nome) {
            cout << "Comando a ser implementado" << endl;
        }
        else cout << "Parametros para reativaro estado da reserva invalidos!" << endl;
    }
        //  Encerra a simulação
    else if (input == "exit") {
        cout << "Simulador encerrado" << endl;
        exit(1);
    }

    // Comando para slides
    if (input == "slide") {
        int xvisivel = r->getxvisivel();
        int yvisivel = r->getyvisivel();
        if (iss >> direcao && iss >> valor) {
            if (direcao == "right") {
                // Restrição de 10 lin/col (relatório -> decidi que o user não pode mover mais de 10 casas)
                if (valor > 0 && valor <= 10){
                    //cout << coluna;
                    if (yvisivel+valor <= coluna) {
                        r->setarea(xvisivel, valor + yvisivel);
                        cout << "\nJanela movida para a direita!" << endl;
                        r->atualizaReservaVisivel();
                        r->MostrarZonas();
                    }else cout << "O valor introduzido leva-o para fora da reserva! Introduza um valor mais baixo!" << endl;
                }
                else cout << "Numero de casas a mover tem de ser entre 0 e 10!" << endl;
            } else if (direcao == "left") {
                if (valor > 0 && valor <= 10){
                    if (yvisivel-valor >= 0) {
                        r->setarea(xvisivel,  yvisivel - valor);
                        cout << "\nJanela movifa para a esquerda!" << endl;
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

void Interface::lerconstantes(istringstream& iss) {
    string var, valor;
    iss >> var >>  valor;
    cout << "Parametro:" << var << " Valor:" << valor << endl;
}

void Interface::ui(){
    string input, nomeF,text, aux;
    // Dimensões para inicialização da reserva
    int linhas, colunas;

    // Ler ficheiro constantes.txt ao iniciar
    ifstream ficheiro("../constantes.txt");
    if(ficheiro.fail())
        cout <<  "O ficheiro constantes.txt nao foi encontrado!\n" << endl;
    else {
        cout << "Os seguintes parametros vao ser atualizados:\n" << endl;
        while (getline(ficheiro, text)) {
            istringstream fss;
            fss.str(text);
            lerconstantes(fss);
        }
        cout << "\nFicheiro constantes carregado c/ Sucesso!\n" << endl;
    }

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
    r.gerar();
    r.atualizaReservaVisivel();
    r.MostrarZonas();


    do {
        cout << "\nIntroduza um comando:" << endl;
        getline(cin, input);
        istringstream iss(input);
        istringstream ess(input);
        if (iss >> input) {
            if (input == "load") {                                             //load de ficheiro comandos
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
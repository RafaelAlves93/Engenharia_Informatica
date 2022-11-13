#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define TAM 256

#define N_THREADS 4 //Numero de threads inicial

int SomaGlobalPares = 0, SomaGlobalPrimos = 0;  //VARIAVEIS GLOBAIS -> Seccao critica!

////////////
//ESTRUTURA:
typedef struct {
    int numeroMenor;
    int numeroMaior;
    int contador;
    //int soma;
    int continua;   //Se continua = 0 as 4 threads que criei acabam
    HANDLE pMutex;
}dadosThread;


////////////
//FUNCOES:
//
DWORD WINAPI numerospares(LPVOID dados) {

    dadosThread* DADOS = (dadosThread*)dados;
    _tprintf( _T("\nTHREAD PARES- LIMITES: %d - %d!\n"), DADOS->numeroMenor, DADOS->numeroMaior );

    for (int i = (DADOS->numeroMenor); i <= (DADOS->numeroMaior); i++) {
        _tprintf(_T("CONTINUA = %d\n"), DADOS->continua);
        if (DADOS->continua == 0) {
            _tprintf(_T("MUDEIII A FLAGGGG!!!!!\n"));
            break;
        }
        else {
            Sleep(1000);
            if (i % 2 == 0) {
                DADOS->contador++;
                WaitForSingleObject(DADOS->pMutex, INFINITE);
                SomaGlobalPares = SomaGlobalPares+i;
                ReleaseMutex(DADOS->pMutex);

                if (DADOS->contador == 5) { //de 5 em 5
                   //_tprintf(_T("\n[THREAD PARES] Vou parar!\n"));
                   Sleep(500);
                }
            }
        }
    }
    _tprintf(_T("PARES:\n"));
    return 0;
}
//
//
DWORD verificaPrimo(DWORD num) {   //devolve 1 se for primo e 0 se n for
    if (num <= 1) {
        return 0;
    }
    for (DWORD i = 2; i < num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}
//
//
DWORD WINAPI numerosprimos(LPVOID dados) {

    dadosThread* DADOS = (dadosThread*)dados;
    _tprintf(_T("\nTHREAD PRIMOS- LIMITES: %d - %d!\n"), DADOS->numeroMenor, DADOS->numeroMaior);

    for (int i = (DADOS->numeroMenor); i <= (DADOS->numeroMaior); i++) {
        _tprintf(_T("CONTINUA = %d\n"), DADOS->continua);
        if (DADOS->continua == 0) {
            _tprintf(_T("MUDEIII A FLAGGGG!!!!!\n"));
            break;
        }
        else {
            Sleep(1000);
            if (verificaPrimo(i) == 1) {
                DADOS->contador++;

                WaitForSingleObject(DADOS->pMutex, INFINITE);
                SomaGlobalPrimos = SomaGlobalPrimos + i;
                ReleaseMutex(DADOS->pMutex);

                if (DADOS->contador == 5) {
                    //_tprintf(_T("\n[THREAD PRIMOS] Vou parar!\n"));
                    Sleep(500);
                }
            }
        }
    }
    _tprintf(_T("PRIMOS:\n"));
    return 0;
}

////////////
int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

    ////////////
    //VARIAVEIS:
    dadosThread dados[N_THREADS];   //array de 4 estruturas

    DWORD NT = N_THREADS;   //NT = Nmr de Threads, ATUALIZADO!
    HANDLE hThreads[N_THREADS]; //4 handles de 4 threads

    //PREENCHER ESTRUTURAS DOS PARES de 1 a 20:
    dados[0].numeroMenor = 1;
    dados[0].numeroMaior = 10;
    dados[0].contador = 0;
    dados[0].continua = 1;
    //...
    dados[1].numeroMenor = 11;
    dados[1].numeroMaior = 20;
    dados[1].contador = 0;
    dados[1].continua = 1;
    //PREENCHER ESTRUTURAS DOS PRIMOS de 21 a 40:
    dados[2].numeroMenor = 21;
    dados[2].numeroMaior = 30;
    dados[2].contador = 0;
    dados[2].continua = 1;
    //...
    dados[3].numeroMenor = 31;
    dados[3].numeroMaior = 40;
    dados[3].contador = 0;
    dados[3].continua = 1;
    
    ////////////

    HANDLE hMutex;//handler para Mutex
    hMutex = CreateMutex(
        NULL, //Parm. de seg.
        FALSE, //Sem dono
        NULL //Nome
        );


    //CRIAR 2 THREADS PARA OS PARES(0 e 1):
    for (int i = 0; i < 2; i++) {
        dados[i].pMutex = hMutex;
        hThreads[i] = CreateThread(NULL, 0, &numerospares, &dados[i], 0, NULL);
    }

    //CRIAR 2 THREADS PARA OS IMPARES(2 e 3):
    for (int i = 2; i < 4; i++) {
        dados[i].pMutex = hMutex;
        hThreads[i] = CreateThread(NULL, 0, &numerosprimos, &dados[i], 0, NULL);
    }
       
    DWORD resultado;    //recebe 'WaitForMultipleObjects()'
    int continuar;
    
    do {//Enquanto n acabarem tds as threads que criei:

        //ESPERAR Q 1 DAS THREADS TERMINE:
        resultado = WaitForMultipleObjects(NT, hThreads, FALSE, 300);    //TRUE: Espera que as 2 threads terminem //FALSE: espera so que 1 das threads termine
        //resultado = WAIT_OBJECT_0 + INDICE DA THREAD Q TERMINOU;

        if (resultado == WAIT_TIMEOUT) {//Se passou 300 Milisegundos e nenhuma das Threads terminou:

            _tprintf(_T("\n\tAinda à espera que uma das Threads acabe...\n"));
            //PRETENDE TERMINAR?
            _tprintf(_T("\nPretende TERMINAR ja? [1]-SIM | [2]-NAO\n"));
            _tcscanf_s(_T("%d"), &continuar);

            if (continuar == 1) {//Se pretender TERMINAR:
                for (int i = 0; i < NT; i++) {
                    dados[i].continua = 0;
                }
                break;
            }
        }
        else {//Se uma das Threads terminou:

            _tprintf(_T("\nTerminou a Thread[%d] ...\n"), resultado - WAIT_OBJECT_0);
            //Fechar logo essa thread:
            CloseHandle(hThreads[resultado - WAIT_OBJECT_0]);

            //Atualizar o array de Threads do indice(da thread q acabou) para a frente:
            for (DWORD i = resultado - WAIT_OBJECT_0; i < (NT - 1); i++) {
                hThreads[i] = hThreads[i + 1];
            }
            //Atualizar o Nmr. de threads que ainda estao em execucao:
            NT--;
        }

    } while (NT > 0);

    //SE QUISER PARAR A MEIO, FECHO O RESTO DAS THREADS Q ACABARAM INESPERADAMENTE:
    for (int i = 0; i < NT; i++) {
        CloseHandle(hThreads[i]);
    }

    _tprintf( _T("\nTERMINARAM TODAS AS THREADS QUE CRIEI!\n") );

    _tprintf(_T("SOMA DE NUMEROS PARES DE %d A %d: %d\n"), dados[0].numeroMenor, dados[1].numeroMaior, SomaGlobalPares);
    _tprintf(_T("SOMA DE NUMEROS PRIMOS DE %d A %d: %d\n"), dados[2].numeroMenor, dados[3].numeroMaior, SomaGlobalPrimos);

    //FECHAR MUTEX:
    CloseHandle(hMutex);

    return 0;
}
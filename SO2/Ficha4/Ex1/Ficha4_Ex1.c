#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define MAX 256

////////////
//ESTRUTURA:
typedef struct {
    int numeroMaior;
    int numeroMenor;
    int contador;
    int soma;
}dadosThread;


////////////
//FUNCOES:
//
DWORD WINAPI numerospares(LPVOID dados) {
    dadosThread* DADOS = (dadosThread*)dados;
    
    for (DWORD i = (DADOS->numeroMenor); i <= (DADOS->numeroMaior); i++) {
        if (i % 2 == 0) {
            DADOS->contador++;
            DADOS->soma += i;
            
            if (DADOS->contador == 200) {
                _tprintf( _T("\n[THREAD PARES] Vou parar!\n") );
                DADOS->contador = 0;
                //Sleep(1000);
            }
        }
    }

    return 0;
}
//
//
DWORD WINAPI numerosprimos(LPVOID dados) {

    dadosThread* DADOS = (dadosThread*)dados;

    for (DWORD i = (DADOS->numeroMenor); i <= (DADOS->numeroMaior); i++) {
        
        if (verificaPrimo(i) == 1) {
            DADOS->soma += i;
            DADOS->contador++;

            if (DADOS->contador == 15) {
                _tprintf(_T("\n[THREAD PRIMOS] Vou parar!\n"));
                DADOS->contador = 0;
                //Sleep(500);
            }
        }

    }

    return 0;
}
//
//
DWORD verificaPrimo(DWORD num) {
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


////////////
int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

    //VARIAVEIS:
    dadosThread dados[2];   //array de estruturas
    HANDLE hThreads[2]; //2 handles de 2 threads

    dados[0].numeroMaior = 3000; dados[0].numeroMenor = 500;
    dados[1].numeroMaior = 7000; dados[1].numeroMenor = 700;
    dados[0].soma = 0; dados[1].soma = 0;
    dados[0].contador = 0; dados[1].contador = 0;


    ////////////
    //CRIAR AS 2 THREADS:
    hThreads[0] = CreateThread(NULL, 0, &numerospares, &dados[0], 0, NULL);
    hThreads[1] = CreateThread(NULL, 0, &numerosprimos, &dados[1], 0, NULL);

    //ESPERAR Q AS 2 THREADS ACABEM:
    DWORD resultado = WaitForMultipleObjects(2, hThreads, FALSE, INFINITE);    //TRUE: Espera que as 2 threads terminem //FALSE: espera so que 1 das threads termine

    //ALINEA C e D:
    if (resultado - WAIT_OBJECT_0 == 0) {//Se a PARES ACABAR 1º:
        _tprintf(_T("\nTerminou a Thread [PARES]\n"));
        _tprintf(_T("NUMEROS PARES DE %d A %d: %d\n"), dados[0].numeroMenor, dados[0].numeroMaior ,dados[0].soma);
        WaitForSingleObject(hThreads[1], INFINITE);
        _tprintf(_T("\nTerminou a Thread [PRIMOS]\n"));
        _tprintf(_T("NUMEROS PRIMOS DE %d A %d: %d\n"), dados[1].numeroMenor, dados[1].numeroMaior, dados[1].soma);

    }
    else {//Se a PRIMOS ACABAR 1º:
        _tprintf(_T("\nTerminou a Thread [PRIMOS]\n"));
        _tprintf(_T("NUMEROS PRIMOS DE %d A %d: %d\n"), dados[1].numeroMenor, dados[1].numeroMaior, dados[1].soma);
        WaitForSingleObject(hThreads[0], INFINITE);
        _tprintf(_T("\nTerminou a Thread [PARES]\n"));
        _tprintf(_T("NUMEROS PARES DE %d A %d: %d\n"), dados[0].numeroMenor, dados[0].numeroMaior, dados[0].soma);
    }

    // tentar fazer ate ao H?

    /*
    do{
        //Em cada ciclo temos de diminuir o nmr de Threads e ajustar...
        resultado = WaitForMultipleObjects(nT, )
    
    }while();

    */

    //FECHAR THREADS:
    CloseHandle(hThreads[0]);
    CloseHandle(hThreads[1]);

    return 0;
}
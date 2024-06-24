
#include "..\util.h"

void welcome() {
    _tprintf_s(_T("\t\t\t ----------------------\n"));
    _tprintf_s(_T("\t\t\t  BEM-VINDO AO MONITOR\n"));
    _tprintf_s(_T("\t\t\t ----------------------\n\n"));
}

typedef struct {
    HANDLE hEv;
    SDATA* shm;
    BOOL continua;
} TDATA;


// thread que espera por uma operação recente
DWORD WINAPI OperacaoRecente(LPVOID data) {
    TDATA* td = (TDATA*)data;
    while (td->continua) {
        //ESPERA PELO EVENTO DAS OPERAÇÕES - LÊ MEMORIA PARTILHADA - IMPRIME - REPETE
        WaitForSingleObject(td->hEv, INFINITE);
        _tprintf_s(_T("\nOperacao Realizada:\n"));
        _tprintf_s(_T("Empresa: %s | Ações: %d | Valor/ação: %.2f€\n"), td->shm->recente.nome, td->shm->recente.nAcoes, td->shm->recente.preco);
    }
    return 0;
}

int _tmain(int argc, LPTSTR argv[]) {
    int r;

    TDATA tdata; //ESTRUTURA PARTILHADA COM A THREAD 

#ifdef UNICODE 
    r = _setmode(_fileno(stdin), _O_WTEXT);
    r = _setmode(_fileno(stdout), _O_WTEXT);
    r = _setmode(_fileno(stderr), _O_WTEXT);
#endif

    welcome();

    // Criação de um objeto de memória partilhada
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, NOME_MEMORIA_PARTILHADA);
    if (hMapFile == NULL) {
        _tprintf_s(_T("[Erro]: CreateFileMapping (%d)"), GetLastError());
        return 1;
    }

    SDATA* shm = (SDATA*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    // Mapeamento da memória partilhada
    if (shm == NULL) {
        _tprintf_s(_T("[Erro]: MapViewOfFile (%d)"), GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Abertura dos eventos
    HANDLE hEventServerToMonitor = OpenEvent(SYNCHRONIZE, FALSE, NOME_EVENTO_ALTERACAO_EMPRESAS);
    HANDLE hEventServerToMonitor2 = OpenEvent(SYNCHRONIZE, FALSE, NOME_EVENTO_ESCRITA_COMPLETA);
    if (hEventServerToMonitor == NULL || hEventServerToMonitor2 == NULL) {
        _tprintf_s(_T("Erro ao abrir o evento: %d\n"), GetLastError());
        return 1;
    }

    //PREENCHER ESTRUTURA
    tdata.hEv = hEventServerToMonitor2;
    tdata.shm = shm;
    tdata.continua = TRUE;
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OperacaoRecente, (LPVOID)&tdata, 0, NULL);

    do {
        //ESPERA PELA ADIÇÃO DE UMA EMPRESA - LE MEMORIA PARTILHADA - IMPRIME - REPETE
        WaitForSingleObject(hEventServerToMonitor, INFINITE);
        _tprintf_s(_T("\nEmpresa Adicionada:\n"));
        _tprintf_s(_T("Empresas Da Bolsa:\n"));
        for (int i = 0; i < shm->mercado.numEmpresas; ++i) {
            _tprintf_s(_T("Nome: %s | Açoes: %d | Preço: %.2f€\n"), shm->mercado.empresas[i].nome, shm->mercado.empresas[i].AcoesDisponiveis, shm->mercado.empresas[i].preco);
        }
    } while (1);

    tdata.continua = FALSE;
    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);
    UnmapViewOfFile(shm);
    CloseHandle(hMapFile);
    CloseHandle(hEventServerToMonitor);
    CloseHandle(hEventServerToMonitor2);

    return 0;
}
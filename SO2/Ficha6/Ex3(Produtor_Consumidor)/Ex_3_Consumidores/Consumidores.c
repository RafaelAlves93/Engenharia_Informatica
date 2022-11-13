#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <time.h>

#define NOME_MEM_PART _T("NomeMemoriaPartilhada")       // Nome da Memória Partilhada
#define NOME_MUTEX _T("NomeMutex")                      // Nome da Mutex Partilhado
#define NOME_SEM_WRITE _T("SemaforoWrite")              // Nome do Semáforo para escrita
#define NOME_SEM_READ _T("SemaforoRead")                // Nome do Semáforo para leitura

#define MAX 256
#define N 10                       // Numero maximo para o buffer

///////////////
// ESTRUTURA 1:
typedef struct _buffer { //CADA indice do buffer:
    int id;             // id do Consumidor x ('Cx')
    int val;            // Valor(aleatório entre 10 e 99) -> ITEM
}buffer;

///////////////
// ESTRUTURA 2:
typedef struct _SharedMem { //O QUE VAI ESTAR NA MEM. PART. :
    int p;                              // Contador partilhado com o numero total de produtores
    int c;                              // Contador partilhado com o numero total de consumidores
    int wP;                             // Posicao do indice do buffer circular para WRITE(Escrita)
    int rP;                             // Posicao do indice do buffer circular para READ(Leitura)

    buffer buf[N];               // BUFFER CIRCULAR
}SharedMem;

///////////////
// ESTRUTURA 3:
typedef struct {
    int continua;                   // Continua = 1 -> Thread 'produce' acaba
    int id;                         // Id do Processo (0,1,2 ,....)
    int N_intens;                   // Contador do Nmr. Total de Itens Consumidos
    int sum;                        // Somatório(basicamente o M dos consumidores)

    HANDLE hMemPart;                // HANDLE Mem.Part. Partilhada
    HANDLE hMutex;                  // HANDLE MUTEX Partilhado (p/ escrever no buffer...)
    HANDLE hWriteSem;               // Semáforo avisa escrita
    HANDLE hReadSem;                // Semáforo avisa leitura

    SharedMem* pMemPart;            // Ponteiro p/ Memoria Partilhada
}Estrutura_data;


//////////////
//FUNCÃO INICIALIZA(Mem. Part. ,....):
BOOL Inicializa(Estrutura_data* dados) {

    BOOL primeiro_processo = FALSE;

    ///
    // 0. TENTAR ABRIR MEM. PART.   (se não for o 1º) :
    dados->hMemPart = OpenFileMapping(FILE_MAP_ALL_ACCESS,               // Permissoes
        FALSE,                                                           // Herança
        NOME_MEM_PART);                                                   // Nome
    // VERIFICAÇÃO:           ( Se ainda nao criei -> ,ou seja, se for o 1 produtor: )
    if (dados->hMemPart == NULL) {  //Se ainda nao foi criado:
        primeiro_processo = TRUE;
        _tprintf(_T("Vou criar um novo Ficheiro Mapeado!\n"));

        ///
        //1. CRIAR MEM. PART. :
        dados->hMemPart = CreateFileMapping(INVALID_HANDLE_VALUE,						// P/ n estar associado a nenhum ficheiro
            NULL,									                                	// Atrib. Seg.
            PAGE_READWRITE,							                                	// Ler e Escrever (permissões)
            0,										                                	// Começa do inicio
            sizeof(SharedMem),							                                // Na Mem. Part. vai estar esta estrutura(SharedMem)
            NOME_MEM_PART);						                                   		// Nome da Mem. Partilhada
        //VERIFICAÇÃO:
        if (dados->hMemPart == NULL) {
            _tprintf(_T("[ERRO] CreateFileMapping (%d)\n"), GetLastError());
            return 1;
        }
    }
    ///
    //2. CRIAR VISTA :
    dados->pMemPart = (SharedMem*)MapViewOfFile(dados->hMemPart,                   // HANDLE Mem. Part.
        FILE_MAP_ALL_ACCESS,                                                        // Permissões
        0,                                                                          // Offset
        0,                                                                          // Offset
        sizeof(SharedMem));                                                         // Tamanho
    //VERIFICAÇÃO:
    if (dados->pMemPart == NULL) {
        _tprintf(_T("[ERRO] MapViewOfFile (%d)\n"), GetLastError());
        CloseHandle(dados->hMemPart);
        return 1;
    }

    ///
    //INICIALIZA VARIAVEIS, caso seja o 1º processo:
    if (primeiro_processo == TRUE) {
        dados->pMemPart->p = 0;                      // Contador do nmr. total de produtores
        dados->pMemPart->c = 0;                      // Contador do nmr. total de consumidores
        dados->pMemPart->wP = 0;                     // Posicao de 0 até N (=10)
        dados->pMemPart->rP = 0;                     // Posicao de 0 até N (=10)
    }

    ///
    // 3. CRIAR MUTEX:
    dados->hMutex = CreateMutex(NULL, FALSE, NOME_MUTEX);
    //VERIFICAÇÃO:
    if (dados->hMutex == NULL) {
        UnmapViewOfFile(dados->pMemPart);
        CloseHandle(dados->hMemPart);
        return 1;
    }

    ///
    // 4. CRIAR SEMAFORO para Escrita(WRITE): -> Inicialmente BUFFER c/ 10 posicoes p/ poder escrever!
    dados->hWriteSem = CreateSemaphore(NULL,        // Atrib. Seg.
        N,                                          // Valor inicial(que vai decrementando, até 0)
        N,                                          // Valor MAX. (por mt q faça releases, so incremento ate o N, n ultrapasso)
        NOME_SEM_WRITE);                            // Nome
    //VERIFICAÇÃO:
    if (dados->hWriteSem == NULL) {
        UnmapViewOfFile(dados->pMemPart);
        CloseHandle(dados->hMemPart);
        CloseHandle(dados->hMutex);
        return 1;
    }

    ///
    // 5. CRIAR SEMAFORO para Leitura(READ): -> Inicialmente BUFFER c/ 0 posicoes p/ serem lidas!
    dados->hReadSem = CreateSemaphore(NULL,        // Atrib. Seg.
        0,                                         // Valor inicial (0 posicoes para ler inicialmente)
        N,                                         // Valor MAX. (por mt q faça releases, so incremento ate o N, n ultrapasso)
        NOME_SEM_READ);                            // Nome
    //VERIFICAÇÃO:
    if (dados->hReadSem == NULL) {
        UnmapViewOfFile(dados->pMemPart);
        CloseHandle(dados->hMemPart);
        CloseHandle(dados->hMutex);
        CloseHandle(dados->hWriteSem);
        return 1;
    }


    return 0;
}
//////////////
void Mostra_Buffer(Estrutura_data* dados) {
    _tprintf(_T("\n--------"));
    _tprintf(_T("\nRESULTADO FINAL DO BUFFER:\n"));
    _tprintf(_T("--------"));
    for (int i = 0; i < N; i++) {
        _tprintf(_T("\n"));
        _tprintf(_T("P%d - ITEM= %d"), dados->pMemPart->buf[i].id, dados->pMemPart->buf[i].val);
    }
}
//////////////
//THREAD CONSOME:
DWORD WINAPI consume(LPVOID param) {

    Estrutura_data* dados = (Estrutura_data*)param;
    buffer buf;         //para onde vou copiar o q esta em cd indice do buffer
    //Inicializa somatório:
    dados->sum = 0;

    while (1) {

        //Se escrevi 'sair' basicamente:
        if (dados->continua == 1)
            break;

        _tprintf(_T("\nA espera que haja algo para ler!"));
        // 1. Ler ITEM do BUFFER:
          //Garantir que tenho posicoes para ler(SEMÁFORO READ):
        WaitForSingleObject(dados->hReadSem, INFINITE);
        _tprintf(_T("\nJA HA!!!!!\n"));
        //MUTEX P/ LER DO BUFFER:
        WaitForSingleObject(dados->hMutex, INFINITE);
            CopyMemory( &buf, &dados->pMemPart->buf[dados->pMemPart->rP], sizeof(buffer) );
            dados->pMemPart->rP = (dados->pMemPart->rP + 1) % 10;                // incremento do indice do buffer 'rP' do buffer
        ReleaseMutex(dados->hMutex);
        // 2. Incremento Nmr. de itens q já consumi:
        (dados->N_intens)++;
        // 3. Incremeto a soma(M) q é pedida no enunciado:
        dados->sum += buf.val;
        // 3. Dps de escrever -> Informo que ja podem escrever outro(SEMAFORO WRITE):
        ReleaseSemaphore(dados->hWriteSem, 1, NULL);
        
        _tprintf(_T("C%d consumiu %d\n"), dados->id, buf.val);

        Sleep(1000);
    }
    Mostra_Buffer(dados);

    return 0;
}
//////////////
int _tmain(int argc, LPTSTR argv[]) {

    srand((int)time(NULL));

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

    ///////////
    //VARIÁVEIS:
    Estrutura_data dados;
    TCHAR comando[MAX];

    ///////////
    //Inicializa valores:
    dados.continua = 0;           //  Trinco
    dados.N_intens = 0;           //  Numero de Itens que produzi

    //FUNCAO INICIALIZA:
    if (Inicializa(&dados) == 1) {
        _tprintf(_T("\n[ERRO] Erro ao Inicializar! (%d)"), GetLastError());
        return 1;
    }

    //ZONA CRITICA:
    WaitForSingleObject(dados.hMutex, INFINITE);
       dados.id = dados.pMemPart->c;       // Guardar em 'id' o nmr.(id) do produtor
       (dados.pMemPart->c)++;              // Incremento valor(nmr. total de produtores), q se encontra na MEM. PART. (daí ser preciso mutex)
    ReleaseMutex(dados.hMutex);
    _tprintf(_T("\n--CONSUMIDOR ID[%d]--\n"), dados.id);

    //Crio Thread:
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consume, &dados, 0, NULL);
    _tprintf(_T("\nEscreve 'sair' para terminar!\n"));

    do {    //Continuar em execução enquanto n escrever 'sair':
        _fgetts(comando, N, stdin);
    } while (_tcscmp(comando, _T("sair\n")) != 0);

    //DPS DE ESCREVER 'sair':
    dados.continua = 1;        //Alterar valor, para a Thread terminar
    //ESPERAR PELA THREAD:
    WaitForSingleObject(hThread, INFINITE);
    _tprintf(_T("\nC%d consumiu %d itens, somando um valor acumulado de %d.\n"), dados.id, dados.N_intens, dados.sum);

    _gettc(stdin);

    //////
    //FECHAR E APAGAR TUDO O Q CRIEI:
    CloseHandle(hThread);
    UnmapViewOfFile(dados.pMemPart);
    CloseHandle(dados.hMemPart);
    CloseHandle(dados.hMutex);
    CloseHandle(dados.hWriteSem);
    CloseHandle(dados.hReadSem);

    return 0;
}
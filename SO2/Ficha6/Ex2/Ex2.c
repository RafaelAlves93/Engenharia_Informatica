#include <io.h>
#include <Windows.h>
#include <fcntl.h>
#include <stdio.h>	
#include <stdlib.h>
#include <tchar.h>
/////////////////////////////////
#define  NOME_MEM_PART _T("NomeMemPartilhada")         //Nome da Memoria partilhada
#define  NOME_MUTEX _T("NomeMutex")					   //Nome do Mutex partilhado
#define  NOME_EVENTO _T("NomeEvento")                  //Nome do Evento partilhado
#define  NOME_SEMAFORO _T("NomeSemaforo")			   //Nome do Semaforo
#define  NOME_WAIT _T("NomeWaitableTimer")			   //Nome do Waitable Timer
#define  TAM_MSG 100                                   //Tamanho do buffer(da msg)
#define N 3

/////////////////////////////////
//ESTRUTURA 1:
typedef struct {
    TCHAR mensagem[TAM_MSG];
}estrutura_msg;

//ESTRUTURA 2:
typedef struct {
    HANDLE hMemPart;
    BOOL continua;
    HANDLE hEvento_nova_msg;
	estrutura_msg* pEstruturaMsg;
    HANDLE hMutex;
	HANDLE hTimer;
}ControlData;

/////////////////////////////////
BOOL initMemAndSync(ControlData* estrutura_data) {
	//CRIAR FICHEIRO MAPEADO:
	estrutura_data->hMemPart = CreateFileMapping(
		INVALID_HANDLE_VALUE,						// P/ n apontar p nenhum ficheiro
		NULL,										// Atrib. Seg.
		PAGE_READWRITE,								// Ler e Escrever (permissões)
		0,											// Começa do inicio
		sizeof(estrutura_msg),							// Ate ao final desta estrutura(vamos ler esta estrutura)
		NOME_MEM_PART);								// Nome da Mem. Partilhada
	//VERIFICAÇÃO:
	if (estrutura_data->hMemPart == NULL) {
		_tprintf(_T("[ERRO] CreateFileMapping (%d)\n"), GetLastError());
		return 0;
	}

	//MAPEAR VISTA:
	estrutura_data->pEstruturaMsg = (estrutura_msg*)MapViewOfFile(estrutura_data->hMemPart,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(estrutura_msg) );
	//VERIFICAÇÃO:
	if (estrutura_data->pEstruturaMsg == NULL) {
		_tprintf(_T("[ERRO] MapViewOfFile (%d)\n"), GetLastError());
		CloseHandle(estrutura_data->hMemPart);
		return 0;
	}

	//CRIAR MUTEX:
	estrutura_data->hMutex = CreateMutex(NULL,			// Atrib. Seg.
		FALSE,											// Herança
		NOME_MUTEX);									// Nome
	//VERIFICAÇÃO:
	if (estrutura_data->hMutex == NULL) { //Se correu mal:

		_tprintf(_T("ERRO AO CRIAR MUTEX (%d)\n"), GetLastError());
		UnmapViewOfFile(estrutura_data->pEstruturaMsg);
		CloseHandle(estrutura_data->hMemPart);
		return 0;
	}

	//CRIAR EVENTO
	estrutura_data->hEvento_nova_msg = CreateEvent(NULL,	// Atrib. Seg.
		TRUE,												// MANUAL RESET = TRUE| AUTO RESET = FALSE(começa 1)
		FALSE,												// Smpr FALSE
		NOME_EVENTO);										// Nome
	//VERIFICAÇÃO:
	if (estrutura_data->hEvento_nova_msg == NULL) {

		_tprintf(_T("ERRO AO CRIAR EVENTO (%d)\n"), GetLastError());
		UnmapViewOfFile(estrutura_data->pEstruturaMsg);
		CloseHandle(estrutura_data->hMemPart);
		CloseHandle(estrutura_data->hMutex);
		return 0;
	}

	//Se correu bem devolvo 1!
	return 1;
}
/////////////////////////////////
//THREAD que lê e mostra a mensagem q está na Mem. Part. :
DWORD WINAPI leMSG(LPVOID param) {

    ControlData* dados = (ControlData*) param;

	estrutura_msg est_msg;
	LARGE_INTEGER li;
	
	li.QuadPart = -1 * 10000000;  //1 Segundo
    while(1) {

        //Evento que avisa que chegou a MSG:
        WaitForSingleObject(dados->hEvento_nova_msg, INFINITE);

		if (dados->continua == 0) { //Se continua=0 saio
			return 0;
		}
		//ZONA CRITICA(assegurada com Mutex, uma vez q sao processos diferentes e a memoria é partilhada):
		WaitForSingleObject(dados->hMutex, INFINITE);
		CopyMemory( &est_msg, dados->pEstruturaMsg, sizeof(estrutura_msg) ); //Copia um bloco de memoria(est_msg = dados->pEstruturaMsg), com o tamanho sizeof(estrutura_msg)
		ReleaseMutex(dados->hMutex);

        _tprintf(_T("\n Mensagem Recebida : %s"), est_msg.mensagem);
		if ( _tcscmp(_T("fugir"), est_msg.mensagem) == 0) {
			UnmapViewOfFile(dados->pEstruturaMsg);
			CloseHandle(dados->hMemPart);
			CloseHandle(dados->hMutex);
			CloseHandle(dados->hEvento_nova_msg);
			exit (0);
		}
		//Esperar 1 seg. :
		SetWaitableTimer(dados->hTimer, &li, 0, NULL, NULL, FALSE);
		//Sleep(1000);										//Substituiu-se, na alinea 2.D)
		WaitForSingleObject(dados->hTimer, INFINITE);					//esperar que o tempo acabe
        
    }

    return 0;
}
/////////////////////////////////
//FUNCAO que escreve mensagem na Mem.Part. :
void EscreveMSG(ControlData* dados) {

	estrutura_msg est_msg;
	LARGE_INTEGER li;
	li.QuadPart = -0.5 * 10000000;	//  0.5 seg:

	while (1) {

		_getts_s(est_msg.mensagem, TAM_MSG);

		WaitForSingleObject(dados->hMutex, INFINITE);
		CopyMemory(dados->pEstruturaMsg, &est_msg, sizeof(estrutura_msg));
		ReleaseMutex(dados->hMutex);

		if (_tcscmp(est_msg.mensagem, TEXT("sair")) == 0) {
			dados->continua = 0;
		}

		SetEvent(dados->hEvento_nova_msg);
			//Esperar 0.5 seg:
			SetWaitableTimer(dados->hTimer, &li, 0, NULL, NULL, FALSE);
			//Sleep(500);										//Substituiu-se, na alinea 2.D)
			WaitForSingleObject(dados->hTimer, INFINITE);				//esperar que o tempo acabe
		ResetEvent(dados->hEvento_nova_msg);

		if (dados->continua == 0)
			break;

		if (_tcscmp(est_msg.mensagem, TEXT("fugir")) == 0)
			break;
	}
}

/////////////////////////////////
int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

	ControlData estrutura_data;
	//INICIALIZAR TUDO(EVENTO,MUTEX,MEM.PART., ...):
	if (initMemAndSync(&estrutura_data) == 0) {		//Se der erro:
		_tprintf(_T("[ERRO] ao criar/abrir Mem. Part. e a Sincronizar mecanismos...\n"));
		exit(1);
	}

	//CRIAR SEMÁFORO:
	HANDLE hSemaforo = CreateSemaphore(NULL,				// Atrib. Seg.
		N,													// Valor inicial(q vai sendo decrementado)
		N,													// Valor maximo
		NOME_SEMAFORO);										// Nome
	//VERIFICAÇÃO:
	if ( hSemaforo == NULL ) {
		_tprintf(_T("ERRO AO CRIAR SEMAFORO (%d)\n"), GetLastError());
		UnmapViewOfFile(&estrutura_data.pEstruturaMsg);
		return 0;
	}
	////
	//CRIAR WT(tempo relativo) -> ou seja, 'daqui a X seg':
	estrutura_data.hTimer = CreateWaitableTimer(NULL,				// Atrib. Seg.
		TRUE,														// TRUE = MANUAL RESET(TEMPO RELATIVO)
		NOME_WAIT);													// Nome
	//VERIFICAÇÃO:
	if (estrutura_data.hTimer == NULL) {
		_tprintf(_T("ERRO AO CRIAR WAITABLE TIMER (%d)\n"), GetLastError());
		return 0;
	}

	_tprintf(_T("\nAguardo por 1 SEMAFORO estar disponivel!\n"));

	estrutura_data.continua = 1;	//se continua = 0 saio 

	//Decrementar valor do semaforo:
	WaitForSingleObject(hSemaforo, INFINITE);
	_tprintf(_T("Entrei!\n"));
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)leMSG, &estrutura_data, 0, NULL);
	
	_tprintf( _T("Envia mensagens a outros utilizadores. Escreve 'sair' para acabar.\n") );
	EscreveMSG(&estrutura_data);
	ReleaseSemaphore(hSemaforo, 1, NULL);
	_tprintf(_T("Cliente a acabar...\n"));
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(estrutura_data.hEvento_nova_msg);
	CloseHandle(estrutura_data.hTimer);
	CloseHandle(hSemaforo);
	UnmapViewOfFile(&estrutura_data.pEstruturaMsg);

	return 0;
}
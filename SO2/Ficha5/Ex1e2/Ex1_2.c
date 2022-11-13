#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <stdio.h>
#include <fcntl.h> 
#include <io.h>

#define TAM 100

// funcionalidade relacionada com temporização

static double PerfCounterFreq; // n ticks por seg.

void initClock() {
	LARGE_INTEGER aux;
	if (!QueryPerformanceFrequency(&aux))
		_tprintf(TEXT("\nSorry - No can do em QueryPerfFreq\n"));
	PerfCounterFreq = (double)(aux.QuadPart); // / 1000.0;
	_tprintf(TEXT("\nTicks por sec.%f\n"), PerfCounterFreq);
}

__int64 startClock() {
	LARGE_INTEGER aux;
	QueryPerformanceCounter(&aux);
	return aux.QuadPart;
}

double stopClock(__int64 from) {
	LARGE_INTEGER aux;
	QueryPerformanceCounter(&aux);
	return (double)(aux.QuadPart - from) / PerfCounterFreq;
}

// estrutura de dados para controlar as threads:
typedef struct {
	unsigned int limiteSuperior;
	unsigned int limiteInferior;
	unsigned int* contadorMultiplos;//variavel q aponta p uma variavel no main e vai GERAR PROBLEMAS. vai ser a mudada
	//HANDLE pMutex; //Mutex partilhado e igual p todas as threads
	CRITICAL_SECTION* criticalSectionPartilhada;
	HANDLE eventopartilhado;
	int continua;
} TDados;

DWORD WINAPI MultiplosdeTres(LPVOID lpParam) {

	TDados* dados = (TDados*)lpParam;

	//AGUARDAM POR EVENTO P COMEÇAR:
	WaitForSingleObject(dados->eventopartilhado, INFINITE);

	_tprintf(_T("\nLIM. INF: %u"), dados->limiteInferior);
	_tprintf(_T("\nLIM. SUP: %u"), dados->limiteSuperior);

	for (unsigned int i = dados->limiteInferior; i <= dados->limiteSuperior; i++) {

		if (dados->continua == 0) {
			_tprintf(_T("\nCONTINUA = 0!\n"));
			break;
		}

		if ( (i % 3) == 0) {	//Se for multiplo de 3:
			
		//ZONA CRITICA:	
			//WaitForSingleObject(dados->pMutex, INFINITE);
			EnterCriticalSection(dados->criticalSectionPartilhada);
			( *(dados->contadorMultiplos) )++;
			//ReleaseMutex(dados->pMutex);
			LeaveCriticalSection(dados->criticalSectionPartilhada);

		}
	}

	return 0;
}

// número * máximo * de threads 20
// podem (e devem) ser menos
#define MAX_THREADS 4


int _tmain(int argc, TCHAR* argv[]) {

	// matriz de handles das threads
	HANDLE hThreads[MAX_THREADS];

	// Matriz de dados para as threads;
	TDados tdados[MAX_THREADS];

	// número efectivo(atualizado) de threads
	int numthreads;

	// limite superior
	unsigned int limsup;

	// variáveis para cronómetro
	__int64 clockticks;
	double duracao;

	unsigned int range;
	unsigned int inter;

	//VARIAVEL Q VAI SER MUDADA POR TODAS AS THREADS E VAI GERAR PROBLEMAS:
	unsigned int contadorMultiplos = 0;

	DWORD resultado;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif 

	//Variavel do handle do mutex:
	//HANDLE hMutex;
	CRITICAL_SECTION criticalSectionPartilhado;
	HANDLE evento;
	
	//Inicializar Mutex:
	//hMutex = CreateMutex(NULL, FALSE, NULL);
	BOOL res = InitializeCriticalSectionAndSpinCount( &criticalSectionPartilhado, 200 );	//spincount -> nmr. de maximo de espera ativa
	evento = CreateEvent(NULL, TRUE, FALSE, NULL);	//1º true->Dps preciso de fazer Reset() do Evento       //2ª false é o valor inicial

	initClock();
	_tprintf(TEXT("\nLimite sup. -> "));
	_tscanf_s(TEXT("%u"), &limsup);
	_tprintf(TEXT("\nNum threads -> "));
	_tscanf_s(TEXT("%u"), &numthreads);
	if (numthreads > MAX_THREADS)
		numthreads = MAX_THREADS;

	// FAZER prepara e cria threads
	//       manda as threads começar
	for (int i = 0; i < numthreads; i++) {
		tdados[i].continua = 1;
		tdados[i].contadorMultiplos = &contadorMultiplos;
		tdados[i].limiteInferior = 1 + (limsup / numthreads) * i;
		tdados[i].limiteSuperior = (limsup / numthreads)* (i+1);
		//Copiar p cd thread o handle p este mutex partilhado:
		//tdados[i].pMutex = hMutex;
		tdados[i].criticalSectionPartilhada = &criticalSectionPartilhado;
		tdados[i].eventopartilhado = evento;
		hThreads[i] = CreateThread(NULL, 0, &MultiplosdeTres, &tdados[i], CREATE_SUSPENDED, NULL);	//Criar todas em modo suspenso, ou seja, ficam tds paradas

	}

	clockticks = startClock();
	// FAZER aguarda / controla as threads 
	//       manda as threads parar
//COMEÇAR AS THREADS AO MM TEMPO:
	for (int i = 0; i < numthreads; i++) {
		ResumeThread(hThreads[i]);
	}
	SetEvent(evento);

	TCHAR palavra[TAM];

	do {

		_tprintf(_T("\nDigite 'fim' se pretender sair!"));
		_tscanf_s(_T("%s"), &palavra);
		if (_tcscmp(_T("fim\n"), palavra) == 0) {
			for (int i = 0; i < numthreads; i++) {
				tdados[i].continua = 0;
			}
			break;
		}

		//esperar p uma das threads que criei:
		resultado = WaitForMultipleObjects(numthreads, hThreads, FALSE, INFINITE);			// FALSE-> Esperar que 1 delas termine
		_tprintf(_T("\nTerminou a thread [%d]..."), resultado - WAIT_OBJECT_0);
		CloseHandle(hThreads[resultado - WAIT_OBJECT_0]);
		for (int i = resultado - WAIT_OBJECT_0; i < numthreads - 1; i++) {
			hThreads[i] = hThreads[i + 1];
		}
		numthreads--;
	} while (numthreads > 0);


	//Apresenta resultados:
	duracao = stopClock(clockticks);
	_tprintf(TEXT("\nSegundos=%f\n"), duracao);
	_tprintf(TEXT("\nContador Global=%d\n"), contadorMultiplos);


	//Terminar as Threads q estiverem em execucao:
	for (int i = 0; i < numthreads; i++) {
		CloseHandle(hThreads[i]);
	}

	//Terminar Mutex:
	//CloseHandle(pMutex);
	DeleteCriticalSection(&criticalSectionPartilhado);
	CloseHandle(evento);

	return 0;
}

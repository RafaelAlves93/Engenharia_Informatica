#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#define N 10
#define PIPE_NAME TEXT("\\\\.\\pipe\\teste")

typedef struct {
	HANDLE hInstancia;		//Handle para a instancia no NP
	OVERLAPPED overlap;		//estrutura overlap
	BOOL activo;			//verificar o estado
}DadosPipe;

typedef struct {
	DadosPipe hPipes[N];	//para cada pipe uma estrutura que contem handle pipe, ED overlao e o estado
	HANDLE hEvents[N];		//Array de eventos
	HANDLE hMutex;			//handle do mutex
	int terminar;			//trinco
}ThreadDados;

DWORD WINAPI ThreadMensagens(LPVOID param) {
	TCHAR buf[256];
	DWORD n;
	int i;
	ThreadDados* dados = (ThreadDados*)param;

	do {
		_tprintf(TEXT("[ESCRITOR] Frase: "));
		_fgetts(buf, 256, stdin);
		buf[_tcslen(buf) - 1] = '\0';
		for (i = 0; i < N; i++) { 
			WaitForSingleObject(dados->hMutex, INFINITE);
			if (dados->hPipes[i].activo) {
				if(!WriteFile(dados->hPipes[i].hInstancia, buf, _tcslen(buf)* sizeof(TCHAR), &n, NULL))
					_tprintf(TEXT("[ERRO] Escrever no pipe! (WriteFile)\n"));
				else
					_tprintf(TEXT("[ESCRITOR] Enviei %d bytes ao leitor [%d]... (WriteFile)\n"), n, i);
			}
			ReleaseMutex(dados->hMutex);
		}
	} while (_tcscmp(buf, TEXT("fim")));
	dados->terminar = 1;
	for (i = 0; i < N; i++)
		SetEvent(dados->hEvents[i]);
	return 0;
}

int _tmain(int argc, LPTSTR argv[]) {
	ThreadDados dados;
	HANDLE hPipe, hThread, hEventTemp;
	int i, numClientes = 0;
	DWORD offset, nBytes;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif // UNICODE

	dados.terminar = 0;
	dados.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (dados.hMutex == NULL) {
		_tprintf(TEXT("[ERRO] Criar Mutex! (CreateMutex)\n"));
		exit(-1);
	}
	for (i = 0; i < N; i++) {
		_tprintf(TEXT("[ESCRITOR] Criar uma cópia do pipe '%s' ... (CreateNamedPipe)\n"), PIPE_NAME);
		//true para o evento estar sinalizado
		hEventTemp = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (hEventTemp == NULL) {
			_tprintf(TEXT("[ERRO] Criar Evento! (CreateEvent)\n"));
			exit(-1);
		}
		hPipe = CreateNamedPipe(PIPE_NAME,
			PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
			PIPE_WAIT | PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
			N, 256 * sizeof(TCHAR), 256 * sizeof(TCHAR), 1000, NULL);

		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(TEXT("[ERRO] Criar Named Pipe! (CreateNamedPipe)\n"));
			exit(-1);
		}
		//ZeroMemory(destino, tamanho)
		//conforme a documentação meter a memoria a estrutura overlap a zero
		ZeroMemory(&dados.hPipes[i].overlap, sizeof(dados.hPipes[i].overlap));
		dados.hPipes[i].hInstancia = hPipe;		//handle do pipe
		dados.hPipes[i].overlap.hEvent = hEventTemp;	//handle do evento (dentro da estrutura)
		dados.hEvents[i] = hEventTemp;		//handle do evento
		dados.hPipes[i].activo = FALSE;		//flag de sinalizaçao

		//o segundo parametro é o ponteiro para a estrutura de dados overlap
		if (ConnectNamedPipe(hPipe, &dados.hPipes[i].overlap)) {
			_tprintf(TEXT("[ERRO] Ligar ao leitor! (ConnectNamedPipe)\n"));
			exit(-1);
		}
	}

	hThread = CreateThread(NULL, 0, ThreadMensagens, &dados, 0, NULL);

	if (hThread == NULL) {
		_tprintf(TEXT("[ERRO] Criar Thread! (CreateThread)\n"));
		exit(-1);
	}

	while (!dados.terminar && numClientes < N) {
		_tprintf(TEXT("[ESCRITOR] Esperar ligação de um leitor...\n"));

		//3º parametro FALSE, the function returns when the state of any one of the objects is set to signaled
		offset = WaitForMultipleObjects(N, dados.hEvents, FALSE, INFINITE);
		i = offset - WAIT_OBJECT_0;

		if (i >= 0 && i < N) {
			_tprintf(TEXT("[ESCRITOR] Leitor %d chegou...\n"), i);
			//identificador para o ficheiro named pipe 
			//ponteiro para a estrutura overlap
			//ponteiro para uma variavel que recebe o numero de bytes
			//true -> se estiver a true e o membro interno da estrutura lpOverlaped for STATUS_PENDING, a funcao nao retornara
			//false -> e a operaçao ainda estiver pendente, a funcao retornara FALSE e a funcao GetLastError retornara ERROR_I

			if (GetOverlappedResult(dados.hPipes[i].hInstancia,
				&dados.hPipes[i].overlap, &nBytes, FALSE)) {

				ResetEvent(dados.hEvents[i]);
				WaitForSingleObject(dados.hMutex, INFINITE);
				dados.hPipes[i].activo = TRUE;
				ReleaseMutex(dados.hMutex);
			}
			numClientes++;
		}
	}

	WaitForSingleObject(hThread, INFINITE);

	for (i = 0; i < N; i++) {
		_tprintf(TEXT("[ESCRITOR] Desligar o pipe (DisconnectNamedPipe)\n"));

		if (!DisconnectNamedPipe(dados.hPipes[i].hInstancia)) {
			_tprintf(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)\n"));
			exit(-1);
		}
		CloseHandle(dados.hPipes[i].hInstancia);
	}

	return 0;
}
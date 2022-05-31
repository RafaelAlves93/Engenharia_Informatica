#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

//https://docs.microsoft.com/en-us/windows/win32/ipc/pipe-names

#define MAX_CLI 10
#define BUF_SIZE 256
#define PIPE_NAME TEXT("\\\\.\\pipe\\teste")

typedef struct {
	HANDLE hPipes[MAX_CLI];
	HANDLE hMutex;
	int numClientes;
	int terminar;
}ThreadDados;

DWORD WINAPI ThreadMensagens(LPVOID param) {
	TCHAR buf[BUF_SIZE];
	DWORD n;
	int i;
	ThreadDados* dados = (ThreadDados*)param;

	do {
		_tprintf(TEXT("[ESCRITOR] Frase: "));
		_fgetts(buf, BUF_SIZE, stdin);
		buf[_tcslen(buf) - 1] = '\0';

		WaitForSingleObject(dados->hMutex, INFINITE);

		for (i = 0; i < dados->numClientes; i++) {
			if (!WriteFile(dados->hPipes[i], buf, _tcslen(buf) * sizeof(TCHAR), &n, NULL)) {
				_tprintf(TEXT("[ERRO] Escrever no pipe! (WriteFile)\n"));
				exit(-1);
			}
			_tprintf(TEXT("[ESCRITOR] Enviei %d bytes ao leitor [%d]... (WriteFile]\n"), n, i);
		}

		ReleaseMutex(dados->hMutex);

	} while (_tcscmp(buf, TEXT("fim")));

	dados->terminar = 1; //BATOTA

	//Workaround para desbloquear a main! Overlapped I/O permite uma melhor soluçao...
	CreateFile(PIPE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	return 0;
}

int _tmain(int argc, LPSTR argv[]) {
	ThreadDados dados;
	HANDLE hPipe, hThread;
	int i;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif // UNICODE

	dados.numClientes = 0;
	dados.terminar = 0;

	dados.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (dados.hMutex == NULL) {
		_tprintf(TEXT("[ERRO] Criar Mutex! (CreateMutex)\n"));
		exit(-1);
	}

	hThread = CreateThread(NULL, 0, ThreadMensagens, &dados, 0, NULL);

	if (hThread == NULL) {
		_tprintf(TEXT("[ERRO] Criar Thread! (CreateThread)\n"));
		exit(-1);
	}

	while (!dados.terminar) {
		_tprintf(TEXT("[ESCRITOR] Criar uma cópia do pipe '%s' ... (CreateNamedPipe)\n"), PIPE_NAME);

		hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_OUTBOUND,
			PIPE_WAIT | PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
			MAX_CLI, sizeof(TCHAR) * BUF_SIZE, sizeof(TCHAR) * BUF_SIZE, 1000, NULL);

		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(TEXT("[ERRO] Criar Named Pipe! (CreateNamedPipe)\n"));
			exit(-1);
		}

		_tprintf(TEXT("[ESCRITOR] Esperar ligação ao leitor! (ConnectNamedPipe)\n"));

		if (!ConnectNamedPipe(hPipe, NULL)) {
			_tprintf(TEXT("[ERRO] Ligação ao leitor! (ConnectNamedPipe)\n"));
			exit(-1);
		}

		WaitForSingleObject(dados.hMutex, INFINITE);
		dados.hPipes[dados.numClientes] = hPipe;
		dados.numClientes++;
		ReleaseMutex(dados.hMutex);
	}

	WaitForSingleObject(hThread, INFINITE);

	for (i = 0; i < dados.numClientes; i++) {
		_tprintf(TEXT("[ESCRITOR] Desligar o pipe (DisconnectNamedPipe)\n"));

		if (!DisconnectNamedPipe(dados.hPipes[i])) {
			_tprintf(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)\n"));
			exit(-1);
		}
		CloseHandle(dados.hPipes[i]);
	}

	return 0;
}
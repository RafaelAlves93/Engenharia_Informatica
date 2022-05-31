#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

//https://docs.microsoft.com/en-us/windows/win32/ipc/pipe-names
#define PIPE_NAME TEXT("\\\\.\\pipe\\teste")

int _tmain(int argc, LPTSTR argv[]) {
	DWORD n;
	HANDLE hPipe;
	TCHAR buf[256];

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif // UNICODE

	_tprintf(TEXT("[ESCRITOR] Criar uma cópia do pipe '%s' ... (CreateNamedPipe)\n"), PIPE_NAME);
	hPipe = CreateNamedPipe(PIPE_NAME,
							PIPE_ACCESS_OUTBOUND,
							PIPE_WAIT | PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
							2, sizeof(buf), sizeof(buf), 1000, NULL);

	if (hPipe == INVALID_HANDLE_VALUE) {
		_tprintf(TEXT("[ERRO] Criar Named Pipe! (CreateNamedPipe"));
		exit(-1);
	}

	while (1) {
		_tprintf(TEXT("[ESCRITOR] Esperar ligação de um leitor... (ConnectNamedPipe)\n"));
		if (!ConnectNamedPipe(hPipe, NULL)) {
			_tprintf(TEXT("[ERRO] Ligação ao leitor! (ConnectNamedPipe\n"));
			exit(-1);
		}
		
		do {
			_tprintf(TEXT("[ESCRITOR] Frase: "));
			_fgetts(buf, 256, stdin);
			buf[_tcslen(buf) - 1] = '\0';

			if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &n, NULL)) {
				_tprintf(TEXT("[ERRO] Escrever no pipe! (WriteFile)\n"));
				exit(-1);
			}
			_tprintf(TEXT("[EXCRITOR] Enviei %d bytes ao leitor... (WriteFile)\n"), n);
		} while (_tcscmp(buf, TEXT("FIM")));

		_tprintf(TEXT("[ESCRITOR] Desligar o pipe (DisconnectNamedPipe)\n"));

		if (!DisconnectNamedPipe(hPipe)) {
			_tprintf(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)\n"));
			exit(-1);
		}
	}
	Sleep(2000);
	CloseHandle(hPipe);
	return 0;
}
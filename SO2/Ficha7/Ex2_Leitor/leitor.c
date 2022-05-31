#include <Windows.h>
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
	int i = 0;
	BOOL ret;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif // UNICODE

	_tprintf(TEXT("\n[LEITOR] Esperar pelo pipe %s\n"), PIPE_NAME);
	if (!WaitNamedPipe(PIPE_NAME, NMPWAIT_WAIT_FOREVER)) {
		_tprintf(TEXT("\nErro a ligar ao pipe"));
		exit(-1);
	}

	hPipe = CreateFile(PIPE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == NULL) {
		_tprintf(TEXT("\nErro a abrir o pipe"));
		exit(-1);
	}

	while (1) {
		ret = ReadFile(hPipe, buf, sizeof(buf), &n, NULL);
		buf[n / sizeof(TCHAR)] = '\0';

		if (!ret || !n) {
			_tprintf(TEXT("[LEITOR] %d %d ... (ReadFile)\n"), ret, n);
			break;
		}
		_tprintf(TEXT("LEITOR: recebi %d bytes: [%s]\n"), n, buf);
	}
	CloseHandle(hPipe);
	Sleep(200);
	return 0;
}
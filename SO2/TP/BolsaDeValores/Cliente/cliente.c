
#include "..\util.h"

void welcome() {
    _tprintf_s(_T("\t\t\t -------------------\n"));
    _tprintf_s(_T("\t\t\t  BEM-VINDO CLIENTE\n"));
    _tprintf_s(_T("\t\t\t -------------------\n\n"));
}


int _tmain(int argc, LPTSTR argv[]) {
    int r;
    TCHAR cmd[256];
    HANDLE hPipe;
    DWORD nbytes;

#ifdef UNICODE 
    r = _setmode(_fileno(stdin), _O_WTEXT);
    r = _setmode(_fileno(stdout), _O_WTEXT);
    r = _setmode(_fileno(stderr), _O_WTEXT);
#endif
    welcome();

    if (!WaitNamedPipe(NOME_PIPE, NMPWAIT_WAIT_FOREVER)) {
        _tprintf_s(_T("[ERRO] Servidor não está em execução!\n"));
        return 1;
    }

    hPipe = CreateFile(NOME_PIPE, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hPipe == NULL) {
        _tprintf_s(_T("[ERRO] Ligação ao pipe!\n"));
        return 1;
    }
    _tprintf(_T("[CLIENTE] Conectei-me ao pipe\n"));

    while (1) {
        //Ciclo para ler comandos
        _tprintf_s(_T("Comando: "));
        _fgetts(cmd, 256, stdin);
        cmd[_tcsclen(cmd) - 1] = _T('\0');
        if (_tcscmp(cmd, _T("exit")) == 0) {
            if (!WriteFile(hPipe, cmd, (DWORD)_tcslen(cmd) * sizeof(TCHAR), &nbytes, NULL)) {
                _tprintf(_T("[ERRO] Escrever no pipe!\n"));
                exit(1);
            }
            break;
        }

        if (!WriteFile(hPipe, cmd, (DWORD)_tcslen(cmd) * sizeof(TCHAR), &nbytes, NULL)) {
            _tprintf(_T("[ERRO] Escrever no pipe!\n"));
            exit(1);
        }
        _tprintf(_T("Escrevi no pipe a msg [%s]\n"), cmd);

        if (!ReadFile(hPipe, &cmd, sizeof(cmd), &nbytes, NULL)) {
            _tprintf(_T("[ERRO] Ler pipe!\n"));
            exit(-1);
        }
        cmd[nbytes / sizeof(TCHAR)] = '\0';
        _tprintf_s(_T("[MSG BOLSA] %s\n"), cmd);
    }
    CloseHandle(hPipe);
    return 0;
}

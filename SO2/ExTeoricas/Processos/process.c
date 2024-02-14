#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#define MAX 256


int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif

    BOOL res;
    TCHAR cmd[MAX] = _T("notepad.exe");
    TCHAR erro[MAX];
    DWORD valor, codigo;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);


    res = CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    codigo = GetLastError();
    
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, codigo, LANG_USER_DEFAULT, erro, MAX, NULL);
    _tprintf_s(_T("[ERRO] %d - %s"), codigo, erro);

    _tprintf_s(_T("[INICIO]\n"));

    for (int i = 0; i < 5;i++) {
        Sleep(1000);
        _tprintf_s(_T("."));
    }
    _tprintf_s(_T("\n"));
    _tprintf_s(_T("[FIM]\n"));

    //Aguarda ate que o filho termine
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &valor);
    _tprintf_s(_T("Sou o %d, o meu filho %d terminou %d\n"), GetCurrentProcessId(), valor, pi.dwProcessId);
    
    ExitProcess(0);
}
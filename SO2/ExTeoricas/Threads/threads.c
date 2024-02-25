#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>


typedef struct {
    TCHAR letra;
    BOOL continua;
}TDATA;


//FUNCAO
DWORD WINAPI mostra(LPVOID tdata) {
    TDATA* td = (TDATA*)tdata;

    while (td->continua) {
        _tprintf_s(_T("%c"), td->letra);
        Sleep(1000);
    }
    ExitThread(7);
}

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif

    HANDLE hTread[2];
    DWORD tid[2], codigo;
    TDATA tData[2];

    tData[0].letra = _T('A');
    tData[0].continua = TRUE;

    hTread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mostra, (LPVOID)&tData[0], 0, &tid[0]);

    tData[1].letra = _T('B');
    tData[1].continua = TRUE;

    hTread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mostra, (LPVOID)&tData[1], 0, &tid[1]);

    tData[0].continua = FALSE;
    WaitForSingleObject(hTread[0], INFINITE);
    GetExitCodeThread(hTread[0], &codigo);

    tData[1].continua = FALSE;
    WaitForSingleObject(hTread[1], INFINITE);
    GetExitCodeThread(hTread[1], &codigo);


    ExitProcess(0);
}
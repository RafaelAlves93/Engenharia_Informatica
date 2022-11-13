//Crie um projeto novo e, utilizando as fun��es da Windows API CreateProcess e GetModuleFileName e estruturas do tipo 
//PROCESS_INFORMATION e STARTUP_INFO, execute as seguintes a��es:
//b) Modifique o programa de forma a que pe�a ao utilizador o nome de um outro programa(ficheiro execut�vel) que � 
//posteriormente executado no contexto de um novo processo, mantendo - se o seu programa em execu��o e repetindo o 
//comportamento at� o utilizador desejar sair.

#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define MAX 256

int _tmain(int argc, LPTSTR argv[]) {
	PROCESS_INFORMATION pi;
	STARTUPINFO si;


#ifdef UNICODE 
	_setmode(_fileno(stdin), _O_WTEXT);     //->0
	_setmode(_fileno(stdout), _O_WTEXT);    //->1    STDERR ->2
#endif

	TCHAR nomePrograma[MAX];
	do {
		_tprintf(TEXT("Introduza o programa que quer abrir: \n"));
		_fgetts(nomePrograma, MAX, stdin);
		nomePrograma[_tcslen(nomePrograma) - 1] = '\0';
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(NULL, nomePrograma, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
			_tprintf(TEXT("Programa lan�ado\n"));
		else
			_tprintf(TEXT("Ocorreu um erro\n"));
	} while (_tcscmp(TEXT("fim"), nomePrograma));
	return 0;
}
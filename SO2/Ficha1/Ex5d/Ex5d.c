//Crie um projeto novo e, utilizando as funções da Windows API CreateProcess e GetModuleFileName e estruturas do tipo 
//PROCESS_INFORMATION e STARTUP_INFO, execute as seguintes ações:
//d) Modifique o programa de forma a que deixe de pedir nome de programas a executar e simplesmente se execute novamente
//mais 3 vezes.Cada nova execução lança a seguinte(apenas uma de cada vez), criando uma cadeira de execuções que pára na 
//quarta execução.O comportamento é automático e não requer a intervenção do utilizador.Cada execução deve indicar uma 
//mensagem que permita distingui-la das restantes.

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>

#define MAX 256

int _tmain(int argc, LPTSTR argv[]) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR text[256];
	int vezes;

	//UNICODE: Por defeito, a consola Windows não processa caracteres wide.
	//A maneira mais fácil para ter esta funcionalidade é chamar _setmode:
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	
	GetModuleFileName(NULL, text, 256);

	if (argc == 1)
		vezes = 3;
	else
		vezes = _ttoi(argv[1]);

	if (vezes > 0) {
		_tprintf(TEXT("Faltam %d execuções\n"), vezes);
		vezes--;
		_stprintf_s(text, 256, TEXT("%s %d"), text, vezes);
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if (!CreateProcess(NULL, text, NULL, NULL, FALSE, FALSE, NULL, NULL, &si, &pi))
			_tprintf(TEXT("Erro ao lancar processo."));
	}
	return 0;
}
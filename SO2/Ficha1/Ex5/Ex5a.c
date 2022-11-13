//Crie um projeto novo e, utilizando as fun��es da Windows API CreateProcess e GetModuleFileName e estruturas do tipo 
//PROCESS_INFORMATION e STARTUP_INFO, execute as seguintes a��es:
//a) Fa�a com que o programa apresente no ecr� o nome do ficheiro execut�vel que lhe corresponde.

#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define MAX 256

//TCHAR *argv[]
int _tmain(int argc, LPTSTR argv[]) {
	TCHAR nome[MAX];
	unsigned int size;	//DWORD size;

#ifdef UNICODE 
	_setmode(_fileno(stdin), _O_WTEXT);     //->0
	_setmode(_fileno(stdout), _O_WTEXT);    //->1    STDERR ->2
#endif

		//ALINEA A
		size = GetModuleFileName(NULL, nome, MAX);
		DWORD error = GetLastError();
		_tprintf(TEXT("[%d] - O meu file �: %s\n"), size, nome);
		
		return 0;
}
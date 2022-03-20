//Crie um projeto novo e, utilizando as funções da Windows API CreateProcess e GetModuleFileName e estruturas do tipo 
//PROCESS_INFORMATION e STARTUP_INFO, execute as seguintes ações:
//c) Acrescente a possibilidade de o utilizador especificar um argumento a passar ao outro programa.Teste essa funcionalidade 
//mandando executar o programa notepad passando - lhe o nome de um ficheiro de texto.Se tudo estiver a funcionar, o notepad é 
//executado abrindo o ficheiro indicado.

#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define MAX 256

int _tmain(int argc, LPTSTR argv[]) {
#ifdef UNICODE 
	_setmode(_fileno(stdin), _O_WTEXT);     //->0
	_setmode(_fileno(stdout), _O_WTEXT);    //->1    STDERR ->2
#endif


	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	unsigned int size; //DWORD size;
	TCHAR nomePrograma[MAX], parametro[MAX];


	do {
		_tprintf(TEXT("Introduza o programa que quer abrir: \n"));
		_fgetts(nomePrograma, MAX, stdin);
		nomePrograma[_tcslen(nomePrograma) - 1] = '\0';
		if(_tcscmp(TEXT("fim"), nomePrograma))
		{
			fflush(stdin);
			_tprintf(TEXT("Introduza o parametro\n"));
			_fgetts(parametro, MAX, stdin);
			parametro[_tcslen(parametro) - 1] = '\0';
			_tcscat_s(nomePrograma, MAX, TEXT(" "));
			_tcscat_s(nomePrograma, MAX, parametro);
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);
			if (!CreateProcess(NULL, nomePrograma, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
				_tprintf(TEXT("Programa lançado\n"));
			else
				_tprintf(TEXT("Ocorreu um erro\n"));
		}
		WaitForSingleObject(pi.hProcess, INFINITE);		//wait (pid)    | ESTA LINHA NAO ERA PEDIDA NO ENUNCIADO O PROF QUIS UTILIZAR O "WAIT"!!!  
	} while (_tcscmp(TEXT("fim"), nomePrograma));
	return 0;
}
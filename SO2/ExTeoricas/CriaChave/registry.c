#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>

#define TAM 20

int _tmain(int argc, LPTSTR argv[]) {
	TCHAR texto[TAM];
	TCHAR utilizador[40] = _T("Rafa");
	LSTATUS res;
	DWORD estado, tipo, tamanho;
	HKEY hkey;


#ifdef UNICODE 
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	//CRIAR A CHAVE
	res = RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\Aula\\SO2"), 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &estado);
	if (res == ERROR_SUCCESS) {
		if (estado == REG_CREATED_NEW_KEY) {
			_tprintf(_T("Criei a chave HKEY_CURRENT_USER\\Software\\Aula\\SO2\n"));
		}
		else if (estado == REG_OPENED_EXISTING_KEY) {
			//CONSULTAR A CHAVE
			_tprintf(_T("Abri a chave HKEY_CURRENT_USER\\Software\\Aula\\SO2\n"));
			tamanho = sizeof(texto);
			res = RegQueryValueEx(hkey, _T("utilizador"), 0, &tipo, (LPBYTE)&texto, &tamanho);
			if (res == ERROR_SUCCESS) {
				_tprintf(_T("Utilizador = %s(%d)\n"), texto, tipo);
			}
			RegCloseKey(hkey);
		}


		res = RegSetValueEx(hkey, _T("utilizador"), 0, REG_SZ, (LPBYTE)utilizador, (DWORD)(_tcslen(utilizador) + 1) * sizeof(TCHAR));
		if (res == ERROR_SUCCESS) {
			_tprintf(_T("Utilizador = %s\n"), utilizador);
		}
		else {
			_tprintf(_T("[ERRO] no create key!!\n"));
		}
		RegCloseKey(hkey);
	}
	return 0;
}
//escreve.c
//SEM MUTEX


#include "header.h"


int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hsemItens, hsemVazios, hmap;
	DADOS* pshm;
	TCHAR letra;
	int i = 0;

	_tprintf(_T("INICIO PRODUTOR!\n"));

	hsemItens = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, nome_semaforo_itens);
	hsemVazios = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, nome_semaforo_vazios);
	hmap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, nome_shm);

	pshm = (DADOS*)MapViewOfFile(hmap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(DADOS));

	
	_tprintf(_T("TEXTO= "));
	do {
		letra = _gettch();
		WaitForSingleObject(hsemVazios, INFINITE);
		pshm->str[pshm->in] = letra;
		pshm->in = (pshm->in + 1) % TAM;
		ReleaseSemaphore(hsemItens, 1, NULL);
		_tprintf(_T("%c"), letra);
		i = (i + 1) % (TAM - 1);
	} while (letra != _T('x'));

	_tprintf(_T("FIM!!\n"));
	UnmapViewOfFile(pshm);
	CloseHandle(hmap);
	CloseHandle(hsemItens);
	CloseHandle(hsemVazios);
	return 0;
}
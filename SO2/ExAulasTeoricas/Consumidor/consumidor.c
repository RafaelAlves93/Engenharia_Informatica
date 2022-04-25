//le.c
//SEM MUTEX


#include "header.h"

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hsemItens, hsemVazios;
	HANDLE hmap;
	DADOS* pshm;
	TCHAR letra;


	_tprintf(_T("INICIO CONSUMIDOR!\n"));

	hsemItens = CreateSemaphore(NULL, 0, TAM, nome_semaforo_itens);
	hsemVazios = CreateSemaphore(NULL, TAM, TAM, nome_semaforo_vazios);
	hmap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(DADOS), nome_shm);
	pshm = (DADOS*)MapViewOfFile(hmap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(DADOS));
	

	pshm->in = 0;
	pshm->out = 0;

	pshm->str[TAM - 1] = _T('\0');

	do {
		Sleep(1000);
		WaitForSingleObject(hsemItens, INFINITE);
		letra = pshm->str[pshm->out];
		pshm->out = (pshm->out + 1) % TAM;
		ReleaseSemaphore(hsemVazios, 1, NULL);
		_tprintf(_T("LETRA = '%c'\n"), letra);
	} while (letra != _T('x'));
	_tprintf(_T("FIM!!\n"));

	UnmapViewOfFile(pshm);
	CloseHandle(hmap);
	CloseHandle(hsemItens);
	CloseHandle(hsemVazios);
	return 0;
}
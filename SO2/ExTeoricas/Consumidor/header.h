#pragma once

#include <windows.h>
#include <tchar.h>

#define TAM 20
//#define Nome_mutex _T("mutex")
#define nome_shm _T("memoria")
#define nome_semaforo_itens _T("sem_itens")
#define nome_semaforo_vazios _T("sem vazios")


typedef struct {
	int in, out;
	TCHAR str[TAM];
}DADOS;

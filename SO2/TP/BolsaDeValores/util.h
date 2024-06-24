#include <io.h>
#include <Windows.h>
#include <fcntl.h>
#include <stdio.h>	
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <conio.h>

#define NOME_PIPE _T("\\\\.\\pipe\\pipe_bolsa")
#define NOME_MEMORIA_PARTILHADA _T("SharedMemory")
#define NOME_EVENTO_SERVIDOR_MONITOR _T("EventoServidorMonitor")
#define NOME_EVENTO_ALTERACAO_EMPRESAS _T("EventAlteracaoEmpresas")
#define NOME_EVENTO_ESCRITA_COMPLETA _T("EventEscritaCompleta")
#define MAX_UTILIZADORES 20		
#define MAX_EMPRESAS 30
#define BUFFER 512
#define MAX_CLIENTES 5     //numero maximo de clientes (processos) que o servidor pode atender
#define TAM 50

#define NOME_MUT_UM_SERVIDOR _T("Um_Servidor")				// Nome do Mutex que garante que so ha 1 Servidor

typedef struct {
	HANDLE hMutex;											// HANDLE do Semaforo que garante que so ha 1 Servidor
	HANDLE hFile;											// HANDLE do ficheiro de log
	HANDLE hPipe;											// HANDLE do pipe			
	DWORD cliLigados;										// Numero de clientes ligados
} Controlo;

typedef struct {
	TCHAR empresa[TAM];
	DWORD nAcoes;
} Carteira;

typedef struct {
	TCHAR username[TAM];
	TCHAR password[TAM];
	float saldo;
	DWORD ligado;											// 1 ligado, 0 desligado
	Carteira carteira[5];									//Carteira de Ações
	DWORD nCarteira;										//Numero de diferentes empresas presentes na carteira
	DWORD id_cliente;										//id do cliente (igual ao id da thread AtendeCliente
} Utilizador;

typedef struct {
	DWORD numUtilizadores;
	Utilizador utilizadores[MAX_UTILIZADORES];
} Cliente;

typedef struct {
	TCHAR nome[TAM];
	DWORD AcoesDisponiveis;
	float preco;
} Empresa;

typedef struct {
	DWORD numEmpresas;
	Empresa empresas[MAX_EMPRESAS];
} Mercado;

typedef struct {
	TCHAR nome[TAM];
	DWORD nAcoes;
	float preco;
} Operacao;

typedef struct {
	Operacao recente;
	Mercado mercado;
	BOOL continua;
} SDATA;



int PauseCommand(LPVOID param, DWORD segundos);
DWORD WINAPI Input(LPVOID data);
DWORD WINAPI AtendeCliente(LPVOID data);
BOOL inicializaServidor(Controlo* dados);
void welcome();
BOOL registoChave();
BOOL InicializaClientes(Cliente* pc, TCHAR* nome_fich);
BOOL inicializaEmpresas(Mercado* pe, TCHAR* nome_fich);
DWORD WINAPI OperacaoRecente(LPVOID data);



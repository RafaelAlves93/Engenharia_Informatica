#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define MAX 256


int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

    //////////////////////////
    //1.ABRIR O FICHEIRO:
    HANDLE hFicheiro = CreateFile(_T("alfabeto.txt"),       // Nome do ficheiro
        GENERIC_READ | GENERIC_WRITE,                // Tipo de acesso(o que quero fazer ao ficheiro)
        FILE_SHARE_READ | FILE_SHARE_WRITE,          // Acesso partilhado?
        NULL,                                        // Atributos de Seg.
        CREATE_NEW | OPEN_EXISTING,                  // Criar ou Abrir(se ja existir) Ficheiro
        FILE_ATTRIBUTE_NORMAL,                       //
        NULL);                                       //
    //VERIFICACOES:
    if (hFicheiro == INVALID_HANDLE_VALUE)  //Se correu mal:
        _tprintf(_T("\nErro ao Criar/Abrir Ficheiro- %d \n"), GetLastError());
    else                                    //Se abriu corretamente:
        _tprintf(_T("\nFicheiro Aberto/Criado Corretamente!\n"));


    //////////////////////////
    //2.Mapear o Ficheiro na Memoria:
    HANDLE hMemPart = CreateFileMapping(hFicheiro,       // Handle(ponteiro) para o ficheiro
        NULL,                                                       // Atributos de Seg.
        PAGE_READWRITE,                                     // Permissoes(ler e escrever) das vistas
        0,                                                           // Tamanho maximo deste ficheiro mapeado
        26,                                                          // Tamanho do buffer
        _T("Mem_Partilhada"));                                     // Nome deste pedaço de memoria partilhada
    //VERIFICACOES:
    if (hMemPart == NULL)
        _tprintf(_T("\nErro ao criar Mem. Part.- %d\n"), GetLastError());
    else
        _tprintf(_T("\nMem. Part. criada\n"));


    //////////////////////////
    //3.Criar Vista:
    char* pVistaFicheiro = (char*)MapViewOfFile(
        hMemPart,                                        // Handle(ponteiro) para a memoria partilhada
        FILE_MAP_READ | FILE_MAP_WRITE,                  // Modo de acesso
        0,                                               // Se estes 2 forem 0, começa no inicio da mem part.
        0,                                               // Se estes 2 forem 0, começa no inicio da mem part.
        26                                               // Tamanho do buffer
    );
    //VERIFICACOES:
    if (pVistaFicheiro == NULL)             //Se n consegui criar a vista:
        _tprintf(_T("\nErro na Criacao da Vista!\n"));
    else                                    //Se criei bem a vista:
        _tprintf(_T("\nVista Criada com Sucesso!\n"));

    //////////////////////////
    //Inverter Ordem das letras:
    char aux; int j = 25;
    for (DWORD i = 0; i < 13; i++) {
        aux = pVistaFicheiro[i];
        pVistaFicheiro[i] = pVistaFicheiro[j];
        pVistaFicheiro[j] = aux;
        j--;
    }
    _tprintf(_T("\nA ORDEM FOI TROCADA!\n"));

    //////////////////////////
    //APAGAR TUDO:
    //Desmapear vista :
    UnmapViewOfFile(pVistaFicheiro);
    //Apagar Mem Part. :
    CloseHandle(hMemPart);
    //Fechar Ficheiro :
    CloseHandle(hFicheiro);

    return 0;
}
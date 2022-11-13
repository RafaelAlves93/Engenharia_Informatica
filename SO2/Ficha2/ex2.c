#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define MAX 256

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif

    //---------------------
    //VARIAVEIS:
    HKEY hkey;
    DWORD Status;

    //DWORD Size;
    DWORD sizeVal = 256 * sizeof(TCHAR);
    
    TCHAR nome_valor[MAX];
    TCHAR numero_valor[MAX];

    TCHAR pesquisar_atributo[MAX];

    TCHAR nome[MAX] = _T("Software\\AULA\\");
    TCHAR nome_chave[MAX];


    //Variaveis para enumerar pares valor:

    TCHAR nome_val[MAX];    //nome do valor
    TCHAR num_valor[MAX];   //numero do valor
    DWORD tam_nome_val;     //tamanho do nome do valor
    int i = 0;

    //
    int elimina_chave;

    //---------------------

    //METER: 'Software\\AULA\\' + 'nome'
    _tprintf( _T("Indique NOME da chave q pretende criar: ") );
    _fgetts(nome_chave, MAX, stdin);
    _tcscat_s(nome, MAX, nome_chave);
    nome[ _tcslen(nome) - 1 ] = '\0';
    _tprintf( _T("METER CHAVE AQUI: '%s'\n\n"), nome );
    
    //CRIAR UMA CHAVE:
    if ( RegCreateKeyEx(HKEY_CURRENT_USER, nome, 0, NULL, REG_OPTION_VOLATILE,
        KEY_ALL_ACCESS, NULL, &hkey, &Status) != ERROR_SUCCESS ){   //Se ocorreu um ERRO ao criar a chave:
        
        DWORD error = GetLastError();
        _tprintf( _T(" [ERRO] - ' %d '\n") , error);
           
    }
    else {//se deu certo  ao criar a chave:

        if (Status == REG_CREATED_NEW_KEY) {
            _tprintf( _T("Chave Criada com Sucesso!\n") );
        }else if(Status == REG_OPENED_EXISTING_KEY){
            _tprintf(_T("Chave Aberta com Sucesso!\n") );
        }

        //ATRIBUIR NOME E VALOR ao atributo:
        _tprintf(_T("\n ----------------------"));
        _tprintf(_T("\n| CRIAR ATRIBUTO VALOR |\n"));
        _tprintf( _T("\nNome do valor: ") );
        _fgetts( nome_valor, MAX, stdin);
        nome_valor[_tcslen(nome_valor) - 1] = '\0';

        _tprintf(_T("Numero do valor: "));
        _fgetts(numero_valor, MAX, stdin);
        numero_valor[_tcslen(numero_valor) - 1] = '\0';

        if ( RegSetValue(hkey, nome_valor, 0, REG_SZ, (LPBYTE)numero_valor, (DWORD)(_tcslen(numero_valor) + 1)*sizeof(TCHAR) ) != ERROR_SUCCESS) {//Se deu erro:
            _tprintf( _T("Atributo Nao Criado!\n") );
        }
        else {//Se Consegui criar o atributo:
            _tprintf(_T("Atributo  Criado!\n"));
        }

        //VERIFICAR O VALOR E TIPO DE DADOS ASSOCIADOS AO ATRIBUTO:
        _tprintf( _T("\nNome do atributo que pretende pesquisar: ") );
        _fgetts(pesquisar_atributo, MAX, stdin);
        pesquisar_atributo[_tcslen(pesquisar_atributo) - 1] = '\0';

        if (RegQueryValueEx(hkey, pesquisar_atributo, NULL, NULL, (LPBYTE)numero_valor, &sizeVal) == ERROR_FILE_NOT_FOUND) {
            _tprintf( _T("Nao existe o Nome Especificado!\n") );
        }
        else {
            _tprintf(_T("Encontrei o atributo!\n"));
            _tprintf(_T("ATRIBUTO [%s] | VALOR [%s]\n"), pesquisar_atributo, numero_valor);
        }

        /*
        //ELIMINAR UM VALOR que criei a pouco:
        if ( RegDeleteValue(hkey, nome_valor) == ERROR_SUCCESS ) {//Se correu bem:
            _tprintf( _T("\nConsegui APAGAR o atributo '%s'!\n"), nome_valor );
        }
        else {//Se de erro ao tentar eliminar o valor:
            _tprintf(_T("NAO Consegui APAGAR o atributo '%s'!\n"), nome_valor);
            return -1;

        }*/


        //ENUMERAR PARES VALOR DE UMA CHAVE:
        _tprintf( _T("\n ENUMERAR PARES VALOR DESTA CHAVE: \n") );
        while (RegEnumValue(hkey, i++, nome_val, &tam_nome_val, NULL, NULL, (LPBYTE)num_valor, &sizeVal) != ERROR_NO_MORE_ITEMS) {
            _tprintf(TEXT("\n\t [%d] - NOME: '%s'| VALOR: %s "), i+1, nome_val, num_valor);
        }
            
        //ELIMINAR CHAVE CRIADA(ou seja, tudo o q se criou):
        
        _tprintf( _T("\n Pretende eliminar a chave criada?\n[1] - SIM | [2] - NAO \n") );
        _tscanf_s(_T("%d"), &elimina_chave);    

        if(elimina_chave == 1){
            RegDeleteKeyEx(HKEY_CURRENT_USER, nome, KEY_WOW64_64KEY, 0);
            _tprintf(_T("\nApaguei a chave!\n"));
        }
    }

    RegCloseKey(hkey);

    return 0;
}
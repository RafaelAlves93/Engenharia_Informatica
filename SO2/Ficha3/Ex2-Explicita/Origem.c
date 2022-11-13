#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#include "SO2_F3_DLL.h"

#define MAX 256

//LoadLibrary		 -> Carrega a livraria
//GetProcAddress	 -> Acede a variavel/funcao que quero
//FreeLibrary		 -> Liberta a livraria

typedef double (*PFUNC)(double);    //para a funcao GetProcAdress() p a funcao

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
#endif

   ///////////
   //VARIAVEIS:

    HINSTANCE hLib; //Variavel para LoadLibrary();

    double* pVar;   //pVar � um ponteiro q aponta para a variavel "factor"
    PFUNC  pFunc;   //pFunc � um ponteiro q aponta para a funcao "applyFactor"

    double auxiliar; //pVar= ('factor') = auxiliar

    ////////////////////////
    //CARREGAR A BIBLIOTECA:
    TCHAR libCaminho[] = _T("D:\\Aulas SO2\\PRATICAS\\Ficha3\\Ficha3_Ex2\\SO2_F3_DLL.dll");

    hLib = LoadLibrary(libCaminho); //Abrir a DLL

    if (hLib == NULL) {//Se deu erro:
        _tprintf( _T("\nErro a abrir DLL!\n") );
        return -1;
    }
    else {//Se correu bem a carregar:
        _tprintf( _T("\nAbri a DLL!\n") );

        pVar = (double*)GetProcAddress(hLib, "factor"); //"factor" � a variavel q quero ir buscar;
        pFunc = (PFUNC)GetProcAddress(hLib, "applyFactor"); //"applyFactor" � a funcao q quero ir buscar;

        do {//FAZER, ENQUANTO auxiliar != -1
         ////////////////////////////////////////////////////////////////////
         //ATRIBUIR VALOR A VARIAVEL EXPORTADA 'factor', q se encontra na DLL:
            _tprintf( _T("\nIndique o NMR q quer atribuir a variavel 'factor': ") );
            _tscanf_s( _T("%lf") , &auxiliar);
            _tprintf(_T("\nVALOR DE 'factor' antes de mudar= %lf \n"), *pVar);
            *pVar = auxiliar;
            _tprintf(_T("\nVALOR DE 'factor' depois de mudar= %lf \n"), *pVar);

            //Se digitar -1 acaba tudo:
            if (auxiliar == -1)
                break;

            ////////////////////////////////////////////////////////////////////
            //ENVIAR VALOR A FUNCAO 'applyfactor', p/ me devolver  o resultado:
            _tprintf(_T("\nIndique o NMR q quer enviar a funcao 'applyFactor': ") );
            _tscanf_s( _T("%lf"), &auxiliar );
            _tprintf(_T("\nResultado da funcao factorial da DLL: %lf \n"), pFunc(auxiliar) );

        } while (1);
    }
    //LIBERTAR A BIBLIOTECA:
    FreeLibrary(hLib);

    return 0;
}
#pragma once

#include <windows.h>

#ifdef SO2F3DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif

DLL_IMP_API double factor;	//exportar a variavel 'factor' do tipo float

DLL_IMP_API double applyFactor(double v);	//exportar funcao 'applyFactor'

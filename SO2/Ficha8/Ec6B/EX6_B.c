#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

TCHAR szProgName[] = TEXT("Base");

typedef struct {
	HANDLE hMutex;		//Mutex
	int* xBitmap;
	int* limDir;
	int* salto;
	HWND hWnd;			//HANDLE da janela
} DadosThread;

DWORD WINAPI MovimentaImagem(LPVOID lparam)
{
	DadosThread* dados = (DadosThread*)lparam;
	int sentido = 1;
	while (1)
	{
		WaitForSingleObject(dados->hMutex, INFINITE);
		if (*dados->salto > 0)
		{
			*dados->xBitmap = *dados->xBitmap + (sentido * *dados->salto);
			if (*dados->xBitmap <= 0)
			{
				*dados->xBitmap = 0;
				sentido = 1;
			}
			else if (*dados->xBitmap >= *dados->limDir)
			{
				*dados->xBitmap = *dados->limDir;
				sentido = -1;
			}
		}
		ReleaseMutex(dados->hMutex);
		InvalidateRect(dados->hWnd, NULL, TRUE);
		Sleep(30);
	}
}

LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	RECT rect;
	PAINTSTRUCT ps;
	MINMAXINFO* mmi;
	TCHAR tecla;

	static HDC bmpDC;
	HBITMAP hBmp;
	static BITMAP bmp;
	static int xBitmap;
	static int yBitmap;
	static int limDir;
	static HANDLE hMutex;
	static DadosThread dados;
	static int salto;

	switch (messg)
	{
	case WM_CREATE:{
		
		//1. Carregar Bitmap na Mem�ria:
		hBmp = (HBITMAP)LoadImage(NULL, _T("logo.bmp"), IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);	// Carregamos o BITMAP(Devolve um HANDLE Gen�rico)
		GetObject(hBmp, sizeof(bmp), &bmp); //Buscar informa��o sobre este HANDLE do BITMAP


		hdc = GetDC(hWnd); //  <-

		bmpDC = CreateCompatibleDC(hdc);	// Criamos uma c�pia do Device Context
		SelectObject(bmpDC, hBmp);		//Aplicamos o BITMAP(hBmp) ao DEVICE CONTEXT(bmpDC)

		ReleaseDC(hWnd, hdc); //  <-

		GetClientRect(hWnd, &rect);

		//Colocar Bitmap no centro:
		xBitmap = (rect.right / 2) - (bmp.bmWidth / 2);
		yBitmap = (rect.bottom / 2) - (bmp.bmHeight / 2);


		limDir = rect.right - bmp.bmWidth;
		salto = 2;

		hMutex = CreateMutex(NULL, FALSE, NULL); // mutex
		dados.hMutex = hMutex; //ponteiro do mutex
		dados.hWnd = hWnd; //handle para a janela
		dados.limDir = &limDir; // ponteiro para o limite direito
		dados.xBitmap = &xBitmap; // ponteiro para a posi��o do eixo dos x
		dados.salto = &salto; // tempo

		CreateThread(NULL, 0, &MovimentaImagem, &dados, 0, NULL); // lan�ar a thread
		break;
	}
	/////
	case WM_PAINT:{

		hdc = BeginPaint(hWnd, &ps); // <-

		GetClientRect(hWnd, &rect);// dimens�es 
		FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 100, 0)));//The FillRect function fills a rectangle by using the specified brush. This function includes the left and top borders, but excludes the right and bottom borders of the rectangle.
		WaitForSingleObject(hMutex, INFINITE);
		BitBlt(hdc, xBitmap, yBitmap, bmp.bmWidth, bmp.bmHeight, bmpDC, 0, 0, SRCCOPY);// we can call BitBlt() to copy the image from our Memory DC to the Window DC, thus displaying on the screen
		//SRCCOPY - Copies the source rectangle directly to the destination rectangle.
		ReleaseMutex(hMutex);

		EndPaint(hWnd, &ps); // <-
		break;
	}
	/////
	case WM_ERASEBKGND:{
		return 1;
	}
	/////
	case WM_GETMINMAXINFO:{
		mmi = (MINMAXINFO*)lParam;
		WaitForSingleObject(hMutex, INFINITE);
		mmi->ptMinTrackSize.x = bmp.bmWidth + 2;
		mmi->ptMinTrackSize.y = bmp.bmHeight * 2;
		ReleaseMutex(hMutex);
		break;
	}
	/////
	case WM_SIZE:{
		WaitForSingleObject(hMutex, INFINITE);
		xBitmap = (LOWORD(lParam) / 2) - (bmp.bmWidth / 2);
		yBitmap = (HIWORD(lParam) / 2) - (bmp.bmHeight / 2);
		limDir = LOWORD(lParam) - bmp.bmWidth;
		ReleaseMutex(hMutex);
		break;
	}
	/////
	case WM_CHAR:{
		tecla = (TCHAR)wParam;
		WaitForSingleObject(hMutex, INFINITE);
		if (tecla == '+')
			salto++;
		else if (tecla == '-' && salto > 2)
			salto--;
		else if (tecla == VK_SPACE)
			salto *= -1;
		ReleaseMutex(hMutex);
		break;
	}
	/////
	case WM_CLOSE:{
		if (MessageBox(hWnd, TEXT("Tem a certeza que quer sair?"),
			TEXT("Confirma��o"), MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
	}
	/////
	case WM_DESTROY: { // Destruir a janela e terminar o programa 
	// "PostQuitMessage(Exit Status)"
		PostQuitMessage(0);
		break;
	}
	/////
	default:
		// Neste exemplo, para qualquer outra mensagem (p.e. "minimizar","maximizar","restaurar")
		// n�o � efectuado nenhum processamento, apenas se segue o "default" do Windows
		return(DefWindowProc(hWnd, messg, wParam, lParam));
		break;  // break tecnicamente desnecess�rio por causa do return
	}
	return(0);
}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;		// hWnd � o handler da janela, gerado mais abaixo por CreateWindow()
	MSG lpMsg;		// MSG � uma estrutura definida no Windows para as mensagens
	WNDCLASSEX wcApp;	// WNDCLASSEX � uma estrutura cujos membros servem para 
			  // definir as caracter�sticas da classe da janela

	// ============================================================================
	// 1. Defini��o das caracter�sticas da janela "wcApp" 
	//    (Valores dos elementos da estrutura "wcApp" do tipo WNDCLASSEX)
	// ============================================================================
	wcApp.cbSize = sizeof(WNDCLASSEX);      // Tamanho da estrutura WNDCLASSEX
	wcApp.hInstance = hInst;		         // Inst�ncia da janela actualmente exibida 
								   // ("hInst" � par�metro de WinMain e vem 
										 // inicializada da�)
	wcApp.lpszClassName = szProgName;       // Nome da janela (neste caso = nome do programa)
	wcApp.lpfnWndProc = TrataEventos;       // Endere�o da fun��o de processamento da janela
											// ("TrataEventos" foi declarada no in�cio e
											// encontra-se mais abaixo)
	wcApp.style = CS_HREDRAW | CS_VREDRAW;  // Estilo da janela: Fazer o redraw se for
											// modificada horizontal ou verticalmente

	wcApp.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);   // "hIcon" = handler do �con normal
										   // "NULL" = Icon definido no Windows
										   // "IDI_AP..." �cone "aplica��o"
	wcApp.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // "hIconSm" = handler do �con pequeno
										   // "NULL" = Icon definido no Windows
										   // "IDI_INF..." �con de informa��o
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);	// "hCursor" = handler do cursor (rato) 
							  // "NULL" = Forma definida no Windows
							  // "IDC_ARROW" Aspecto "seta" 
	wcApp.lpszMenuName = NULL;			// Classe do menu que a janela pode ter
							  // (NULL = n�o tem menu)
	wcApp.cbClsExtra = 0;				// Livre, para uso particular
	wcApp.cbWndExtra = 0;				// Livre, para uso particular
	wcApp.hbrBackground = CreateSolidBrush(RGB(1, 255, 255));
	// "hbrBackground" = handler para "brush" de pintura do fundo da janela. Devolvido por
	// "GetStockObject".Neste caso o fundo ser� branco

	// ============================================================================
	// 2. Registar a classe "wcApp" no Windows
	// ============================================================================
	if (!RegisterClassEx(&wcApp))
		return(0);

	// ============================================================================
	// 3. Criar a janela
	// ============================================================================
	hWnd = CreateWindow(
		szProgName,			// Nome da janela (programa) definido acima
		TEXT("T�TULO DA JANELA"),// Texto que figura na barra do T�TULO
		WS_OVERLAPPEDWINDOW,	// Estilo da janela (WS_OVERLAPPED= normal)
		CW_USEDEFAULT,		// Posi��o x pixels (default=� direita da �ltima)
		CW_USEDEFAULT,		// Posi��o y pixels (default=abaixo da �ltima)
		CW_USEDEFAULT,		// Largura da janela (em pixels)
		CW_USEDEFAULT,		// Altura da janela (em pixels)
		(HWND)HWND_DESKTOP,	// handle da janela pai (se se criar uma a partir de
						// outra) ou HWND_DESKTOP se a janela for a primeira, 
						// criada a partir do "desktop"
		(HMENU)NULL,			// handle do menu da janela (se tiver menu)
		(HINSTANCE)hInst,		// handle da inst�ncia do programa actual ("hInst" � 
						// passado num dos par�metros de WinMain()
		0);				// N�o h� par�metros adicionais para a janela
	  // ============================================================================
	  // 4. Mostrar a janela
	  // ============================================================================
	ShowWindow(hWnd, nCmdShow);	// "hWnd"= handler da janela, devolvido por 
					  // "CreateWindow"; "nCmdShow"= modo de exibi��o (p.e. 
					  // normal/modal); � passado como par�metro de WinMain()
	UpdateWindow(hWnd);		// Refrescar a janela (Windows envia � janela uma 
					  // mensagem para pintar, mostrar dados, (refrescar)� 
	// ============================================================================
	// 5. Loop de Mensagens
	// ============================================================================
	// O Windows envia mensagens �s janelas (programas). Estas mensagens ficam numa fila de
	// espera at� que GetMessage(...) possa ler "a mensagem seguinte"	
	// Par�metros de "getMessage":
	// 1)"&lpMsg"=Endere�o de uma estrutura do tipo MSG ("MSG lpMsg" ja foi declarada no  
	//   in�cio de WinMain()):
	//			HWND hwnd		handler da janela a que se destina a mensagem
	//			UINT message		Identificador da mensagem
	//			WPARAM wParam		Par�metro, p.e. c�digo da tecla premida
	//			LPARAM lParam		Par�metro, p.e. se ALT tamb�m estava premida
	//			DWORD time		Hora a que a mensagem foi enviada pelo Windows
	//			POINT pt		Localiza��o do mouse (x, y) 
	// 2)handle da window para a qual se pretendem receber mensagens (=NULL se se pretendem
	//   receber as mensagens para todas as
	// janelas pertencentes � thread actual)
	// 3)C�digo limite inferior das mensagens que se pretendem receber
	// 4)C�digo limite superior das mensagens que se pretendem receber

	// NOTA: GetMessage() devolve 0 quando for recebida a mensagem de fecho da janela,
	// 	  terminando ent�o o loop de recep��o de mensagens, e o programa 

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);	// Pr�-processamento da mensagem (p.e. obter c�digo 
					   // ASCII da tecla premida)
		DispatchMessage(&lpMsg);	// Enviar a mensagem traduzida de volta ao Windows, que
					   // aguarda at� que a possa reenviar � fun��o de 
					   // tratamento da janela, CALLBACK TrataEventos (abaixo)
	}

	// ============================================================================
	// 6. Fim do programa
	// ============================================================================
	return((int)lpMsg.wParam);	// Retorna sempre o par�metro wParam da estrutura lpMsg
}
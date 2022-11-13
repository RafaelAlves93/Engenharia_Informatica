#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
/* ===================================================== */
/* Programa base (esqueleto) para aplica��es Windows     */
/* ===================================================== */
// Cria uma janela de nome "Janela Principal" e pinta fundo de branco
// Modelo para programas Windows:
//  Composto por 2 fun��es: 
//	WinMain()     = Ponto de entrada dos programas windows
//			1) Define, cria e mostra a janela
//			2) Loop de recep��o de mensagens provenientes do Windows
//     TrataEventos()= Processamentos da janela (pode ter outro nome)
//			1) � chamada pelo Windows (callback) 
//			2) Executa c�digo em fun��o da mensagem recebida


typedef struct {
	TCHAR c;
	int xPos, yPos;
}PosChar;

LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);

// Nome da classe da janela (para programas de uma s� janela, normalmente este nome � 
// igual ao do pr�prio programa) "szprogName" � usado mais abaixo na defini��o das 
// propriedades do objecto janela
TCHAR szProgName[] = TEXT("Base");

// ============================================================================
// FUN��O DE IN�CIO DO PROGRAMA: WinMain()
// ============================================================================
// Em Windows, o programa come�a sempre a sua execu��o na fun��o WinMain()que desempenha
// o papel da fun��o main() do C em modo consola WINAPI indica o "tipo da fun��o" (WINAPI
// para todas as declaradas nos headers do Windows e CALLBACK para as fun��es de
// processamento da janela)
// Par�metros:
//   hInst: Gerado pelo Windows, � o handle (n�mero) da inst�ncia deste programa 
//   hPrevInst: Gerado pelo Windows, � sempre NULL para o NT (era usado no Windows 3.1)
//   lpCmdLine: Gerado pelo Windows, � um ponteiro para uma string terminada por 0
//              destinada a conter par�metros para o programa 
//   nCmdShow:  Par�metro que especifica o modo de exibi��o da janela (usado em  
//        	   ShowWindow()

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
	wcApp.hbrBackground = CreateSolidBrush(RGB(255, 100, 0));
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

// ============================================================================
// FUN��O DE PROCESSAMENTO DA JANELA
// Esta fun��o pode ter um nome qualquer: Apenas � neces�rio que na inicializa��o da
// estrutura "wcApp", feita no in�cio de // WinMain(), se identifique essa fun��o. Neste
// caso "wcApp.lpfnWndProc = WndProc"
//
// WndProc recebe as mensagens enviadas pelo Windows (depois de lidas e pr�-processadas
// no loop "while" da fun��o WinMain()
// Par�metros:
//		hWnd	O handler da janela, obtido no CreateWindow()
//		messg	Ponteiro para a estrutura mensagem (ver estrutura em 5. Loop...
//		wParam	O par�metro wParam da estrutura messg (a mensagem)
//		lParam	O par�metro lParam desta mesma estrutura
//
// NOTA:Estes par�metros est�o aqui acess�veis o que simplifica o acesso aos seus valores
//
// A fun��o EndProc � sempre do tipo "switch..." com "cases" que descriminam a mensagem
// recebida e a tratar.
// Estas mensagens s�o identificadas por constantes (p.e. 
// WM_DESTROY, WM_CHAR, WM_KEYDOWN, WM_PAINT...) definidas em windows.h
// ============================================================================

LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {

	int retorno;
	//TCHAR c;
	//int xPos, yPos;
	HDC hdc;
	RECT rect;		//Guarda dados(posicoes, etc...) deum retangulo
	static TCHAR car = 'g';

	static int TotalPosicoes = 0;		//Total de posicoes que o array tem(coisas q meti)
	static PosChar posicoes[1000];		//Array de estruturas, q guarda tds os chars

	PAINTSTRUCT ps;	// PARA 'WM_PAINT'

	//EX.6.A):
	HBITMAP hBmp = NULL;			// HANDLE para o Bitmap que vou carregar
	HBITMAP hBmp2 = NULL;			// HANDLE para o Bitmap que vou carregar
	static BITMAP bmp;		// Bitmap
	static BITMAP bmp2;		// Bitmap
	static HDC bmpDC = NULL;
	static HDC bmpDC2 = NULL;
	static int xBitmap = 0;
	static int yBitmap = 0;
	static int xBitmap2 = 100;
	static int yBitmap2 = 100;


	switch (messg) {

	case WM_CREATE:{

		//1. Carregar Bitmap na Mem�ria:
		hBmp = (HBITMAP)LoadImage(NULL, _T("logo.bmp"), IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);	// Carregamos o BITMAP(Devolve um HANDLE Gen�rico)
		GetObject(hBmp, sizeof(bmp), &bmp); //Buscar informa��o sobre este HANDLE do BITMAP

		hBmp2 = (HBITMAP)LoadImage(NULL, _T("logo2.bmp"), IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);	// Carregamos o BITMAP(Devolve um HANDLE Gen�rico)
		GetObject(hBmp2, sizeof(bmp2), &bmp2); //Buscar informa��o sobre este HANDLE do BITMAP

		hdc = GetDC(hWnd);	// <-  // GetDC function retrieves a handle to a device context (DC) 

		bmpDC = CreateCompatibleDC(hdc);	// Criamos uma c�pia do Device Context
		SelectObject(bmpDC, hBmp);		//Aplicamos o BITMAP(hBmp) ao DEVICE CONTEXT(bmpDC)

		bmpDC2 = CreateCompatibleDC(hdc);	// Criamos uma c�pia do Device Context
		SelectObject(bmpDC2, hBmp2);		//Aplicamos o BITMAP(hBmp) ao DEVICE CONTEXT(bmpDC)

		ReleaseDC(hWnd, hdc);	// <-  

		GetClientRect(hWnd, &rect);  // dimens�es
		//Colocar Bitmap no centro:
		xBitmap = (rect.right / 2) - (bmp.bmWidth / 2);
		yBitmap = (rect.bottom / 2) - (bmp.bmHeight / 2);

		xBitmap2 = (rect.bottom / 2);
		yBitmap2 = (rect.bottom / 2);

		break;

	}
		/////
	case WM_DESTROY: {	// Destruir a janela e terminar o programa 
						// "PostQuitMessage(Exit Status)"		
		PostQuitMessage(0);
		break;
	}
		/////
	case WM_CLOSE: {	//Caso Clique em Fechar:

		retorno = MessageBox(hWnd,			// Janela Pai/Dono
			_T("Pretende mesmo sair?"),		// texto / informa��o
			_T("SAIR"),						// T�tulo
			MB_YESNO | MB_ICONQUESTION | MB_HELP);						// Tipo (implica bot�es espec�ficos)			

		if (retorno == 0) //Deu erro
			return -1;

		if (retorno == IDYES) {
			DestroyWindow(hWnd);	//Destruo esta janela
		}
		if (retorno == IDNO) {
			break;
		}
	}
		/////
	case WM_CHAR: {	//Se clicar com o teclado:
		car = (TCHAR)wParam;	//Guardo a tecla em q premi
		break;
	}
		/////
	case WM_PAINT:{

		hdc = BeginPaint(hWnd, &ps); //<-
		//GetClientRect(hWnd, &rect); // dimens�es 
		//FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0))); //The FillRect function fills a rectangle by using the specified brush. This function includes the left and top borders, but excludes the right and bottom borders of the rectangle.
		BitBlt(hdc, xBitmap, yBitmap, bmp.bmWidth, bmp.bmHeight, bmpDC, 0, 0, SRCCOPY); // we can call BitBlt() to copy the image from our Memory DC to the Window DC, thus displaying on the screen
		
		BitBlt(hdc, xBitmap2, yBitmap2, bmp2.bmWidth, bmp2.bmHeight, bmpDC2, 0, 0, SRCCOPY); // we can call BitBlt() to copy the image from our Memory DC to the Window DC, thus displaying on the screen

																						//SRCCOPY - Copies the source rectangle directly to the destination rectangle. //http://www.winprog.org/tutorial/transparency.html
		//A fun��o EndPaint marca o fim da pintura na janela especificada.Essa fun��o � necess�ria para cada chamada � fun��o BeginPaint
		EndPaint(hWnd, &ps); //<-

		break;
	}
		/////
	case WM_SIZE: { //Sent to a window after its size has changed.
		//Caso ele redimensione a janela, continua no meio a img:
		xBitmap = (LOWORD(lParam) / 2) - (bmp.bmWidth / 2);
		yBitmap = (HIWORD(lParam) / 2) - (bmp.bmHeight / 2);
		break;
	}
		/////

	default:
		// Neste exemplo, para qualquer outra mensagem
		// n�o � efectuado nenhum processamento, apenas se segue o "default" do Windows
		return(DefWindowProc(hWnd, messg, wParam, lParam));
		break;  // break tecnicamente desnecess�rio por causa do return
	}
	return(0);
}

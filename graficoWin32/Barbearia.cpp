#include "defines.h"
#include <Windows.h>	
#include <Windowsx.h>
#include <string>
#include <vector>

//-DEBUG-//
int labelText = 99999;


//-VARIAVEIS GLOBAIS DAS JANELAS-//
HWND main_hwnd, main_bttn_excCorte, main_bttn_excVenda, main_bttn_relatorio,
	main_labl_vlrCaixa[2], main_labl_vlrCorte[2], main_labl_vlrVenda[2];
RECT main_areaCliente;
HMENU main_hmenu;





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Pessoa {
public:
	std::string nome;
	int idade;
};

std::vector<Pessoa> vetorPessoas = {
	{"João", 25},
	{ "Maria", 30 },
	{ "João", 25 },
	{ "Maria", 30 },
	{ "João", 25 }
};

//Função para preencher a lista de rolagem com os dados.
void PreencherListaRolagem(HWND hwndList) {
	// Limpar a lista
	SendMessage(hwndList, LB_RESETCONTENT, 0, 0);

	// Adicionar cada pessoa à lista de rolagem
	for (const auto& pessoa : vetorPessoas) {
		std::string infoPessoa = pessoa.nome + " - " + std::to_string(pessoa.idade);
		SendMessageA(hwndList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(infoPessoa.c_str()));
	}
}


INT_PTR CALLBACK dboxExecCorteProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		// Criar a lista de rolagem na segunda janela
		HWND hwndList = GetDlgItem(hwnd, LIST_DBOX_EXCORTE_BARBEIROS);
		PreencherListaRolagem(hwndList);
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case BTTN_DBOX_EXCORTE_CONF:
			// Lógica para obter a pessoa selecionada e fazer algo com ela
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}


// Função para criar a segunda janela com a lista de pessoas
void CriarSegundaJanela(HWND hwnd) {
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_EXCORTE), hwnd, dboxExecCorteProcedure);
}
//////////////////////////////////DIALOG BOX EXECUTAR CORTES///////////////////////////////////////////////////////////////



















//-ATUALIZAR POSICAO E TAMANHO DOS ITENS DA JANELA PRINCIPAL-//
void updateWinPos(HWND hwnd) {
	int nowWSize = W_BTTN * main_areaCliente.right / W_MAINWINDOW;
	int nowHSize = H_BTTN * main_areaCliente.bottom / H_MAINWINDOW;

	//-LABELS-//
	SetWindowPos(main_labl_vlrCaixa[0], NULL,
		main_areaCliente.right - nowWSize - 10, 10,
		nowWSize, 40, SWP_NOZORDER);


	//-BOTOES-//
	SetWindowPos(main_bttn_excCorte, NULL,
		main_areaCliente.right / 2 - (nowWSize / 2) - nowWSize * 2, main_areaCliente.bottom / 2 - (nowHSize / 2),
		nowWSize, nowHSize, SWP_NOZORDER);
	SetWindowPos(main_bttn_excVenda, NULL,
		main_areaCliente.right / 2 - (nowWSize / 2), main_areaCliente.bottom / 2 - (nowHSize / 2),
		nowWSize, nowHSize, SWP_NOZORDER);
	SetWindowPos(main_bttn_relatorio, NULL,
		main_areaCliente.right / 2 - (nowWSize / 2) + nowWSize * 2, main_areaCliente.bottom / 2 - (nowHSize / 2),
		nowWSize, nowHSize, SWP_NOZORDER);
}

//-CRIAR BARRA DE MENU DA JANELA PRINCIPAL-//
void addMenus(HWND hwnd) {
	main_hmenu = CreateMenu();
	HMENU cadstr_hmenu = CreateMenu();

	AppendMenuW(cadstr_hmenu, MF_STRING, HMENU_MAIN_BARBEIRO, L"Barbeiros");
	AppendMenuW(cadstr_hmenu, MF_STRING, HMENU_MAIN_CORTE, L"Cortes");
	AppendMenuW(cadstr_hmenu, MF_STRING, HMENU_MAIN_VENDA, L"Produtos");

	AppendMenuW(main_hmenu, MF_POPUP, (UINT_PTR)cadstr_hmenu, L"Cadastros");
	AppendMenuW(main_hmenu, MF_STRING, NULL, L"Teste");

	SetMenu(hwnd, main_hmenu);
}




//-PROCEDURE DA JANELA PRINCIPAL-//
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	switch (uMsg){
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case BTTN_MAIN_EXCORTE:
			CriarSegundaJanela(hwnd);

			labelText += 1;
			break;
		case BTTN_MAIN_EXVENDA:
			labelText += 2;
			break;
		case BTTN_MAIN_RELATORIO:
			labelText += 3;
			break;
		case HMENU_MAIN_BARBEIRO:
			labelText += 4;
			break;
		case HMENU_MAIN_CORTE:
			labelText += 5;
			break;
		case HMENU_MAIN_VENDA:
			labelText += 6;
			break;
		}

		break;
	case WM_CREATE:
		//-MENU-//
		addMenus(hwnd);


		//-LABELS-//
		main_labl_vlrCaixa[0] = CreateWindow(L"STATIC", std::to_wstring(labelText).c_str(),
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
			0, 0, W_BTTN, W_BTTN,
			hwnd, NULL, NULL, NULL);


		//-BOTOES-//
		main_bttn_excCorte = CreateWindow(L"BUTTON", L"Executar Corte",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_EXCORTE, NULL, NULL);
		main_bttn_excVenda = CreateWindow(L"BUTTON", L"Executar Venda",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_EXVENDA, NULL, NULL);
		main_bttn_relatorio = CreateWindow(L"BUTTON", L"Relatorios",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_RELATORIO, NULL, NULL);



		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &main_areaCliente);

		updateWinPos(hwnd);

		InvalidateRect(hwnd, &main_areaCliente, TRUE);

		break;
	default: 
		return DefWindowProc(hwnd, uMsg, wp, lp);
		break;
	}


	return 0; //Significa que tudo ocorreu bem.
}


int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE p_hInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	//-CLASSE DA JANELA PRINCIPAL-//
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hInstance = hInst;
	wc.lpszClassName = L"MainWindow";
	wc.lpfnWndProc = MainWindowProc;
	//-REGISTRAR A JANELA PRINCIPAL-//
	RegisterClass(&wc);
	//-CONFIGURACOES DA JANELA PRINCIPal-//
	main_hwnd = CreateWindow(
		L"MainWindow", L"DonBarba",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, W_MAINWINDOW, H_MAINWINDOW,
		NULL, NULL, hInst, NULL);

	//-REGISTRAR OS DIALOGOS-//
	DialogBoxParam(hInst, MAKEINTRESOURCE(DBOX_MAIN_EXCORTE), NULL, dboxExecCorteProcedure, 0);	//Excutando Cortes...

	//-AJUSTANDO A AREA CLIENTE DA JANELA PRINCIPAL-//
	main_areaCliente = { 0, 0, W_MAINWINDOW, H_MAINWINDOW };
	AdjustWindowRectEx(&main_areaCliente, GetWindowStyle(main_hwnd), GetMenu(main_hwnd) != NULL, GetWindowExStyle(main_hwnd));
	main_areaCliente.right = main_areaCliente.right - main_areaCliente.left;
	main_areaCliente.bottom = main_areaCliente.bottom - main_areaCliente.top;
	MoveWindow(main_hwnd,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (main_areaCliente.right / 2), GetSystemMetrics(SM_CYSCREEN) / 2 - (main_areaCliente.bottom / 2),
		main_areaCliente.right, main_areaCliente.bottom, TRUE);
	
	//-ABRINDO A JANELA-//
	ShowWindow(main_hwnd, nCmdShow);
	UpdateWindow(main_hwnd);

	//-LOOP DE MENSAGENS-//
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}
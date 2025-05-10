#pragma once
#include "ExecutarCorte.hpp"
#include "DBCommands.hpp"
#include "CadastroCortes.hpp"
#include "SelecionarCorte.hpp"
#include "CadastroPessoas.hpp"































//-VARIAVEIS GLOBAIS DAS JANELAS-//

//-PROTOTIPOS-//
	//"funcoes.hpp":
		void criarDBoxExecCorte(HWND);
		void criarDBoxExecVenda(HWND);
		int prepareAndDisplay(HWND, const std::string&);



//-CRIAR BARRA DE MENU DA JANELA PRINCIPAL-//
void addMenus(HWND hwnd) {
	main_hmenu = CreateMenu();
	HMENU cadstr_hmenu = CreateMenu();

	AppendMenuW(cadstr_hmenu, MF_STRING, HMENU_MAIN_BARBEIRO, L"Barbeiros");
	AppendMenuW(cadstr_hmenu, MF_STRING, HMENU_MAIN_CORTE, L"Cortes");
	AppendMenuW(cadstr_hmenu, MF_STRING, HMENU_MAIN_PRODUTO, L"Produtos");

	AppendMenuW(main_hmenu, MF_POPUP, (UINT_PTR)cadstr_hmenu, L"Cadastros");
	AppendMenuW(main_hmenu, MF_STRING, 567, L"Teste");

	SetMenu(hwnd, main_hmenu);
	}




void atualizaFinanceiro(char type) {	
		//SetWindowText(main_vlrCorte, _PickMoney(vlr_Cortes).c_str());
		//SetWindowText(main_vlrVenda, _PickMoney(vlr_Vendas).c_str());
		//SetWindowText(main_vlrCaixa, _PickMoney(vlr_Cortes + vlr_Vendas).c_str());
}
 





	//-PROCEDURE DA JANELA PRINCIPAL-//
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	static botaoComFilho myLabls, bttnMain;

	//atualizaFinanceiro();

	switch (uMsg){
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case BTTN_MAIN_EXCORTE: {
			pessoaFromDB pess(1);
			if (pessoaFromDB(1).encontrou())
				MessageBox(hwnd, (pess.id()+pess.nome()+pess.salario()).c_str(), L"Tudo junto", MB_OK);
			else
				MessageBox(hwnd, L"nao encontronado", L"Tudo junto", MB_OK);
			break;
		}
		case BTTN_MAIN_EXVENDA: {
			break;
		}
		case BTTN_MAIN_RELATORIO: {
			break;
		}
		case BTTN_MAIN_CORTECORRETA: {
			criarDBoxCorteCorreto(hwnd);
			break;
		}
		case BTTN_MAIN_RELATORIOCORRETO: {

			break;
		}
		case HMENU_MAIN_BARBEIRO: {
			criarDBoxCadPessoa(hwnd);
			break;
		}
		case HMENU_MAIN_CORTE: {
			criarDBoxCadCortes(hwnd);
			break;
		}
		case HMENU_MAIN_PRODUTO: {
			vlr_Vendas += 100;
			break;
		}
		case 567: {
			prepareAndDisplay(hwnd, "select id, UPPER(nome), valor from corte;");

			break;
		}
		case 12345: {
			uniqueTimer.genTimer(L"Texto 1", 0, 400);
			break;
		}
		}

		break;
	case WM_CREATE: {
		
		//timedMsg = CreateWindow(L"STATIC", L"", WS_CHILD, 0, 0, 0, 0, hwnd, 0, NULL, NULL);
		uniqueTimer.init(hwnd);

		myLabls.init(hwnd, 1, false);
		bttnMain.init(hwnd, 1, false);

		//-MENU-//
		addMenus(hwnd);



		//Botoes principais.
		bttnMain.adoptChild(CreateWindow(L"BUTTON", L"teste1 excorte",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_MULTILINE,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_EXCORTE, NULL, NULL), 0, 0, 1, 1);
		
		bttnMain.adoptChild(CreateWindow(L"BUTTON", L"teste2",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_MULTILINE,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_EXVENDA, NULL, NULL), 2, 0, 1, 1);
		
		bttnMain.adoptChild(CreateWindow(L"BUTTON", L"teste3",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_MULTILINE,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_RELATORIO, NULL, NULL), 4, 0, 1, 1);

		bttnMain.adoptChild(CreateWindow(L"BUTTON", L"Corte\n Correto ",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_MULTILINE,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_CORTECORRETA, NULL, NULL), 6, 0, 1, 1);

		bttnMain.adoptChild(CreateWindow(L"BUTTON", L"Relatorio\n Correto ",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_MULTILINE,
			0, 0, W_BTTN, H_BTTN, hwnd, (HMENU)BTTN_MAIN_RELATORIOCORRETO, NULL, NULL), 8, 0, 1, 1);





		//Labels.
		main_vlrCaixa = CreateWindow(L"STATIC", L":)",
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
			0, 0, 0, 0,
			hwnd, NULL, NULL, NULL);

		main_vlrVenda = CreateWindow(L"STATIC", L">:(",
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
			0, 0, 0, 0,
			hwnd, NULL, NULL, NULL);

		main_vlrCorte = CreateWindow(L"STATIC", L";(",
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
			0, 0, 0, 0,
			hwnd, NULL, NULL, NULL);

		//Valor do caixa sera o pai.

		//Legenda (nao se altera).
		myLabls.createChild(L"STATIC", L"CAIXA", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, 0, 1, 1, 0.7, NULL);
		myLabls.createChild(L"STATIC", L"VENDAS", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, -1, 1, 1, 0.7, NULL);
		myLabls.createChild(L"STATIC", L"CORTES", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, -2, 1, 1, 0.7, NULL);
		
		////Informacao (altera).
		myLabls.adoptChild(main_vlrCaixa, 0, 0, 1, 1);
		myLabls.adoptChild(main_vlrVenda, -1, 0, 1, 1);
		myLabls.adoptChild(main_vlrCorte, -2, 0, 1, 1);
		
		
		relogio_hwnd = myLabls.createChild(L"BUTTON", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, -3, 0, 1, 1.7, 12345);



	}
	case WM_SIZE: {
		//Atualizar os controles e redesenhar a tela.
		GetClientRect(hwnd, &main_areaCliente);
		updateFontSize();
		InvalidateRect(hwnd, &main_areaCliente, TRUE);

		bttnsNewWSize = W_BTTN * main_areaCliente.right / W_MAINWINDOW;
		bttnsNewHSize = H_BTTN * main_areaCliente.bottom / H_MAINWINDOW;
				
		myLabls.setPosition(main_areaCliente.right - bttnsNewWSize - 10, 10, bttnsNewWSize, main_areaCliente.right * 40 / 1280);

		int tW = bttnsNewWSize * 0.8;
		//Isso faz os botoes principais ficarem centralizados.
		bttnMain.setPosition((main_areaCliente.right - ((bttnMain.getRectTotal().right + 1) * tW)) / 2, main_areaCliente.bottom / 2 - bttnsNewHSize / 2, tW, bttnsNewHSize * 1.2);
	}
	case WM_MOVE: {
		//Pega a posicao da jenela principal perante monitor.
		GetWindowRect(main_hwnd, &main_areaTotal);
		main_areaTotal.right -= main_areaTotal.left;
		main_areaTotal.bottom -= main_areaTotal.top;
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hwnd, uMsg, wp, lp);
		break;
	}


	return 0; //Significa que tudo ocorreu bem.
}








































//-RELOGIO-//
VOID CALLBACK TimerProc(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	timePassed++;

	SetWindowText(relogio_hwnd, charToWstring(getTime_now(2).c_str()).c_str());

	SetWindowText(main_vlrCaixa, std::to_wstring(timePassed).c_str());

	uniqueTimer.TryDeleteTimer();
}




int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE p_hInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	main_hinstance = hInst;

	//Criar e ligar o relogio assincrono.
	if (!CreateTimerQueueTimer(&hTimer, NULL, TimerProc, NULL, 0, 1000, WT_EXECUTEDEFAULT)) {
		MessageBox(main_hwnd, L"Inicial Main\nRelogio não conseguiu ser inicializado!", L"CreateTimerQueueTimer error", MB_OK | MB_ICONERROR);
		PostQuitMessage(100);
	}


	//E:/SINCRO GDRIVE/School/Codigos/CPP/Barbearia/Programa/bancodados.db
	std::string sqlLoc;
	if (std::string(lpCmdLine).size() > 0) sqlLoc = std::string(lpCmdLine);
	else sqlLoc = "E:/SINCRO GDRIVE/School/Codigos/CPP/Barbearia/Programa/bancodados.db";


	if (sqlite3_open(sqlLoc.c_str(), &db) != SQLITE_OK) {
		erroBancoDados(L"Conexao inicial do banco de dados.");
		PostQuitMessage(0);
		return -10;
	}
	if (sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr) != SQLITE_OK) {
		erroBancoDados(L"Definicao foreign_key");
		PostQuitMessage(0);
		return -10;
	}

	


	//-COMMON CONTROL-//
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);


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
		WS_OVERLAPPEDWINDOW | DS_MODALFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, W_MAINWINDOW, H_MAINWINDOW,
		NULL, NULL, hInst, NULL);

	//-REGISTRAR OS DIALOGOS-//
	// util?
	//DialogBoxParam(hInst, MAKEINTRESOURCE(DBOX_MAIN_EXCORTE), NULL, dboxExecCorteProcedure, 0);	//Excutando Cortes...

	//-AJUSTANDO A AREA CLIENTE DA JANELA PRINCIPAL-//
	main_areaCliente = { 0, 0, W_MAINWINDOW, H_MAINWINDOW };
	AdjustWindowRectEx(&main_areaCliente, GetWindowStyle(main_hwnd), GetMenu(main_hwnd) != NULL, GetWindowExStyle(main_hwnd));
	main_areaCliente.right = main_areaCliente.right - main_areaCliente.left;
	main_areaCliente.bottom = main_areaCliente.bottom - main_areaCliente.top;
	main_areaCliente.left = GetSystemMetrics(SM_CXSCREEN) / 2 - (main_areaCliente.right / 2);
	main_areaCliente.top = GetSystemMetrics(SM_CYSCREEN) / 2 - (main_areaCliente.bottom / 2);
	MoveWindow(main_hwnd,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (main_areaCliente.right / 2), GetSystemMetrics(SM_CYSCREEN) / 2 - (main_areaCliente.bottom / 2),
		main_areaCliente.right, main_areaCliente.bottom, TRUE);

	//-ABRINDO A JANELA-//
	ShowWindow(main_hwnd, nCmdShow);
	UpdateWindow(main_hwnd);






	

	//-LOOP DE MENSAGENS-//
	MSG msg = { 0 };

	do {
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} while (msg.message != WM_QUIT);


	return 0;
}
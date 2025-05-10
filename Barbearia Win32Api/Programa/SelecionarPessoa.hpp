#pragma once
#include "funcoes.hpp"


#define COD 0
#define NOME 1



std::wstring *codPessoaSelec;
HWND lvPessoas_hwnd, selPessoa_hwnd;






void preencherLVSelPessoa(wchar_t* additSearch = nullptr) {
	ListView_DeleteAllItems(lvPessoas_hwnd);

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	std::wstring tmp;

	std::vector<pessoaInfo> pi;

	sqlite3_stmt* stmt = nullptr;


	std::string pesquisa = "select id, UPPER(nome) from pessoa order by UPPER(nome);";
	if (additSearch != nullptr && std::wcslen(additSearch) > 0) {
		pesquisa = "select id, UPPER(nome) from pessoa where nome like '%" + wstringToString(additSearch) + "%' order by UPPER(nome);";
	}

	if (sqlite3_prepare_v2(db, pesquisa.c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
		erroBancoDados(L"preencherLVSelPessoa()");
	}
	else {
		int res = 0;
		while (res = sqlite3_step(stmt) == SQLITE_ROW) {
			pessoaInfo tmpPi;
			tmpPi.cod = sqlite3_column_int(stmt, 0);
			tmpPi.nome = (const char*)sqlite3_column_text(stmt, 1);

			pi.push_back(tmpPi);
		}
		if (res == SQLITE_ERROR) {
			erroBancoDados(L"step in preencherLVSelPessoa()");
			pi.clear();
		}
	}
	sqlite3_finalize(stmt);


	int linha = 0;
	for (pessoaInfo& i : pi) {
		lvItem.iItem = linha++;

		lvItem.iSubItem = COD;
		tmp = std::to_wstring(i.cod);
		lvItem.pszText = _ToWstr(tmp.c_str());
		ListView_InsertItem(lvPessoas_hwnd, &lvItem);

		lvItem.iSubItem = NOME;
		tmp = charToWstring(i.nome.c_str());
		lvItem.pszText = _ToWstr(tmp.c_str());
		ListView_SetItem(lvPessoas_hwnd, &lvItem);
	}
}



HWND geraLVSelPessoa() {

	lvPessoas_hwnd = CreateWindow(WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER| LVS_REPORT,
		0, 0, 0, 0, selPessoa_hwnd, (HMENU)LISTVIEW_SELPESSOA, NULL, NULL);

	 //Adiciona colunas.
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVS_AUTOARRANGE;


	lvColumn.pszText = _ToWstr(L"Codigo");
	lvColumn.cx = 150;
	lvColumn.iSubItem = COD;
	ListView_InsertColumn(lvPessoas_hwnd, COD, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Nome");
	lvColumn.cx = 150;
	lvColumn.iSubItem = NOME;
	ListView_InsertColumn(lvPessoas_hwnd, NOME, &lvColumn);

	// Habilitar notificação de duplo clique
	ListView_SetExtendedListViewStyle(lvPessoas_hwnd, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	preencherLVSelPessoa();

	return lvPessoas_hwnd;
}



INT_PTR CALLBACK procSelPessoa(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static botaoComFilho selPessoa;
	static HWND hPesq;
	static int dlgErroOuSuccess;

	switch (msg) {
	case WM_INITDIALOG: {
		SetWindowText(hwnd, L"Selecionar uma pessoa");

		dlgErroOuSuccess = 1;

		selPessoa.init(hwnd, 1.5, false);
		selPessoa_hwnd = hwnd;
		centerWinInMain(hwnd, 0.6);


		UINT styleBotao = WS_CHILD | WS_VISIBLE | WS_BORDER;

		hPesq = selPessoa.createChild(L"EDIT", L"", styleBotao, 0, 0, 3, 0.5, NULL);
		selPessoa.createChild(L"BUTTON", L"Pesquisar", styleBotao, 3, 0, 2, 0.5, 1000);
		selPessoa.adoptChild(geraLVSelPessoa(), 0, 0.5, 5, 4.5, typeChildForBCF(2,L"0=0.1;1=0.9;"));
		
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case 1000: {
			wchar_t nomet[256] = { 0 };
			GetWindowText(hPesq, nomet, 255);

			preencherLVSelPessoa(nomet);

			break;
		}
		}
		break;
	}
	case WM_NOTIFY: {
		NMHDR* pNMHDR = reinterpret_cast<NMHDR*>(lp);
		if (pNMHDR->idFrom == LISTVIEW_SELPESSOA && pNMHDR->code == NM_DBLCLK) {
			NMITEMACTIVATE* pNMIA = reinterpret_cast<NMITEMACTIVATE*>(lp);

			//Nao fazer nada caso haja duploclique no vazio.
			if (pNMIA->iItem < 0) break;

			wchar_t cod[256] = { 0 };
			ListView_GetItemText(lvPessoas_hwnd, pNMIA->iItem, COD, cod, 255);
			if (codPessoaSelec != nullptr) {
				*codPessoaSelec = cod;
				dlgErroOuSuccess = 0;
			}

			SendMessage(hwnd, WM_CLOSE, wp, lp);
		}
		break;
	}
	case WM_SIZE: {

		RECT jan = { 0 };
		GetClientRect(hwnd, &jan);
		int x = jan.right * 0.2;
		int y = jan.bottom * 0.2;

		selPessoa.setPosition(0, 0, x, y);
		InvalidateRect(hwnd, &jan, TRUE);

		break;
	}
	case WM_CLOSE:{
		selPessoa.finalize();
		EndDialog(hwnd, dlgErroOuSuccess);
		return TRUE;
	}
	}

	return FALSE;
}
INT_PTR selecionarPessoa(HWND hwnd, std::wstring *retornocodigo) {
	codPessoaSelec = retornocodigo;
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procSelPessoa);
}

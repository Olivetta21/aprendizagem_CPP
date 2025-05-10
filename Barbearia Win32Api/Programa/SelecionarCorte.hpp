#pragma once
#include "funcoes.hpp"

#define adcCOD 0
#define adcNOME 1
#define adcVLR 2


HWND selCorte_hwnd, lvSelCorte_hwnd;
std::wstring* codCorteSelec;





//-LIMPAR E PREENCHER LISTVIEW DOS CORTES-//
void preencherLVCortes(HWND& lv, wchar_t* additSearch = nullptr) {
	ListView_DeleteAllItems(lv);
	int totLin = -1;

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	std::wstring tmp;

	std::vector<corteAdicionadoInfo> ci;

	sqlite3_stmt* stmt = nullptr;


	std::string pesquisa = "select id, UPPER(nome), valorpadrao from corte order by UPPER(nome);";
	if (additSearch != nullptr && std::wcslen(additSearch) > 0) {
		pesquisa = "select id, UPPER(nome), valorpadrao from corte where nome like '%" + wstringToString(additSearch) + "%' order by UPPER(nome);";
	}

	if (sqlite3_prepare_v2(db, pesquisa.c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
		erroBancoDados(L"preencherLVCortes()");
	}
	else {
		int res = 0;
		while (res = sqlite3_step(stmt) == SQLITE_ROW) {
			corteAdicionadoInfo tmpCi(sqlite3_column_int(stmt, 0), (const char*)sqlite3_column_text(stmt, 1), sqlite3_column_double(stmt, 2), 0);
			//tmpCi.iddCorte = sqlite3_column_int(stmt, 0);
			//tmpCi.nome = (const char*)sqlite3_column_text(stmt, 1);
			//tmpCi.setVlr(sqlite3_column_double(stmt, 2));

			ci.push_back(tmpCi);
		}
		if (res == SQLITE_ERROR) {
			erroBancoDados(L"step in preencherLVCortes()");
			ci.clear();
		}
	}
	sqlite3_finalize(stmt);



	for (corteAdicionadoInfo& i : ci) {
		lvItem.iItem = ++totLin;

		lvItem.iSubItem = adcCOD;
		tmp = std::to_wstring(i.getIddCorte());
		lvItem.pszText = _ToWstr(tmp.c_str());
		ListView_InsertItem(lv, &lvItem);

		lvItem.iSubItem = adcNOME;
		tmp = charToWstring(i.getNome().c_str());
		lvItem.pszText = _ToWstr(tmp.c_str());
		ListView_SetItem(lv, &lvItem);

		lvItem.iSubItem = adcVLR;
		tmp = _PickMoney(i.getVlr());
		lvItem.pszText = _ToWstr(tmp.c_str());
		ListView_SetItem(lv, &lvItem);

	}
}

//-GERA A LISTVIEW COM AS TRES COLUNAS NECESSARIAS-//
HWND gerarLVCortes(HWND& chamadora, HWND& lv) {
	//Criar o controle ListView.
	lv = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_BORDER,
		0, 0, 0, 0, chamadora, (HMENU)LSITVIEW_ADDCORTES, NULL, NULL);


	//Adicionar colunas ao ListView
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVS_AUTOARRANGE;


	lvColumn.pszText = _ToWstr(L"Codigo");
	lvColumn.cx = 150;
	lvColumn.iSubItem = adcCOD;
	ListView_InsertColumn(lv, adcCOD, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Nome");
	lvColumn.cx = 150;
	lvColumn.iSubItem = adcNOME;
	ListView_InsertColumn(lv, adcNOME, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Valor");
	lvColumn.cx = 150;
	lvColumn.iSubItem = adcVLR;
	ListView_InsertColumn(lv, adcVLR, &lvColumn);


	// Habilitar notificação de duplo clique
	ListView_SetExtendedListViewStyle(lv, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	preencherLVCortes(lv);

	return lv;
}




INT_PTR CALLBACK procSelecionarCorte(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static botaoComFilho selCorte;
	static HWND hPesq;
	static int dlgErroOuSuccess;

	switch (msg) {
	case WM_INITDIALOG: {
		SetWindowText(hwnd, L"Selecionar um corte");

		dlgErroOuSuccess = 1;

		selCorte.init(hwnd, 1.5, false);
		selCorte_hwnd = hwnd;
		centerWinInMain(hwnd, 0.6);


		UINT styleBotao = WS_CHILD | WS_VISIBLE | WS_BORDER;

		hPesq = selCorte.createChild(L"EDIT", L"", styleBotao, 0, 0, 3, 0.5, NULL);
		selCorte.createChild(L"BUTTON", L"Pesquisar", styleBotao, 3, 0, 2, 0.5, 1000);
		selCorte.adoptChild(gerarLVCortes(hwnd, lvSelCorte_hwnd), 0, 0.5, 5, 4.5, typeChildForBCF(2, L"0=0.1;1=0.45;2=0.45;"));

		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case 1000: {
			wchar_t nomet[256] = { 0 };
			GetWindowText(hPesq, nomet, 255);

			preencherLVCortes(lvSelCorte_hwnd, nomet);

			break;
		}
		}
		break;
	}
	case WM_NOTIFY: {
		NMHDR* pNMHDR = reinterpret_cast<NMHDR*>(lp);
		if (pNMHDR->idFrom == LSITVIEW_ADDCORTES && pNMHDR->code == NM_DBLCLK) {
			NMITEMACTIVATE* pNMIA = reinterpret_cast<NMITEMACTIVATE*>(lp);

			//Nao fazer nada caso haja duploclique no vazio.
			if (pNMIA->iItem < 0) break;

			wchar_t cod[256] = { 0 };
			ListView_GetItemText(lvSelCorte_hwnd, pNMIA->iItem, adcCOD, cod, 255);
			if (codCorteSelec != nullptr) {
				*codCorteSelec = cod;
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

		selCorte.setPosition(0, 0, x, y);
		InvalidateRect(hwnd, &jan, TRUE);

		break;
	}
	case WM_CLOSE: {
		selCorte.finalize();
		EndDialog(hwnd, dlgErroOuSuccess);
		return TRUE;
	}
	}

	return FALSE;
}
INT_PTR selecionarCorte(HWND hwnd, std::wstring* retornocodigo) {
	codCorteSelec = retornocodigo;
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procSelecionarCorte);
}


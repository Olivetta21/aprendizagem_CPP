#pragma once
#include "funcoes.hpp"
#include "SelecionarPessoa.hpp"

//-PROTOTIPOS EXTERNOS-//
std::wstring charToWstring(const char*);
std::string wstringToString(const std::wstring&);
int erroBancoDados(const wchar_t*);
double wcToD(const wchar_t*);
//std::vector<std::wstring> *getPessoaFromDB(int);
HWND gerarLVCortes(HWND&, HWND&);
void preencherLVCortes(HWND&, wchar_t*);
//int getCorte(int, std::vector<std::wstring>*);


//-PROTOTIPOS INTERNOS-//
double getTempoMedioInsert();
void adicionaCortes(corteInfo);
void colocaCorteNoLV(corteInfo);


//-INDEXES COLUNA CORTES ADICIONADO-//
#define caNOME 0
#define caVLR 1
#define caDESC 2
#define caTOT 3

//-INDEXES COLUNA ADICIONAR CORTES-//
#define adcCOD 0
#define adcNOME 1
#define adcVLR 2


//-ID DO LISTVIEW-//
#define LISTVIEW_CORTESADICIONADOS 1001



//-GLOBAIS 2:-//
HWND addCorte_hwnd, lvAddCorte_hwnd;



//-GLOBAIS 1:-//
int indexUltimoCorte = -1;
std::wstring ultimoCodName,	//Onde digita o barbeiro a realizar o corte.
			ultimoPagtClien;	//Pra calcular o troco.
int transition = -1;	//Esse valor e recuperado do banco toda vez que a janela abre.
HWND execCorte_hwnd, lvInfoCorte_hwnd, barbCod_hwnd, pgtoCliente_hwnd, corteTroco_hwnd, vlrTotal_hwnd, corteTotal_hwnd, descTotal_hwnd, barbText_hwnd, estimativa_hwnd;
bool recalcTotal = true;	//Se houve modificacoes na ListView(e no vetor de cortes adicionados) recalcular.
std::vector<corteInfo> cInfo;	//Os cortes adicionados ficarao aqui.


//----------------------------------------------------@@@@@@@@@@@@@----------------------------------------------------------//
//----------------------------------------------------@@@@@@@@@@@@@----------------------------------------------------------//
//-------------------------------------------------------------@@@@----------------------------------------------------------//
//--------------------------------------------------------@@@@@@@@@----------------------------------------------------------//
//--------------------------------------------------------@@@@@--------------------------------------------------------------//
//----------------------------------------------------@@@@@@@@@--------------------------------------------------------------//
//----------------------------------------------------@@@@-------------------------------------------------------------------//
//----------------------------------------------------@@@@@@@@@@@@@----------------------------------------------------------//
//----------------------------------------------------@@@@@@@@@@@@@----------------------------------------------------------//








//---------//



INT_PTR CALLBACK procAdicionarCorte(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static bool iniciado = false;
	static botaoComFilho addCorte;
	static HWND adicionar_hwnd, hCod, hPesq, hNome, hVlr, hDesc, hQnt, hTot;
	static tempAddCorte tmpAddCorte(hVlr, hDesc, hQnt, hTot, hwnd);
	static int codigoselecionado;

	if (iniciado) {
		tmpAddCorte.verifyAtts();	//Verifica se teve alteraçao em desconto e quantidade, na selecao do corte.
	}

	switch (msg) {
	case WM_INITDIALOG: {
		SetWindowText(hwnd, L"Adicionar um corte à lista");

		addCorte.init(hwnd, 1.5, false);


		addCorte_hwnd = hwnd;
		codigoselecionado = 0;

		centerWinInMain(hwnd, 0.6);

		UINT estiloBotao = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_BORDER,
			esText = WS_VISIBLE | WS_CHILD | SS_RIGHT | SS_CENTERIMAGE,
			estiloStatic = WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE;



		

		adicionar_hwnd = addCorte.createChild(L"BUTTON", L"ADICIONAR", estiloBotao,	 -1.5, 0, 2, 1, 900);
		addCorte.createChild(L"BUTTON", L"CANCELAR", estiloBotao, -4.62, 0, 2, 1, 901);
		hTot = addCorte.createChild(L"STATIC", L"0", estiloStatic,		 -1, -3.5, 2, 1, NULL);
		hQnt = addCorte.createChild(L"EDIT", L"1", estiloStatic,		 -1, -4.8, 2, 1, NULL);
		hDesc = addCorte.createChild(L"EDIT", L"0", estiloStatic,		 -1, -6.1, 2, 1, NULL);
		hVlr = addCorte.createChild(L"STATIC", L"0", estiloStatic,		 -1, -7.4, 2, 1, NULL);
		hNome = addCorte.createChild(L"STATIC", L"selecione", estiloStatic,		 -1, -8.7, 2, 1, NULL);

		addCorte.createChild(L"STATIC", L"CODIGO: ", esText, -2, -11, 1, 1, NULL);
		hCod = addCorte.createChild(L"EDIT", L"digite", estiloStatic, -1, -11, 1, 1, NULL);
		addCorte.createChild(L"BUTTON", L"IR", estiloBotao, 0, -11, 1, 1, 903);

		addCorte.createChild(L"STATIC", L"TOTAL: ", esText,			-2, -3.5, 1, 1, NULL);
		addCorte.createChild(L"STATIC", L"QUANTIDADE: ", esText,	-2, -4.8, 1, 1, NULL);
		addCorte.createChild(L"STATIC", L"DESCONTO: ", esText,		-2, -6.1, 1, 1, NULL);
		addCorte.createChild(L"STATIC", L"VALOR: ", esText,			-2, -7.4, 1, 1, NULL);
		addCorte.createChild(L"STATIC", L"NOME: ", esText,			-2, -8.7, 1, 1, NULL);
		addCorte.adoptChild(gerarLVCortes(hwnd, lvAddCorte_hwnd), -5.12, -10, 3, 9, typeChildForBCF(2, L"0=0.2;1=0.4;2=0.4;"));
		hPesq = addCorte.createChild(L"EDIT", L"", estiloStatic, -5.12, -11, 2, 1, NULL);
		addCorte.createChild(L"BUTTON", L"Pesquisar", estiloBotao, -3.12, -11, 1, 1, 902);




		addCorte.setPosition(300, 300, 100, 20);

		SetFocus(adicionar_hwnd);



		iniciado = true;
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case 900: {

			if (!corteFromDB(codigoselecionado).encontrou()) {
				SetWindowText(hNome, L"");
				break;
			}

			corteInfo tmpCi = tmpAddCorte.getCi();
			tmpCi.iddCorte = codigoselecionado;
			tmpCi.setDesc(tmpCi.getDesc() / tmpCi.qnt);
			//tmpCi.setTot(tmpCi.getTot() / tmpCi.qnt);

			//Adicionando os cortes selecionados ao vetor;
			recalcTotal = false;
			for (int i = 0; i < tmpCi.qnt; i++) {
				adicionaCortes(tmpCi);
			}
			recalcTotal = true;

			SendMessage(hwnd, WM_CLOSE, wp, lp);
			break;
		}
		case 901: {
			SendMessage(hwnd, WM_CLOSE, wp, lp);
			break;
		}
		case 902: {
			//Realizar a pesquisa com os valores digitados.
			wchar_t pesq[256] = { 0 };
			GetWindowText(hPesq, pesq, 256);
			
			preencherLVCortes(lvAddCorte_hwnd, pesq);
			break;
		}
		case 903: {
			//Mostrar o corte selecionado.
			wchar_t cod[256] = { 0 };
			GetWindowText(hCod, cod, 255);
			corteFromDB tmp(wcToD(cod));
			codigoselecionado = wcToD(cod);

			if (tmp.encontrou()) {
				SetWindowText(hNome, tmp.nome().c_str());
				SetWindowText(hVlr, _PickMoney(wcToD(tmp.valor().c_str())).c_str());
			}
			else {
				SetWindowText(hNome, L" ");
				SetWindowText(hVlr, L" ");
				SetWindowText(hDesc, L" ");
				SetWindowText(hTot, L" ");
				SetWindowText(hQnt, L" ");
			}
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

			//Pega o codigo da LV, coloca no hCod e simula o clique do "IR".
			wchar_t cod[256] = { 0 };
			ListView_GetItemText(lvAddCorte_hwnd, pNMIA->iItem, adcCOD, cod, 256);
			SetWindowText(hCod, cod);
			SendMessage(hwnd, WM_COMMAND, 903, lp);
		}
		break;
	}
	case WM_SIZE: {
		RECT jan;
		GetClientRect(hwnd, &jan);

		int w = jan.right * 0.32 / 2;
		int h = jan.bottom * 0.15 / 2;
		int x = jan.right - w - jan.right * 0.01;
		int y = jan.bottom - h - jan.bottom * 0.02;

		addCorte.setPosition(x, y, w, h);

		InvalidateRect(hwnd, &jan, TRUE);

		break;
	}
	case WM_CLOSE:
		iniciado = false;
		addCorte.finalize();
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}
INT_PTR criaAdicionarCorte(HWND hwnd) {
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procAdicionarCorte);
}






//---------------------------------------------------------@@@@@-------------------------------------------------------------//
//-------------------------------------------------------@@@@@@@-------------------------------------------------------------//
//------------------------------------------------------@@@@@@@@-------------------------------------------------------------//
//-----------------------------------------------------@@@@-@@@@-------------------------------------------------------------//
//----------------------------------------------------------@@@@-------------------------------------------------------------//
//----------------------------------------------------------@@@@-------------------------------------------------------------//
//----------------------------------------------------------@@@@-------------------------------------------------------------//
//----------------------------------------------------------@@@@-------------------------------------------------------------//
//----------------------------------------------------------@@@@-------------------------------------------------------------//



//-GERA A LISTVIEW COM AS QUATRO COLUNAS NECESSARIAS-//
HWND gerarLVCortesAdicionados() {
	//Criar o controle ListView.
	lvInfoCorte_hwnd = CreateWindow(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT,
		100, 10, 400, 200, execCorte_hwnd, (HMENU)LISTVIEW_CORTESADICIONADOS, NULL, NULL);


	//Adicionar colunas ao ListView
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVS_AUTOARRANGE;

	lvColumn.pszText = _ToWstr(L"Nome");
	lvColumn.cx = 150;
	lvColumn.iSubItem = caNOME;
	ListView_InsertColumn(lvInfoCorte_hwnd, caNOME, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Valor");
	lvColumn.cx = 150;
	lvColumn.iSubItem = caVLR;
	ListView_InsertColumn(lvInfoCorte_hwnd, caVLR, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Desconto");
	lvColumn.cx = 150;
	lvColumn.iSubItem = caDESC;
	ListView_InsertColumn(lvInfoCorte_hwnd, caDESC, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Total");
	lvColumn.cx = 150;
	lvColumn.iSubItem = caTOT;
	ListView_InsertColumn(lvInfoCorte_hwnd, caTOT, &lvColumn);


	// Habilitar notificação de duplo clique
	ListView_SetExtendedListViewStyle(lvInfoCorte_hwnd, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	return lvInfoCorte_hwnd;
}


//-LIMPAR A LISTVIEW E REFAZE-LA COM AS INFORMACOES DO VETOR-//
void refazerLVCorteAdicionado() {
    ListView_DeleteAllItems(lvInfoCorte_hwnd);
	indexUltimoCorte = -1;

	for (corteInfo& i : cInfo) {
		colocaCorteNoLV(i);
	}
}



//-COLOCA AS INFORMACOES DO CORTE NA LISTVIEW-//
void colocaCorteNoLV(corteInfo corte) {
	std::wstring tmp;
	//std::vector<std::wstring> tmpVec;

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ++indexUltimoCorte;	//Numero da linha a qual ira aparecer na tela.

	lvItem.iSubItem = caNOME;
	//getCorte(corte.iddCorte, &tmpVec); APAGUE SE NAO USAR MAIS
	//tmp = tmpVec[1];
	tmp = corteFromDB(corte.iddCorte).nome();
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_InsertItem(lvInfoCorte_hwnd, &lvItem);

	lvItem.iSubItem = caVLR;
	tmp = _PickMoney(corte.getVlr());
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_SetItem(lvInfoCorte_hwnd, &lvItem);

	lvItem.iSubItem = caDESC;
	tmp = _PickMoney(corte.getDesc());
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_SetItem(lvInfoCorte_hwnd, &lvItem);

	lvItem.iSubItem = caTOT;
	tmp = _PickMoney(corte.getTot());
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_SetItem(lvInfoCorte_hwnd, &lvItem);
}
//-SOH ADICIONA AO VETOR ANTES DE MANDAR COLOCAR A INFORMACAO NA TELA-//
void adicionaCortes(corteInfo corte) {
	cInfo.push_back(corte);
	colocaCorteNoLV(corte);
}




//-APAGAR O CORTE ADICIONADO, MAS ANTES VERIFICA SE O QUE VEMOS EH DE FATO O QUE QUEREMOS-//
void apagarCorte(const int lin, bool ask = true) {
    //Verifica se a linha esta no intervalo do vetor, se o vetor nao eh vazio e se todas as informacoes lidas sao de fato as que foi selecionada.
    if (cInfo.size() != 0 && lin < cInfo.size()) {
		//std::vector<std::wstring> tmpVec; APAGUE SE NAO USAR MAIS
		//getCorte(cInfo[lin].iddCorte, &tmpVec);

		corteFromDB tmpCorte(cInfo[lin].iddCorte);

        bool sameItem = true;
        wchar_t test[256] = { 0 };
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caNOME, test, 256);
        //if (std::wstring(test) != tmpVec[1]) sameItem = false;
		if (std::wstring(test) != tmpCorte.nome()) sameItem = false;
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caVLR, test, 256); 
        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].getVlr()))) sameItem = false;
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caDESC, test, 256);
        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].getDesc()))) sameItem = false;
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caTOT, test, 256);
        if (std::wstring(test) != std::wstring(_PickMoney(cInfo[lin].getTot()))) sameItem = false;
        //if (cInfo[lin].posLin != lin) sameItem = false;


        if (sameItem) {
			int resp = IDOK;
			//if (ask) resp = MessageBox(execCorte_hwnd, (L"Nome: " + tmpVec[1] + L"\nValor: " + _PickMoney(cInfo[lin].vlr) + L"\nDesconto: " + _PickMoney(cInfo[lin].desc) + L"\nTotal: " + _PickMoney(cInfo[lin].tot)).c_str(), L"O corte será apagado!", MB_OKCANCEL | MB_ICONWARNING);
			if (ask) resp = MessageBox(execCorte_hwnd, (L"Nome: " + tmpCorte.nome() + L"\nValor: " + _PickMoney(cInfo[lin].getVlr()) + L"\nDesconto: " + _PickMoney(cInfo[lin].getDesc()) + L"\nTotal: " + _PickMoney(cInfo[lin].getTot())).c_str(), L"O corte será apagado!", MB_OKCANCEL | MB_ICONWARNING);
			if (resp == IDOK) {
				indexUltimoCorte = -1;	//Reseta a quantidade de cortes adicionados.
                std::vector<corteInfo> tmp;
				for (int i = 0; i < cInfo.size(); i++) {
					//Passa tudo pro vetor temporario, excluindo o que esta na linha recebida, e se houver, os que ja foram adicionados.
					if (i != lin) {
						tmp.push_back(cInfo[i]);
						indexUltimoCorte++;
					}
				}
				ListView_DeleteItem(lvInfoCorte_hwnd, lin);	//Remove da tela o corte excluido.
                cInfo.clear();
                cInfo = tmp;
            }
        }
		else {
			//Manda atualizar a lista se houver algum bug.
			refazerLVCorteAdicionado();
		}
    }
	recalcTotal = true;
}




//





//-INSERE OS CORTES DO VETOR AO BANCO-//
int insertCortesBanco() {
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	int quantidade = 0;
	int codigo = 0;
	wchar_t cod[65] = { 0 };
	GetWindowText(barbCod_hwnd, cod, 64);

	if (!pessoaFromDB(wcToD(cod)).encontrou()) codigo = 4;	//Apenas testando se existe.
	if (isBlankW(cod) || ultimoCodName != cod) codigo = 3;
	if (cInfo.size() < 1) codigo = 2;

	if (codigo == 0) {
		bool primeiro = 0;
		std::string timeNow = getTime_now(1);
		std::string tmp = "insert into cortesexec(transit, idBarbeiro, idCorte, valor, desconto, total, data) values ";
		for (corteInfo& ci : cInfo) {
			if (primeiro) tmp += ",";
			else primeiro = 1;	

			tmp += "(" + std::to_string(transition) + ","
			+ wstringToString(ultimoCodName)		+ ","
			+ std::to_string(ci.iddCorte)			+ ","
			+ _PickMoneyM(ci.getVlr())					+ ","
			+ _PickMoneyM(ci.getDesc())					+ ","
			+ _PickMoneyM(ci.getTot())					+ ","
			+ "'" + timeNow + "')";

			quantidade++;
		
		}
		tmp += ';';

		if (sqlite3_exec(db, tmp.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
			quantidade = -100;
			codigo = 1;
			erroBancoDados((std::wstring(L"insertCortesBanco(). Comando:\n") + charToWstring(tmp.c_str())).c_str());
		}
		end = std::chrono::steady_clock::now();

	}



	//Essa parte eh para calcular uma estimativa de tempo que leva para o insert.
	if (quantidade > 0) {
		//reLVCorteAdicionado();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::wstring est = L"Decorrido: ";
		est += std::to_wstring(duration.count());
		est += L"\nQuantidade: ";
		est += std::to_wstring(quantidade);
		est += L"\nMedio: ";
		est += std::to_wstring(duration.count() / quantidade);

		std::string tmp = "insert into tempoInsert (qnt, dur) values (";
		tmp += std::to_string(quantidade); tmp += ", ";
		tmp += std::to_string(duration.count()); tmp += ");";

		if (sqlite3_exec(db, tmp.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
			erroBancoDados((std::wstring(L"tempoInsert. Comando:\n") + charToWstring(tmp.c_str())).c_str());
		}

		//MessageBox(execCorte_hwnd, est.c_str(), L"Microseconds", MB_OK);
	}

	return codigo;
}

//-TENTA ATUALIZAR O NOME DO BARBEIRO SELECIONADO-//
void tryUpDateBarb() {
	wchar_t cod[65] = { 0 };
	GetWindowText(barbCod_hwnd, cod, 64);
	//Atualizar somente se houver algo na caixa de texto e ele for diferente do da ultima vez.
	if (ultimoCodName != cod) {
		ultimoCodName = cod;

		pessoaFromDB tmpPess(wcToD(cod));
		if (!isBlankW(cod) && tmpPess.encontrou()) SetWindowText(barbText_hwnd, tmpPess.nome().c_str());
		else SetWindowText(barbText_hwnd, L"invalido");
	}
}

//-TENTA SOMAR OS TOTAIS DO VETOR, CALCULAR O TROCO E ATUALIZAR A ESTIMATIVA-///
void tryUpDateTotal() {
	static long double total = 0;
	if (recalcTotal) {
		recalcTotal = false;
		long double corte = 0, desc = 0;
		std::wstring somas = L"corte\tdesk\ttotal";
		for (corteInfo& c : cInfo) {
			corte += c.getVlr();
			desc += c.getDesc();
			somas += L"\n" + std::to_wstring(c.getVlr()) + L" | " + std::to_wstring(c.getDesc()) + L" | " + std::to_wstring(c.getVlr() - c.getDesc());
		}
		total = corte - desc;

		//MessageBox(0, somas.c_str(), L"somatorio", MB_OK);

		SetWindowText(vlrTotal_hwnd, (std::wstring(L"R$") + _PickMoney(total)).c_str());
		SetWindowText(descTotal_hwnd, (std::wstring(L"R$") + _PickMoney(desc)).c_str());
		SetWindowText(corteTotal_hwnd, (std::wstring(L"R$") + _PickMoney(corte)).c_str());
		
		//SetWindowText(vlrTotal_hwnd, (std::wstring(L"R$") + std::to_wstring(total)).c_str());
		//SetWindowText(descTotal_hwnd, (std::wstring(L"R$") + std::to_wstring(desc)).c_str());
		//SetWindowText(corteTotal_hwnd, (std::wstring(L"R$") + std::to_wstring(corte)).c_str());


		SetWindowText(pgtoCliente_hwnd, _PickMoney(total).c_str());

		//Aproveitando essa funcao pra calcular as estatisticas.
		double dur = 0.0f;
		if (cInfo.size() > 0) dur = getTempoMedioInsert() * cInfo.size(); 		
		dur /= 1000;
		SetWindowText(estimativa_hwnd, (std::to_wstring(cInfo.size()) + std::wstring(L" : ") + std::to_wstring(dur) + std::wstring(L"ms")).c_str());
	}



	wchar_t pagtoClient[256] = { 0 };
	GetWindowText(pgtoCliente_hwnd, pagtoClient, 255);
	//Atualizar somente se houver algo na caixa de texto e ele for diferente do da ultima vez.
	if (ultimoPagtClien != pagtoClient) {
		ultimoPagtClien = pagtoClient;

		long double troco = truncTwo(wcToD(pagtoClient)) - truncTwo(total);

		//MessageBox(0, (std::to_wstring(troco) + L"\n" + pagtoClient + L"\n" + std::to_wstring(total)).c_str(), L"L", MB_OK);

		SetWindowText(corteTroco_hwnd, _PickMoney(truncTwo(troco)).c_str());
	}
}

//-PEGA O MAIOR VALOR DE TRANSIT DO BANCO E USA ELE+1-//
int getMaxTransit() {
	sqlite3_stmt* stmt = nullptr;
	int codigo = 0;

	if (sqlite3_prepare_v2(db, "select MAX(transit) from cortesexec;", -1, &stmt, 0) != SQLITE_OK) {
		erroBancoDados(L"Nao foi possivel recuperar o maior valor do transit de cortesexec.");
		codigo = 1;
	}
	else {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			transition = sqlite3_column_int(stmt, 0) + 1;
		}
		else {
			erroBancoDados(L"step in getMaxTransit()");
			codigo = 2;
		}
	}

	sqlite3_finalize(stmt);

	return codigo;
}

//-PEGA O TEMPO MEDIO DE EXECUCAO DO INSERT-//
double getTempoMedioInsert() {
	sqlite3_stmt* stmt = nullptr;
	double codigo = 0.0f;

	if (sqlite3_prepare_v2(db, "select SUM(dur), SUM(qnt) from tempoInsert;", -1, &stmt, 0) == SQLITE_ERROR) {
		erroBancoDados(L"Nao foi possivel recuperar o valor medio dos insert.");
		codigo =  0.0f;
	}
	else {
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) {
			double d = sqlite3_column_double(stmt, 0);
			double q = sqlite3_column_double(stmt, 1);
			if (q != 0.0f) codigo = d / q;
		}
		else {
			erroBancoDados(L"step in getTempoMedioInsert()");
			codigo =  0.0f;
		}
	}

	sqlite3_finalize(stmt);

	return codigo;

}

INT_PTR CALLBACK procDBoxCorteCorreto(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static bool iniciado = false;
	static botaoComFilho selBarb;

	if (iniciado) {
		tryUpDateTotal();
		tryUpDateBarb();
	}

	switch (msg) {
	case WM_INITDIALOG: {
		SetWindowText(hwnd, L"Executar um corte");

		selBarb.init(hwnd, 1.5, false);

		transition = -1;
		cInfo.clear();
		execCorte_hwnd = hwnd;
		ultimoCodName = L"-999999";
		indexUltimoCorte = -1;

		if (getMaxTransit()) {
			SendMessage(hwnd, WM_CLOSE, wp, lp);
		}

		centerWinInMain(hwnd);


		UINT estiloBotao = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			estiloEdit = WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE | ES_AUTOHSCROLL,
			estiloInfo = WS_VISIBLE | WS_CHILD | ES_LEFT | SS_CENTERIMAGE,
			esInfo2 = WS_VISIBLE | WS_CHILD | ES_LEFT | SS_CENTER| SS_CENTERIMAGE,
			esInfo3 = WS_VISIBLE | WS_CHILD | ES_RIGHT | SS_CENTERIMAGE;


		//Registrando os childs e adopteds.
		selBarb.createChild(L"BUTTON", L"SELECIONE O BARBEIRO", estiloBotao, 0, 0, 1, 1, 872);
		barbCod_hwnd = selBarb.createChild(L"EDIT", L"", estiloEdit | WS_TABSTOP, 0, 1, 0.3, 1, NULL);
		selBarb.createChild(L"BUTTON", L"?1", estiloBotao, 0, 2, 0.2, 1, 876);
		//selBarb.createChild(L"BUTTON", L"?2", estiloBotao, 0.2, 2, 0.2, 1, 873);
		//selBarb.createChild(L"BUTTON", L"?3", estiloBotao, 0.4, 2, 0.2, 1, 878);
		barbText_hwnd = selBarb.createChild(L"STATIC", L"NomeDoBarbeiro", estiloEdit, 0.3, 1, 0.7, 1, NULL);
		selBarb.createChild(L"BUTTON", L"Cortes", estiloBotao, 0, 4, 1, 2, 877);
		selBarb.createChild(L"BUTTON", L"Cancelar", estiloBotao, 0, 12, 1, 1, 874);
		selBarb.createChild(L"BUTTON", L"Confirmar", estiloBotao, 1.08, 12, 1.9, 1, 875);
		selBarb.adoptChild(gerarLVCortesAdicionados(), 1.08, 0, 1.9, 6, typeChildForBCF(2, L"0=0.4;1=0.2;2=0.2;3=0.2;"));

		selBarb.createChild(L"STATIC", L"Valor", esInfo2, 1.08, 8, 0.633333, 1, NULL);
		corteTotal_hwnd = selBarb.createChild(L"STATIC", L"v0", estiloEdit, 1.08, 7, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", L"Desconto", esInfo2, 1.713333, 8, 0.633333, 1, NULL);
		descTotal_hwnd = selBarb.createChild(L"STATIC", L"d1", estiloEdit, 1.713333, 7, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", L"Total", esInfo2, 2.346666, 8, 0.633333, 1, NULL);
		vlrTotal_hwnd = selBarb.createChild(L"STATIC", L"t2", estiloEdit, 2.346666, 7, 0.633333, 1, NULL);

		estimativa_hwnd = selBarb.createChild(L"STATIC", L"est:", estiloInfo, 0, 8, 1, 1, NULL);
		selBarb.createChild(L"STATIC", (L"ID: " + std::to_wstring(transition)).c_str(), estiloInfo, 0, 7, 1, 1, NULL);

		selBarb.createChild(L"STATIC", L"Pagto Cliente: R$", esInfo3, 1.08-(0.633333), 10, 0.633333, 1, NULL);
		pgtoCliente_hwnd = selBarb.createChild(L"EDIT", L"NENHUM", esInfo2, 1.08, 10, 0.633333, 1, NULL);
		selBarb.createChild(L"STATIC", L"Troco: R$", esInfo3, 1.08+(0.633333), 10, 0.633333, 1, NULL);
		corteTroco_hwnd = selBarb.createChild(L"STATIC", L"NENHUM", esInfo2, 1.08+(0.633333*2), 10, 0.633333, 1, NULL);


		SetFocus(barbCod_hwnd);
		iniciado = true;
		break;
	}
	case WM_NOTIFY: {
		NMHDR* pNMHDR = reinterpret_cast<NMHDR*>(lp);
		if (pNMHDR->idFrom == LISTVIEW_CORTESADICIONADOS && pNMHDR->code == NM_DBLCLK) {
			NMITEMACTIVATE* pNMIA = reinterpret_cast<NMITEMACTIVATE*>(lp);

			//Apagar o item que houver duploclique.
			apagarCorte(pNMIA->iItem);
		}
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case 876: {
			wchar_t cod[256] = { 0 };
			GetWindowText(barbCod_hwnd, cod, 255);
			uniqueTimer.genTimer(cod, 0,0);
			break;
		}
		case 872: {
			//Selecionar um barbeiro.
			std::wstring cod;
			if (!selecionarPessoa(hwnd, &cod)) SetWindowText(barbCod_hwnd, cod.c_str());
			break;
		}
		case 874: {
			//Cancelar
			SendMessage(hwnd, WM_CLOSE, wp, lp);
			break;
		}
		case 875: {
			wchar_t cod[256] = { 0 };
			GetWindowText(barbCod_hwnd, cod, 255);
			bool brk = false;
			if (!pessoaFromDB(wcToD(cod)).encontrou()) {
				SendMessage(hwnd, WM_COMMAND, LOWORD(872), NULL); //Abre selecao do barbeiro.
				brk = true;
			}
			if (cInfo.size() < 1) {
				SendMessage(hwnd, WM_COMMAND, LOWORD(877), NULL); //Abre adicao do corte.
				brk = true;
			}
			if (brk) break;
			//Fechar o dialog de addCorte se todos os cortes forem adicionados sem erro.
			if (!insertCortesBanco()) {
				uniqueTimer.genTimer(std::wstring(L"Transação " + std::to_wstring(transition) + L" efetuada com sucesso!"), 0, 400);
				SendMessage(hwnd, WM_CLOSE, wp, lp);
			}
			break;
		}
		case 877: {
			//Selecionar um corte.
			criaAdicionarCorte(hwnd);
			break;
		}
		}

		break;
	}
	case WM_CTLCOLORDLG: {
		return (INT_PTR)GetStockObject(COLOR_BACKGROUND);
		break;
	}
	case WM_SIZE: {
		RECT jan;
		GetClientRect(hwnd, &jan);


		int w = jan.right * 0.33;
		int h = jan.bottom * 0.15 / 2;
		int x = jan.right * 0.01;
		int y = jan.bottom * 0.02;

		selBarb.setPosition(x, y, w, h);

		//selBarb.setPosition(10, 10, jan.right * 0.33, jan.bottom * 0.15 / 2);

		InvalidateRect(hwnd, &jan, TRUE);

		break;

	}
	case WM_CLOSE:
		selBarb.finalize();
		transition = -1;
		iniciado = false; 
		recalcTotal = true;
		cInfo.clear();
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}

void criarDBoxCorteCorreto(HWND hwnd) {
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procDBoxCorteCorreto);
}
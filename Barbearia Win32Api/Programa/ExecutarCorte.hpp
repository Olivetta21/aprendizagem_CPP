#pragma once
#include "funcoes.hpp"
#include "SelecionarPessoa.hpp"

//-PROTOTIPOS EXTERNOS-//
std::wstring charToWstring(const char*);
std::string wstringToString(const std::wstring&);
int erroBancoDados(const wchar_t*);
int erroComum(const wchar_t*);
double wcToD(const wchar_t*);
//std::vector<std::wstring> *getPessoaFromDB(int);
HWND gerarLVCortes(HWND&, HWND&);
void preencherLVCortes(HWND&, wchar_t*);
//int getCorte(int, std::vector<std::wstring>*);
INT_PTR selecionarCorte(HWND, std::wstring*);


//-PROTOTIPOS INTERNOS-//
void adicionaCortes(corteAdicionadoInfo);
void colocaCorteNoLV(corteAdicionadoInfo);


//-INDEXES COLUNA CORTES ADICIONADO-//
#define caNOME 0
#define caVLR 1
#define caQUANT 2

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
			ultimoCodCorte, //Onde digita o corte pra adiciona a sacola.
			ultimoPagtClien,	//Pra calcular o troco.
			ultimoDesconto;	///Pra atualizar o total.

HWND execCorte_hwnd, lvInfoCorte_hwnd, barbCod_hwnd, pgtoCliente_hwnd, corteTroco_hwnd, vlrTotal_hwnd,
corteTotal_hwnd, descTotal_hwnd, barbText_hwnd, exco_idcorte_hwnd,
exco_nomecorte_hwnd,
exco_valorcorte_hwnd,
exco_qntcorte_hwnd;

bool recalcTotal = true;	//Se houve modificacoes na ListView(e no vetor de cortes adicionados) recalcular.
std::vector<corteAdicionadoInfo> cortesAdic;	//Os cortes adicionados ficarao aqui.
//
//Esse valor eh recuperado do banco toda vez que a janela do executarcorte abre.
class rec_id_for_tables {
	int id_recuperado;
public:
	rec_id_for_tables() { id_recuperado = -1;	}
	void reset() { id_recuperado = -1; }
	int set(int valor) {
		if (id_recuperado < 0) id_recuperado = valor;
		else return 1;
		return 0;	
	}
	int get(int &recuperado) {
		if (id_recuperado >= 0) recuperado = id_recuperado;
		else return 1;
		return 0;	
	}
	int imediateGet() { return id_recuperado; }
} id_executorcorte;


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


/*
INT_PTR CALLBACK procAdicionarCorte(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static bool iniciado = false;
	static botaoComFilho addCorte;
	static HWND adicionar_hwnd, hCod, hPesq, hNome, hVlr, hQnt, hTot;
	static tempAddCorte tmpAddCorte(hVlr, hQnt, hTot, hwnd);
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
		//hDesc = addCorte.createChild(L"EDIT", L"0", estiloStatic,		 -1, -6.1, 2, 1, NULL);
		hVlr = addCorte.createChild(L"STATIC", L"0", estiloStatic,		 -1, -7.4, 2, 1, NULL);
		hNome = addCorte.createChild(L"STATIC", L"selecione", estiloStatic,		 -1, -8.7, 2, 1, NULL);

		addCorte.createChild(L"STATIC", L"CODIGO: ", esText, -2, -11, 1, 1, NULL);
		hCod = addCorte.createChild(L"EDIT", L"digite", estiloStatic, -1, -11, 1, 1, NULL);
		addCorte.createChild(L"BUTTON", L"IR", estiloBotao, 0, -11, 1, 1, 903);

		addCorte.createChild(L"STATIC", L"TOTAL: ", esText,			-2, -3.5, 1, 1, NULL);
		addCorte.createChild(L"STATIC", L"QUANTIDADE: ", esText,	-2, -4.8, 1, 1, NULL);
		//addCorte.createChild(L"STATIC", L"DESCONTO: ", esText,		-2, -6.1, 1, 1, NULL);
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


*/



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
	lvColumn.iSubItem = caNOME;
	ListView_InsertColumn(lvInfoCorte_hwnd, caNOME, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Valor");
	lvColumn.iSubItem = caVLR;
	ListView_InsertColumn(lvInfoCorte_hwnd, caVLR, &lvColumn);

	lvColumn.pszText = _ToWstr(L"Quantidade");
	lvColumn.iSubItem = caQUANT;
	ListView_InsertColumn(lvInfoCorte_hwnd, caQUANT, &lvColumn);

	// Habilitar notificação de duplo clique
	ListView_SetExtendedListViewStyle(lvInfoCorte_hwnd, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	return lvInfoCorte_hwnd;
}


//-LIMPAR A LISTVIEW E REFAZE-LA COM AS INFORMACOES DO VETOR-//
void refazerLVCorteAdicionado() {
    ListView_DeleteAllItems(lvInfoCorte_hwnd);
	indexUltimoCorte = -1;

	for (corteAdicionadoInfo& i : cortesAdic) {
		colocaCorteNoLV(i);
	}
}



//-COLOCA AS INFORMACOES DO CORTE NA LISTVIEW-//
void colocaCorteNoLV(corteAdicionadoInfo corte) {
	std::wstring tmp;
	//std::vector<std::wstring> tmpVec;

	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ++indexUltimoCorte;	//Numero da linha a qual ira aparecer na tela.

	lvItem.iSubItem = caNOME;
	tmp = corteFromDB(corte.getIddCorte()).nome();
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_InsertItem(lvInfoCorte_hwnd, &lvItem);

	lvItem.iSubItem = caVLR;
	tmp = _PickMoney(corte.getVlr());
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_SetItem(lvInfoCorte_hwnd, &lvItem);

	lvItem.iSubItem = caQUANT;
	tmp = std::to_wstring(corte.getQnt()).c_str();
	lvItem.pszText = _ToWstr(tmp.c_str());
	ListView_SetItem(lvInfoCorte_hwnd, &lvItem);

}
//-SOH ADICIONA AO VETOR ANTES DE MANDAR COLOCAR A INFORMACAO NA TELA-//
void adicionaCortes(corteAdicionadoInfo corte) {
	cortesAdic.push_back(corte);
	colocaCorteNoLV(corte);
}




//-APAGAR O CORTE ADICIONADO, MAS ANTES VERIFICA SE O QUE VEMOS EH DE FATO O QUE QUEREMOS-//
void apagarCorte(const int lin, bool ask = true) {
    //Verifica se a linha esta no intervalo do vetor, se o vetor nao eh vazio e se todas as informacoes lidas sao de fato as que foi selecionada.
    if (cortesAdic.size() != 0 && lin < cortesAdic.size()) {

		corteFromDB tmpCorte(cortesAdic[lin].getIddCorte());

        bool sameItem = true;
        wchar_t test[256] = { 0 };
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caNOME, test, 256);
		if (std::wstring(test) != tmpCorte.nome()) sameItem = false;
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caVLR, test, 256); 
        if (std::wstring(test) != std::wstring(_PickMoney(cortesAdic[lin].getVlr()))) sameItem = false;
        ListView_GetItemText(lvInfoCorte_hwnd, lin, caQUANT, test, 256);
        if (std::wstring(test) != std::to_wstring(cortesAdic[lin].getQnt())) sameItem = false;


        if (sameItem) {
			int resp = IDOK;
			if (ask) resp = MessageBox(execCorte_hwnd, (L"Nome: " + tmpCorte.nome() + L"\nValor: " + _PickMoney(cortesAdic[lin].getVlr()) + L"\nQuantidade: " + std::to_wstring(cortesAdic[lin].getQnt())).c_str(), L"O corte será apagado!", MB_OKCANCEL | MB_ICONWARNING);
			if (resp == IDOK) {
				indexUltimoCorte = -1;	//Reseta a quantidade de cortes adicionados.
                std::vector<corteAdicionadoInfo> tmp;
				for (int i = 0; i < cortesAdic.size(); i++) {
					//Passa tudo pro vetor temporario, excluindo o que esta na linha recebida, e se houver, os que ja foram adicionados.
					if (i != lin) {
						tmp.push_back(cortesAdic[i]);
						indexUltimoCorte++;
					}
				}
				ListView_DeleteItem(lvInfoCorte_hwnd, lin);	//Remove da tela o corte excluido.
				cortesAdic.clear();
				cortesAdic = tmp;
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
	int codigo = 0;

	wchar_t cod[65] = { 0 };
	GetWindowText(barbCod_hwnd, cod, 64);

	wchar_t desc[255] = { 0 };
	GetWindowText(descTotal_hwnd, desc, 255);

	wchar_t pgtoclien[255] = { 0 };
	GetWindowText(pgtoCliente_hwnd, pgtoclien, 255);

	int id_executor = -9999999;

	if (id_executorcorte.get(id_executor)) codigo = 5;	//Pegando o numero do executor do corte.
	else if (isBlankW(desc) || ultimoDesconto != desc) codigo = 7;
	else if (isBlankW(pgtoclien) || ultimoPagtClien != pgtoclien) codigo = 6;
	else if (!pessoaFromDB(wcToD(cod)).encontrou()) codigo = 4;	//Apenas testando se existe.
	else if (isBlankW(cod) || ultimoCodName != cod) codigo = 3;
	else if (cortesAdic.size() < 1) codigo = 2;
	else {	//Se nao cair em nenhum erro, inserir no banco.
		std::string comm_executorCorte = "insert into executorcorte(id_barbeiro, pagtocliente, desconto, id, data) values (" +
			wstringToString(cod) + ", " + _PickMoneyM(truncTwo(wcToD(pgtoclien))) + ", " +
			_PickMoneyM(truncTwo(wcToD(desc))) + ", " + std::to_string(id_executor) + ", '" + getTime_now(1) + "');";

		if (sqlite3_exec(db, comm_executorCorte.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
			codigo = 1;
			erroBancoDados((std::wstring(L"insertCortesBanco() - executorcortes. Comando:\n") + charToWstring(comm_executorCorte.c_str())).c_str());
		}
		else {
			bool primeira = 1;

			std::string comm_cortesexec = "insert into corteexec(qnt, valor, id_executor, id_corte) values ";

			for (corteAdicionadoInfo& cAdd : cortesAdic) {
				if (primeira) primeira = 0;
				else comm_cortesexec += ",";
			
				comm_cortesexec += "(" + std::to_string(cAdd.getQnt()) + ", " +
					_PickMoneyM(truncTwo(cAdd.getVlr())) + ", " +
					std::to_string(id_executor) + ", " +
					std::to_string(cAdd.getIddCorte()) + ")";
			
			
			}
			comm_cortesexec += ';';


			if (sqlite3_exec(db, comm_cortesexec.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
				codigo = 8;
				erroBancoDados((std::wstring(L"insertCortesBanco() - corteexec. Comando:\n") + charToWstring(comm_cortesexec.c_str())).c_str());
				//Deleta o executor se os cortes derem erro;
				std::string comm_delExecutor = "delete from executorcorte where id = " + std::to_string(id_executor) + ";";
				if (sqlite3_exec(db, comm_delExecutor.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
					erroBancoDados((std::wstring(L"insertCortesBanco() - delExecutor. Comando:\n") + charToWstring(comm_delExecutor.c_str())).c_str());
				}

			}
		}

		end = std::chrono::steady_clock::now();

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


	GetWindowText(exco_idcorte_hwnd, cod, 64);
	if (ultimoCodCorte != cod) {
		ultimoCodCorte = cod;

		corteFromDB tmpCorte(wcToD(cod));
		if (!isBlankW(cod) && tmpCorte.encontrou()) {
			SetWindowText(exco_nomecorte_hwnd, tmpCorte.nome().c_str());
			SetWindowText(exco_valorcorte_hwnd, _PickMoney(wcToD(tmpCorte.valor().c_str())).c_str());
			SetWindowText(exco_qntcorte_hwnd, L"1");
		}
		else {
			SetWindowText(exco_nomecorte_hwnd,  L"Invalido");
			SetWindowText(exco_valorcorte_hwnd, L"Invalido");
			SetWindowText(exco_qntcorte_hwnd,   L"Invalido");
		}
	}
}

//-TENTA SOMAR OS TOTAIS DO VETOR, CALCULAR O TROCO E O DESCONTO-///
void tryUpDateTotal() {
	static long double total = 0;
	static wchar_t descontoDig[256] = { 0 };
	static wchar_t pagtoClient[256] = { 0 };

	GetWindowText(descTotal_hwnd, descontoDig, 255);
	GetWindowText(pgtoCliente_hwnd, pagtoClient, 255);
	//Atualizar somente se houver algo na caixa de texto e ele for diferente do da ultima vez.
	if (ultimoDesconto != descontoDig) {
		ultimoDesconto = descontoDig;
		recalcTotal = true;
	}

	if (recalcTotal) {
		recalcTotal = false;

		long double subtotal = 0, descount = truncTwo(wcToD(descontoDig));

		for (corteAdicionadoInfo& cAI : cortesAdic) {
			subtotal += truncTwo(cAI.getVlr() * cAI.getQnt());
		}
		total = truncTwo(subtotal - descount);


		SetWindowText(corteTotal_hwnd, _PickMoney(subtotal).c_str());
		SetWindowText(vlrTotal_hwnd, _PickMoney(total).c_str());
		SetWindowText(pgtoCliente_hwnd, _PickMoney(total).c_str());
	}


	if (ultimoPagtClien != pagtoClient) {
		ultimoPagtClien = pagtoClient;
		long double troco = truncTwo(truncTwo(wcToD(pagtoClient))) - truncTwo(total);
		SetWindowText(corteTroco_hwnd, _PickMoney(troco).c_str());
	}

	
}

//-PEGA O MAIOR VALOR DO ID DO EXECUTOR E USA ELE+1-//
int getNextExecutorId() {
	sqlite3_stmt* stmt = nullptr;
	int codigo = 0;
	
	id_executorcorte.reset();

	if (sqlite3_prepare_v2(db, "select MAX(id) from executorcorte;", -1, &stmt, 0) != SQLITE_OK) {
		erroBancoDados(L"Nao foi possivel recuperar o maior valor do id de executorcorte.");
		codigo = 1;
	}
	else {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			if (id_executorcorte.set(sqlite3_column_int(stmt, 0) + 1)) {
				erroComum(L"Não foi possível definir o id do executorcorte, talves por que ele não foi resetado?");
				codigo = 3;
			}
		}
		else {
			erroBancoDados(L"step in getNextExecutorId()");
			codigo = 2;
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

		cortesAdic.clear();
		execCorte_hwnd = hwnd;
		ultimoCodName = L"-999999";
		indexUltimoCorte = -1;

		if (getNextExecutorId()) {
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
		barbText_hwnd = selBarb.createChild(L"STATIC", L"NomeDoBarbeiro", estiloEdit, 0.3, 1, 0.7, 1, NULL);

		//

		selBarb.createChild(L"BUTTON", L"...", estiloBotao, 0, 4, 0.25, 1, 877);
		exco_idcorte_hwnd = selBarb.createChild(L"EDIT", L"id", estiloEdit, 0 + (0.25 * 1), 4, 0.25, 1, NULL);
		exco_nomecorte_hwnd = selBarb.createChild(L"STATIC", L"nome", estiloEdit, 0 + (0.25 * 2), 4, 0.5, 1, NULL);
		exco_valorcorte_hwnd = selBarb.createChild(L"EDIT", L"valor", estiloEdit, 0, 5,0.375, 1, NULL);
		exco_qntcorte_hwnd = selBarb.createChild(L"EDIT", L"qnt", estiloEdit, 0+0.375, 5, 0.375, 1, NULL);
		selBarb.createChild(L"BUTTON", L" >> ", estiloBotao, 0+0.75, 5, 0.25, 1, 873);

		//

		selBarb.createChild(L"BUTTON", L"Cancelar", estiloBotao, 0, 12, 1, 1, 874);
		selBarb.createChild(L"BUTTON", L"Executar", estiloBotao, 1.08, 12, 1.9, 1, 875);
		selBarb.adoptChild(gerarLVCortesAdicionados(), 1.08, 0, 1.9, 6, typeChildForBCF(2, L"0=0.4;1=0.3;2=0.3;"));
		selBarb.createChild(L"BUTTON", L"?1", estiloBotao, 0, 2, 0.2, 1, 876);
		
		//

		float ya = 0.5;

		selBarb.createChild(L"STATIC", L"Subtotal: ", esInfo3, 1.713333, 7 - ya, 0.633333, 1, NULL);
		corteTotal_hwnd = selBarb.createChild(L"STATIC", L"_subtotal", estiloEdit, 2.346666, 7 - ya, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", L"Desconto: ", esInfo3, 1.713333, 8 - ya, 0.633333, 1, NULL);
		descTotal_hwnd = selBarb.createChild(L"EDIT", L"Sem Desconto", esInfo2, 2.346666, 8 - ya, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", L"Total: ", esInfo3, 1.713333, 9 - ya, 0.633333, 1, NULL);
		vlrTotal_hwnd = selBarb.createChild(L"STATIC", L"_total", estiloEdit, 2.346666, 9 - ya, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", L"Pagto Cliente: ", esInfo3, 1.713333, 10 - ya, 0.633333, 1, NULL);
		pgtoCliente_hwnd = selBarb.createChild(L"EDIT", L"NENHUM", esInfo2, 2.346666, 10 - ya, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", L"Troco: ", esInfo3, 1.713333, 11 - ya, 0.633333, 1, NULL);
		corteTroco_hwnd = selBarb.createChild(L"STATIC", L"NENHUM", estiloEdit, 2.346666, 11 - ya, 0.633333, 1, NULL);

		selBarb.createChild(L"STATIC", (L"ID: " + std::to_wstring(id_executorcorte.imediateGet())).c_str(), estiloInfo, 0, 7, 1, 1, NULL);

	

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
		case 873: {
			//Adicionar o corte na sacola.

			wchar_t cod[255] = { 0 };
			GetWindowText(exco_idcorte_hwnd, cod, 255);
			wchar_t nome[255] = { 0 };
			GetWindowText(exco_nomecorte_hwnd, nome, 255);
			wchar_t valor[255] = { 0 };
			GetWindowText(exco_valorcorte_hwnd, valor, 255);
			wchar_t qnt[255] = { 0 };
			GetWindowText(exco_qntcorte_hwnd, qnt, 255);

			adicionaCortes(corteAdicionadoInfo(truncTwo(wcToD(cod)), wstringToString(nome), wcToD(valor), wcToD(qnt)));
			recalcTotal = true;

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
			if (cortesAdic.size() < 1) {
				SendMessage(hwnd, WM_COMMAND, LOWORD(877), NULL); //Abre adicao do corte e o adiciona em seguida.
				SendMessage(hwnd, WM_COMMAND, LOWORD(873), NULL);
				brk = true;
			}
			if (brk) break;
			//Fechar o dialog de addCorte se todos os cortes forem adicionados sem erro.
			if (!insertCortesBanco()) {
				uniqueTimer.genTimer(std::wstring(L"Transação " + std::to_wstring(id_executorcorte.imediateGet()) + L" efetuada com sucesso!"), 0, 400);
				SendMessage(hwnd, WM_CLOSE, wp, lp);
			}
			break;
		}
		case 877: {
			//Selecionar um corte.
			std::wstring tmpIddCorte;
			if (!selecionarCorte(hwnd, &tmpIddCorte)) {
				SetWindowText(exco_idcorte_hwnd, tmpIddCorte.c_str());
			}
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
		iniciado = false; 
		recalcTotal = true;
		cortesAdic.clear();
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}

void criarDBoxCorteCorreto(HWND hwnd) {
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procDBoxCorteCorreto);
}
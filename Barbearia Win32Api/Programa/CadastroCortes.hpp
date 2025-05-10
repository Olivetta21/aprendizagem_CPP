#pragma once
#include "funcoes.hpp"

INT_PTR selecionarCorte(HWND, std::wstring*);
//int getCorte(int, std::vector<std::wstring>*);
bool isBlankC(std::string);
bool isBlankW(std::wstring);


void puxaCortes(HWND&, int);

HWND cadCorte_hwnd, cadCorte_idd_hwnd, cadCorte_nome_hwnd, cadCorte_valor_hwnd, cadCorte_statusCriaEdit_hwnd, cadCorte_iddCriaEdit_hwnd;

//-SALVAR UMA EDICAO OU UM NOVO CORTE-//
void salvarModificacaoCorte() {

	wchar_t aux1[256] = { 0 };
	wchar_t vlr[256] = { 0 };
	wchar_t idd[256] = { 0 };
	wchar_t status[256] = { 0 };
	std::wstring w_status;

	GetWindowText(cadCorte_iddCriaEdit_hwnd, aux1, 255);
	GetWindowText(cadCorte_idd_hwnd, idd, 255);
	GetWindowText(cadCorte_statusCriaEdit_hwnd, status, 255);
	w_status = status;

	if (std::wstring(aux1) == std::wstring(idd) && (std::wstring(aux1).size() + std::wstring(idd).size() > 1)) {	//Verificando se os IDS sao iguais.

		GetWindowText(cadCorte_nome_hwnd, aux1, 255);
		GetWindowText(cadCorte_valor_hwnd, vlr, 255);

		std::string nome = wstringToString(aux1);
		std::string valor = wstringToString(vlr);

		std::wstring test;	//Verifica se tem campos vazios antes de continuar.
		if (nome.size() < 1 || isBlankC(nome)) test += L"NOME\n";
		if (valor.size() < 1 || isBlankC(valor)) test += L"VALOR\n";
		if (test.size() > 0) {
			MessageBox(cadCorte_hwnd, test.c_str(), L"Campos vazios!", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		valor = _PickMoneyM(wcToD(vlr));


		if (w_status == L"Editando") {
			std::string comm = "update corte set nome = '" + nome + "', valorpadrao = " + valor + " where id = " + wstringToString(idd) + ";";

			if (sqlite3_exec(db, comm.c_str(), nullptr, nullptr, nullptr) == SQLITE_ERROR) {
				erroBancoDados(L"SalvarEdicao() - editando");
			}
			else {
				uniqueTimer.genTimer(L"Alteração gravada.",0);
				puxaCortes(cadCorte_idd_hwnd, 0);
			}
		}
		else if (w_status == L"Criando") {
			std::string comm = "insert into corte (nome, valorpadrao, id) values ('" + nome + "', " + valor + ", " + wstringToString(idd) + ");";

			if (sqlite3_exec(db, comm.c_str(), nullptr, nullptr, nullptr) == SQLITE_ERROR) {
				erroBancoDados(L"SalvarEdicao() - criando");
			}
			else {
				uniqueTimer.genTimer(L"Corte criado.", 0);
				puxaCortes(cadCorte_idd_hwnd, 0);
			}
		}
		else {
			MessageBox(cadCorte_hwnd, std::wstring(L"ATENÇÃO: status não identificado corretamente, avise o administrador imediatamente.\n\nstatus: ->" + w_status + L"<-").c_str(), L"ALERTA", MB_OK | MB_ICONERROR);
		}

	}
	else {
		MessageBox(cadCorte_hwnd, L"Por segurança, o ID digitado deve corresponder ao ID da edição/criação.", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
	}
}


//-CANCELAR UMA MODIFICACAO OU UM NOVO CORTE-//
void cancModificCorte() {
	wchar_t status[256] = { 0 };
	std::wstring w_status;
	GetWindowText(cadCorte_statusCriaEdit_hwnd, status, 255);
	w_status = status;

	if (w_status == L"Criando" || w_status == L"") {
		SetWindowText(cadCorte_idd_hwnd, L"");
		SetWindowText(cadCorte_statusCriaEdit_hwnd, L"");
		SetWindowText(cadCorte_iddCriaEdit_hwnd, L"");
		SetWindowText(cadCorte_nome_hwnd, L"");
		SetWindowText(cadCorte_valor_hwnd, L"");
	}
	else if (w_status == L"Editando") {
		puxaCortes(cadCorte_iddCriaEdit_hwnd, 0);	//Puxa o corte com o codigo que fica ao lado do status.
	}
	else MessageBox(cadCorte_hwnd, std::wstring(L"ATENÇÃO: status não identificado corretamente, avise o administrador imediatamente.\n\nstatus: ->" + w_status + L"<-").c_str(), L"ALERTA", MB_OK | MB_ICONERROR);
}



//-PUXA O CORTE PRA JANELA E ATUALIZA O STATUS-//
void puxaCortes(HWND &where, int editCreat) {
	std::vector<std::wstring> vecCorte;
	wchar_t iddCort[256] = { 0 };
	GetWindowText(where, iddCort, 255);


	SetWindowText(cadCorte_statusCriaEdit_hwnd, L"");
	SetWindowText(cadCorte_iddCriaEdit_hwnd, L"");
	SetWindowText(cadCorte_nome_hwnd, L"");
	SetWindowText(cadCorte_valor_hwnd, L"");

	if (isBlankW(iddCort)) return;

	switch (editCreat){
	case 0: {	//Editando existente.
		corteFromDB tmpCorte(wcToD(iddCort));
		if (tmpCorte.encontrou()) {
			SetWindowText(cadCorte_statusCriaEdit_hwnd, L"Editando");
			SetWindowText(cadCorte_iddCriaEdit_hwnd, tmpCorte.id().c_str());
			SetWindowText(cadCorte_nome_hwnd, tmpCorte.nome().c_str());
			SetWindowText(cadCorte_valor_hwnd, _PickMoney(wcToD(tmpCorte.valor().c_str())).c_str());
		}
		break;
	}
	case 1: {	//Criando um novo.
		SetWindowText(cadCorte_statusCriaEdit_hwnd, L"Criando");
		SetWindowText(cadCorte_iddCriaEdit_hwnd, iddCort);
		break;
	}
	}
}



//-PEGA O PROXIMO MENOR CODIGO DISPONIVEL-//
int getNextIdCorte() {
	int idRetorno = -1;
	sqlite3_stmt* stmt = nullptr;

	std::string comm = "select id from corte order by id;";

	if (sqlite3_prepare_v2(db, comm.c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
		erroBancoDados(L"getNextIdCorte() - prepare");
	}
	else {
		int res;
		int anterior = 0;
		int proximo = 0;
		do {
			res = sqlite3_step(stmt);

			if (res == SQLITE_ERROR) {
				erroBancoDados(L"getNextIdCorte() - step");
				break;
			}
			else if (res == SQLITE_DONE) {
				if (anterior + proximo == 0) idRetorno = 1; //Retorna 1 se ainda nao existir nenhum codigo.
				else idRetorno = proximo + 1;	//Retorna o maior valor encontrado + 1, ja que todos foram testados.
				break;
			}
			else if (res == SQLITE_ROW) {
				proximo = sqlite3_column_int(stmt, 0);
				if (anterior + 1 != proximo) {
					idRetorno = anterior + 1;	//Retorna o menor numero que ainda nao existe.
					break;
				}
				anterior = proximo;
			}
			else {
				MessageBox(cadCorte_hwnd, L"Isso não deveria aparecer. Avise o administrador.\n\ncriarNovoCorte() - step", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
				break;
			}

		} while (res != SQLITE_DONE && res != SQLITE_ERROR);
	}
	sqlite3_finalize(stmt);

	return idRetorno;
}



//-CRIA UM NOVO CORTE, TESTANDO SE O CODIGO DIGITADO JA EXISTE-//
void criarNovoCorte() {

	wchar_t iddCort[256] = { 0 };
	GetWindowText(cadCorte_idd_hwnd, iddCort, 255);

	int idFuturo = -1;


	sqlite3_stmt* stmt = nullptr;
	if (wcToD(iddCort) > 0) { //Se houver um codigo escrito.
		std::string comm = "select * from corte where id = " + wstringToString(iddCort) + ";";
		if (sqlite3_prepare_v2(db, comm.c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
			erroBancoDados(L"criarNovoCorte() - prepare");
		}
		else {
			int res = sqlite3_step(stmt);

			if (res == SQLITE_ERROR) {
				erroBancoDados(L"criarNovoCorte() - step");
			}
			else if (res == SQLITE_DONE) {	//Codigo usado ainda nao existe.
				idFuturo = wcToD(iddCort);	//Pode usar o digitado.
			}
			else if (res == SQLITE_ROW) {	//Codigo usado ja existente.
				MessageBox(cadCorte_hwnd, L"Esse código já está sendo utilizado por outro corte. O próximo disponível será usado.", L"Atenção", MB_OK | MB_ICONEXCLAMATION);
				idFuturo = getNextIdCorte();	//Pega o proximo disponivel.
			}
			else {
				MessageBox(cadCorte_hwnd, L"Isso não deveria aparecer. Avise o administrador.\n\ncriarNovoCorte() - step", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
			}
		}
	}
	else {
		idFuturo = getNextIdCorte();	//Pega o proximo disponivel.
	}

	sqlite3_finalize(stmt);

	SetWindowText(cadCorte_idd_hwnd, std::to_wstring(idFuturo).c_str());

	puxaCortes(cadCorte_idd_hwnd, 1);
}



//-DELETA O CORTE SELECIONADO SE ELE ESTIVER NO ESTADO DE EDICAO-//
void deletarCorte() {
	wchar_t aux1[256] = { 0 };
	wchar_t idd[256] = { 0 };
	wchar_t status[256] = { 0 };
	std::wstring w_status;

	GetWindowText(cadCorte_iddCriaEdit_hwnd, aux1, 255);
	GetWindowText(cadCorte_idd_hwnd, idd, 255);
	GetWindowText(cadCorte_statusCriaEdit_hwnd, status, 255);
	w_status = status;

	//Verifica se os ID sao iguais, e se esta no estado de edicao.
	if (std::wstring(aux1) == std::wstring(idd) && (std::wstring(aux1).size() + std::wstring(idd).size() > 1 && w_status == L"Editando")) {
		corteFromDB tmpCorte(wcToD(idd));
		if (tmpCorte.encontrou()) {
			if (IDOK != MessageBox(cadCorte_hwnd, std::wstring(L"ID: " + tmpCorte.id() + L"\nNOME: " + tmpCorte.nome() + L"\nVALOR: " + _PickMoney(wcToD(tmpCorte.valor().c_str()))).c_str(), L"Confirma exclusão?", MB_OKCANCEL | MB_ICONEXCLAMATION))
				return;
		}

		std::string comm = "delete from corte where id = " + wstringToString(idd) + ";";

		int res = sqlite3_exec(db, comm.c_str(), nullptr, nullptr, nullptr);
		if (res == SQLITE_OK) {

			uniqueTimer.genTimer(L"Corte excluído.", 0);
			//Isso aqui vai fazer a tela ficar limpa.
			SetWindowText(cadCorte_statusCriaEdit_hwnd, L"");	
			cancModificCorte();
		}
		else {
			if (sqlite3_errcode(db) == SQLITE_CONSTRAINT)
				MessageBox(cadCorte_hwnd, L"Não foi possível deletar esse corte pois eles está sendo usado por outra tabela.", L"ERRO", MB_OK | MB_ICONERROR);
			else
				erroBancoDados(std::to_wstring(sqlite3_errcode(db)).c_str());
		}
	}
	else MessageBox(cadCorte_hwnd, L"Por segurança, o ID digitado deve corresponder ao ID da edição/criação.", L"Aviso", MB_OK | MB_ICONEXCLAMATION);

}







//-----------------------------------------------------------------------------------------------//

INT_PTR CALLBACK procCriarDBoxCadCortes(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static botaoComFilho cadCorte;

	switch (msg) {
	case WM_INITDIALOG: {
		SetWindowText(hwnd, L"Cadastro de cortes");

		centerWinInMain(hwnd, 0.6);

		cadCorte_hwnd = hwnd;

		cadCorte.init(hwnd, 2, false);

		UINT bS = WS_VISIBLE | WS_CHILD | WS_BORDER,
			eS = WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER,
			sS = WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE;


		cadCorte.createChild(L"BUTTON", L"ID CORTE", bS, 0, 0, 1, 1, 1000);
		cadCorte_idd_hwnd = cadCorte.createChild(L"EDIT", L"", eS, 1.2, 0, 1, 1, NULL);
		cadCorte.createChild(L"BUTTON", L"IR", bS, 2.4, 0, 1, 1, 1001);
		cadCorte.createChild(L"BUTTON", L"NOVO", bS, 3.6, 0, 1, 1, 1002);
		cadCorte.createChild(L"BUTTON", L"DELETAR", bS, 4.8, 0, 1, 1, 1003);

		cadCorte.createChild(L"STATIC", L"Nome: ", sS, 0, 3, 1, 1, NULL);
		cadCorte_nome_hwnd = cadCorte.createChild(L"EDIT", L"", eS, 1, 3, 4.8, 1, NULL);

		cadCorte.createChild(L"STATIC", L"Valor: ", sS, 0, 5, 1, 1, NULL);
		cadCorte_valor_hwnd = cadCorte.createChild(L"EDIT", L"", eS, 1, 5, 4.8, 1, NULL);

		cadCorte_statusCriaEdit_hwnd = cadCorte.createChild(L"STATIC", L"", sS, 0, 8, 1, 1, NULL);
		cadCorte_iddCriaEdit_hwnd = cadCorte.createChild(L"STATIC", L"", sS, 1, 8, 1, 1, NULL);

		cadCorte.createChild(L"BUTTON", L"cancelar", bS, 3.6, 8, 1, 1, 998);
		cadCorte.createChild(L"BUTTON", L"salvar", bS, 4.8, 8, 1, 1, 999);

		cadCorte.createChild(L"BUTTON", L"teste1 ", sS, 0, 6, 1, 1, 1515);


		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case 1515: {

		}
		case 998: {
			cancModificCorte();
			break;
		}
		case 999: {
			salvarModificacaoCorte();
			break;
		}
		case 1000: {
			std::wstring cod;
			if (!selecionarCorte(hwnd, &cod)) {
				SetWindowText(cadCorte_idd_hwnd, cod.c_str());
				puxaCortes(cadCorte_idd_hwnd, 0);
			};
			break;
		}
		case 1001: {
			puxaCortes(cadCorte_idd_hwnd, 0);
			break;
		}
		case 1002: {
			criarNovoCorte();
			break;
		}
		case 1003: {
			deletarCorte();
			break;
		}
		}
		break;
	}
	case WM_SIZE: {
		RECT jan = { 0 };
		GetClientRect(hwnd, &jan);
		InvalidateRect(hwnd, &jan, TRUE);

		int retX = jan.right * 0.01;
		int retY = jan.bottom * 0.02;

		int w = jan.right * 0.15;

		int t = (jan.right - (w * 5.9)) / 5;


		cadCorte.setPosition(0, retY, w + t, jan.bottom * 0.1);

		break;
	}
	case WM_CLOSE: {
		cadCorte.finalize();
		EndDialog(hwnd, 0);
		return TRUE;
	}
	}

	return FALSE;
}
INT_PTR criarDBoxCadCortes(HWND hwnd) {
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procCriarDBoxCadCortes);
}

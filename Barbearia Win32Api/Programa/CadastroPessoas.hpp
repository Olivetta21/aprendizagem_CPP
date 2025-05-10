#pragma once
#include "funcoes.hpp"

bool isBlankC(std::string);
bool isBlankW(std::wstring);
//std::vector<std::wstring>* getPessoaFromDB(int);

void puxaPessoa(HWND&, int);

HWND cadPess_hwnd, cadPess_idd_hwnd, cadPess_nome_hwnd, cadPess_salario_hwnd, cadPess_statusCriaEdit_hwnd, cadPess_iddCriaEdit_hwnd;

//-SALVAR UMA EDICAO OU UM NOVA PESSOA-//
void salvarModificacaoPessoa() {

	wchar_t iddCE[256] = { 0 };
	wchar_t idd[256] = { 0 };
	GetWindowText(cadPess_iddCriaEdit_hwnd, iddCE, 255);
	GetWindowText(cadPess_idd_hwnd, idd, 255);


	if (std::wstring(iddCE) == std::wstring(idd) && (std::wstring(iddCE).size() + std::wstring(idd).size() > 1)) {	//Verificando se os IDS sao iguais.

		wchar_t comiss[256] = { 0 };
		wchar_t status[256] = { 0 };
		wchar_t nome[256] = { 0 };


		GetWindowText(cadPess_salario_hwnd, comiss, 255);
		GetWindowText(cadPess_statusCriaEdit_hwnd, status, 255);
		GetWindowText(cadPess_nome_hwnd, nome, 255);
		
		std::wstring w_status = status;
		std::string s_comiss = wstringToString(comiss);
		std::string s_nome = wstringToString(nome);
		std::string s_idCE = wstringToString(iddCE);
		std::string s_id = wstringToString(idd);

		std::wstring test;	//Verifica se tem campos vazios antes de continuar.
		if (s_nome.size() < 1 || isBlankC(s_nome)) test += L"NOME\n";
		if (s_comiss.size() < 1 || isBlankC(s_comiss)) test += L"COMISSÃO\n";
		if (test.size() > 0) {
			MessageBox(cadPess_hwnd, test.c_str(), L"Campos vazios!", MB_OK | MB_ICONEXCLAMATION);
			return;
		}


		if (w_status == L"Editando") {
			std::string comm = "update pessoa set nome = '" + s_nome + "' where id = " + s_idCE + ";";

			if (sqlite3_exec(db, comm.c_str(), nullptr, nullptr, nullptr) == SQLITE_ERROR) {
				erroBancoDados((L"SalvarEdicao() - editando\n" + charToWstring(comm.c_str())).c_str());
			}
			else {
				uniqueTimer.genTimer(L"Alteração gravada.", 0);
				puxaPessoa(cadPess_iddCriaEdit_hwnd, 0);
			}
		}
		else if (w_status == L"Criando") {
			std::string comm = "insert into pessoa (id, nome) values (" + s_id + ", '" + s_nome + "');";

			if (sqlite3_exec(db, comm.c_str(), nullptr, nullptr, nullptr) == SQLITE_ERROR) {
				erroBancoDados((L"SalvarEdicao() - criando" + charToWstring(comm.c_str())).c_str());
			}
			else {
				uniqueTimer.genTimer(L"Pessoa criada.", 0);
				puxaPessoa(cadPess_idd_hwnd, 0);
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
void cancModificPessoa() {
	wchar_t status[256] = { 0 };
	std::wstring w_status;
	GetWindowText(cadPess_statusCriaEdit_hwnd, status, 255);
	w_status = status;

	if (w_status == L"Criando" || w_status == L"") {
		SetWindowText(cadPess_idd_hwnd, L"");
		SetWindowText(cadPess_statusCriaEdit_hwnd, L"");
		SetWindowText(cadPess_iddCriaEdit_hwnd, L"");
		SetWindowText(cadPess_nome_hwnd, L"");
		SetWindowText(cadPess_salario_hwnd, L"");
	}
	else if (w_status == L"Editando") {
		puxaPessoa(cadPess_iddCriaEdit_hwnd, 0);	//Puxa o corte com o codigo que fica ao lado do status.
	}
	else MessageBox(cadPess_hwnd, std::wstring(L"ATENÇÃO: status não identificado corretamente, avise o administrador imediatamente.\n\nstatus: ->" + w_status + L"<-").c_str(), L"ALERTA", MB_OK | MB_ICONERROR);
}



//-PUXA O CORTE PRA JANELA E ATUALIZA O STATUS-//
void puxaPessoa(HWND& where, int editCreat) {
	//std::vector<std::wstring> vecCorte;
	wchar_t iddCort[256] = { 0 };
	GetWindowText(where, iddCort, 255);


	SetWindowText(cadPess_statusCriaEdit_hwnd, L"");
	SetWindowText(cadPess_iddCriaEdit_hwnd, L"");
	SetWindowText(cadPess_nome_hwnd, L"");
	SetWindowText(cadPess_salario_hwnd, L"");

	if (isBlankW(iddCort)) return;

	switch (editCreat) {
	case 0: {	//Editando existente.
		pessoaFromDB tmpPess(wcToD(iddCort));

		if (tmpPess.encontrou()) {
			SetWindowText(cadPess_statusCriaEdit_hwnd, L"Editando");
			SetWindowText(cadPess_iddCriaEdit_hwnd, tmpPess.id().c_str());
			SetWindowText(cadPess_nome_hwnd, tmpPess.nome().c_str());
			SetWindowText(cadPess_salario_hwnd, tmpPess.salario().c_str());
		}
		break;
	}
	case 1:	//Criando um novo.
		SetWindowText(cadPess_statusCriaEdit_hwnd, L"Criando");
		SetWindowText(cadPess_iddCriaEdit_hwnd, iddCort);
		break;
	}
}



//-PEGA O PROXIMO MENOR CODIGO DISPONIVEL-//
int getNextIdPessoa() {
	int idRetorno = -1;
	sqlite3_stmt* stmt = nullptr;

	std::string comm = "select id from pessoa order by id;";

	if (sqlite3_prepare_v2(db, comm.c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
		erroBancoDados(L"getNextIdPessoa() - prepare");
	}
	else {
		int res;
		int anterior = 0;
		int proximo = 0;
		do {
			res = sqlite3_step(stmt);

			if (res == SQLITE_ERROR) {
				erroBancoDados(L"getNextIdPessoa() - step");
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
				MessageBox(cadPess_hwnd, L"Isso não deveria aparecer. Avise o administrador.\n\ngetNextIdPessoa() - nenhum retorno de sql tratado", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
				break;
			}

		} while (res != SQLITE_DONE && res != SQLITE_ERROR);
	}
	sqlite3_finalize(stmt);

	return idRetorno;
}



//-CRIA UM NOVO CORTE, TESTANDO SE O CODIGO DIGITADO JA EXISTE-//
void criarNovaPessoa() {

	wchar_t iddCort[256] = { 0 };
	GetWindowText(cadPess_idd_hwnd, iddCort, 255);

	int idFuturo = -1;


	sqlite3_stmt* stmt = nullptr;
	if (!isBlankW(iddCort)) { //Se houver um codigo escrito.
		std::string comm = "select * from pessoa where id = " + wstringToString(iddCort) + ";";
		if (sqlite3_prepare_v2(db, comm.c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
			erroBancoDados(L"criarNovaPessoa() - prepare");
		}
		else {
			int res = sqlite3_step(stmt);

			if (res == SQLITE_ERROR) {
				erroBancoDados(L"criarNovaPessoa() - step");
			}
			else if (res == SQLITE_DONE) {	//Codigo usado ainda nao existe.
				idFuturo = wcToD(iddCort);	//Pode usar o digitado.
			}
			else if (res == SQLITE_ROW) {	//Codigo usado ja existente.
				MessageBox(cadPess_hwnd, L"Esse código já está sendo utilizado por outra pessoa. O próximo disponível será usado.", L"Atenção", MB_OK | MB_ICONEXCLAMATION);
				idFuturo = getNextIdPessoa();	//Pega o proximo disponivel.
			}
			else {
				MessageBox(cadPess_hwnd, L"Isso não deveria aparecer. Avise o administrador.\n\ncriarNovaPessoa() - retorno do sql nao tratado", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
			}
		}
	}
	else {
		idFuturo = getNextIdPessoa();	//Pega o proximo disponivel.
	}

	sqlite3_finalize(stmt);

	SetWindowText(cadPess_idd_hwnd, std::to_wstring(idFuturo).c_str());

	puxaPessoa(cadPess_idd_hwnd, 1);
}



//-DELETA O CORTE SELECIONADO SE ELE ESTIVER NO ESTADO DE EDICAO-//
void deletarPessoa() {
	wchar_t aux1[256] = { 0 };
	wchar_t idd[256] = { 0 };
	wchar_t status[256] = { 0 };
	std::wstring w_status;

	GetWindowText(cadPess_iddCriaEdit_hwnd, aux1, 255);
	GetWindowText(cadPess_idd_hwnd, idd, 255);
	GetWindowText(cadPess_statusCriaEdit_hwnd, status, 255);
	w_status = status;

	//Verifica se os ID sao iguais, e se esta no estado de edicao.
	if (std::wstring(aux1) == std::wstring(idd) && (std::wstring(aux1).size() + std::wstring(idd).size() > 1 && w_status == L"Editando")) {
		pessoaFromDB tmpPess(wcToD(idd));
		if (tmpPess.encontrou()) {
			if (IDOK != MessageBox(cadPess_hwnd, std::wstring(L"ID: " + tmpPess.id() + L"\nNOME: " + tmpPess.nome() + L"\nCOMISSÃO: " + tmpPess.salario()).c_str(), L"Confirma exclusão?", MB_OKCANCEL | MB_ICONEXCLAMATION))
				return;
		}

		std::string comm = "delete from pessoa where id = " + wstringToString(idd) + ";";

		int res = sqlite3_exec(db, comm.c_str(), nullptr, nullptr, nullptr);
		if (res == SQLITE_OK) {

			uniqueTimer.genTimer(L"Pessoa excluída.", 0);
			//Isso aqui vai fazer a tela ficar limpa.
			SetWindowText(cadPess_statusCriaEdit_hwnd, L"");
			cancModificPessoa();
		}
		else {
			if (sqlite3_errcode(db) == SQLITE_CONSTRAINT)
				MessageBox(cadPess_hwnd, L"Não foi possível deletar essa pessoa pois ela está sendo usado por outra tabela.", L"ERRO", MB_OK | MB_ICONERROR);
			else
				erroBancoDados(std::to_wstring(sqlite3_errcode(db)).c_str());
		}
	}
	else MessageBox(cadPess_hwnd, L"Por segurança, o ID digitado deve corresponder ao ID da edição/criação.", L"Aviso", MB_OK | MB_ICONEXCLAMATION);
}















//-----------------------------------------------------------------------------------------------//

INT_PTR CALLBACK procCriarDBoxCadPessoa(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	static botaoComFilho cadPessoa;

	switch (msg) {
	case WM_INITDIALOG: {
		SetWindowText(hwnd, L"Cadastro de pessoa");

		centerWinInMain(hwnd, 0.6);

		cadPess_hwnd = hwnd;

		cadPessoa.init(hwnd, 2, false);

		UINT bS = WS_VISIBLE | WS_CHILD | WS_BORDER,
			eS = WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER,
			sS = WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE;


		cadPessoa.createChild(L"BUTTON", L"ID PESSOA", bS, 0, 0, 1, 1, 1000);
		cadPess_idd_hwnd = cadPessoa.createChild(L"EDIT", L"", eS, 1.2, 0, 1, 1, NULL);
		cadPessoa.createChild(L"BUTTON", L"IR", bS, 2.4, 0, 1, 1, 1001);
		cadPessoa.createChild(L"BUTTON", L"NOVO", bS, 3.6, 0, 1, 1, 1002);
		cadPessoa.createChild(L"BUTTON", L"DELETAR", bS, 4.8, 0, 1, 1, 1003);

		cadPessoa.createChild(L"STATIC", L"Nome: ", sS, 0, 3, 1, 1, NULL);
		cadPess_nome_hwnd = cadPessoa.createChild(L"EDIT", L"", eS, 1, 3, 4.8, 1, NULL);

		cadPessoa.createChild(L"STATIC", L"Comissão: ", sS, 0, 5, 1, 1, NULL);
		cadPess_salario_hwnd = cadPessoa.createChild(L"EDIT", L"", eS, 1, 5, 4.8, 1, NULL);

		cadPess_statusCriaEdit_hwnd = cadPessoa.createChild(L"STATIC", L"", sS, 0, 8, 1, 1, NULL);
		cadPess_iddCriaEdit_hwnd = cadPessoa.createChild(L"STATIC", L"", sS, 1, 8, 1, 1, NULL);

		cadPessoa.createChild(L"BUTTON", L"cancelar", bS, 3.6, 8, 1, 1, 998);
		cadPessoa.createChild(L"BUTTON", L"salvar", bS, 4.8, 8, 1, 1, 999);


		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case 998: {
			cancModificPessoa();
			break;
		}
		case 999: {
			salvarModificacaoPessoa();
			break;
		}
		case 1000: {
			std::wstring cod;
			if (!selecionarPessoa(hwnd, &cod)) {
				SetWindowText(cadPess_idd_hwnd, cod.c_str());
				puxaPessoa(cadPess_idd_hwnd, 0);
			};
			break;
		}
		case 1001: {
			puxaPessoa(cadPess_idd_hwnd, 0);
			break;
		}
		case 1002: {
			criarNovaPessoa();
			break;
		}
		case 1003: {
			deletarPessoa();
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


		cadPessoa.setPosition(0, retY, w + t, jan.bottom * 0.1);

		break;
	}
	case WM_CLOSE: {
		cadPessoa.finalize();
		EndDialog(hwnd, 0);
		return TRUE;
	}
	}

	return FALSE;
}
INT_PTR criarDBoxCadPessoa(HWND hwnd) {
	return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(DBOX_MAIN_BLANK), hwnd, procCriarDBoxCadPessoa);
}




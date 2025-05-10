#pragma once
#include "funcoes.hpp"
#include "DBCommands.hpp"


void updateFontSize(int);
double wcToD(const wchar_t*);
int getFontSize(HWND& hwin, bool);
long double truncTwo(long double);

//-EXCLUSIVO DE SelecionarPessoa.hpp-//
struct pessoaInfo {
	std::string nome;
	int cod;
	pessoaInfo() {
		nome = "inicialErro";
		cod = 0;
	}
};



//-PEGA AS INFORMACOES DAS PESSOAS DO BANCO DE FORMA SEGURA-//
class pessoaFromDB {
private:
	bool encontrado = false;
	std::vector<std::wstring> infos = { L"null", L"null", L"null" }; //Precaucao

public:
	pessoaFromDB(int personID) {
		std::string command = "select id, UPPER(nome), id*2 from pessoa where id = " + std::to_string(personID) + ";";
		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, 0) != SQLITE_OK) {
			erroBancoDados(L"class pessoaFromDB()");
			infos.clear();
			encontrado = false;
		}
		else {
			int res;
			if (res = sqlite3_step(stmt) == SQLITE_ROW) {
				infos.clear();	//Limpar pois ele nasce com "null".
				infos.push_back(std::to_wstring(sqlite3_column_int(stmt, 0)));
				infos.push_back(charToWstring((const char*)sqlite3_column_text(stmt, 1)));
				infos.push_back(std::to_wstring(sqlite3_column_double(stmt, 2)));
				//for (std::wstring& w : infos) MessageBox(0, w.c_str(), L"na classe", MB_OK);
				if (infos.size() == 3) encontrado = true;	//Somente definir como encontrado se o tamanho do vetor estiver certo.
			}
		}

		sqlite3_finalize(stmt);
	}

	std::vector<std::wstring> vectorPessoa() {
		if (encontrou()) return infos;
		return std::vector<std::wstring>{L"null", L"null", L"null"};	//No caso de erro.
	}
	std::wstring id() {
		if (encontrou()) return infos[0];
		return L"null";
	}
	std::wstring nome() {
		if (encontrou()) return infos[1];
		return L"null";
	}
	std::wstring salario() {
		if (encontrou()) return infos[2];
		return L"null";
	}

	bool encontrou() {
		if (encontrado && infos.size() == 3) return true;
		return false;
	}
};
//-PEGA AS INFORMACOES DOS CORTES DO BANCO DE FORMA SEGURA-//
class corteFromDB {
private:
	bool encontrado = false;
	std::vector<std::wstring> infos = { L"null", L"null", L"null" };

public:
	corteFromDB(int corteID) {
		std::string command = "select id, UPPER(nome), valorpadrao from corte where id = " + std::to_string(corteID) + ";";
		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, 0) != SQLITE_OK) {
			erroBancoDados(L"class corteFromDB()");
			infos.clear();
			encontrado = false;
		}
		else {
			int res;
			if (res = sqlite3_step(stmt) == SQLITE_ROW) {
				infos.clear();
				infos.push_back(std::to_wstring(sqlite3_column_int(stmt, 0)));
				infos.push_back(charToWstring((const char*)sqlite3_column_text(stmt, 1)));
				infos.push_back(std::to_wstring(truncTwo(sqlite3_column_double(stmt, 2))));
				if (infos.size() == 3) encontrado = true;
			}
		}

		sqlite3_finalize(stmt);
	}

	std::vector<std::wstring> vectorCorte() {
		if (encontrou()) return infos;
		return std::vector<std::wstring>{L"null", L"null", L"null"};
	}
	std::wstring id() {
		if (encontrou()) return infos[0];
		return L"null";
	}
	std::wstring nome() {
		if (encontrou()) return infos[1];
		return L"null";
	}
	std::wstring valor() {
		if (encontrou()) return infos[2];
		return L"null";
	}

	bool encontrou() {
		if (encontrado && infos.size() == 3) return true;
		return false;
	}
};






class myClockTimer {
private:
	unsigned long long int limit = 0;
	bool passed = true;
	bool avisado = 0;
	bool initialized = 0;
	unsigned int linhas = 0, maxLengh = 0;

	void errJanNInit(std::wstring adic = L"") {
		//Avisa que a janela do temp nao foi gerada ate que o usuario confirme.
		if (!avisado) MessageBox(0, L"OBJETO\nJANELA DO TEMPORIZADOR NÃO FOI GERADA!", (adic + std::to_wstring(avisado)).c_str(), MB_OK);
		avisado = true;
	}

	void deleteTimer() {
		linhas = 0;
		passed = true;
		limit = 0;
		maxLengh = 0;
		ShowWindow(timedMsg, SW_HIDE);
	}


public:
	void init(HWND mainWin) {
		if (timedMsg == NULL && initialized == false) {
			timedMsg = CreateWindow(L"STATIC", L"", WS_POPUPWINDOW | SS_LEFT, 0, 0, 0, 0, mainWin, 0, NULL, NULL);
			initialized = true;
		}
		else
			MessageBox(0, L"Timed não é nulo!", L"Init", MB_OK);
	}

	void genTimer(std::wstring text, int x = 0, int y = main_areaTotal.bottom - 100) {
		if (initialized) {
			if (timedMsg != NULL) {

				//SendMessage(timedMsg, WM_SETFONT, (WPARAM)fontePadrao, FALSE);
				int len = text.size();

				if (len > maxLengh) maxLengh = len;

				//Se ja tiver uma mensagem sendo exibida, colocar a nova por cimaa.
				if (IsWindowVisible(timedMsg)) {
					wchar_t msg[256] = { 0 };
					GetWindowText(timedMsg, msg, 255);
					text += std::wstring(L"\n") + msg;
				}
				linhas++;

				SetWindowText(timedMsg, L"");
				ShowWindow(timedMsg, SW_HIDE);

				SetWindowText(timedMsg, text.c_str());

				int tamFontHoriz = getFontSize(timedMsg, 0),
					tamFontVerti = getFontSize(timedMsg, 1);

				SetWindowPos(timedMsg, HWND_TOPMOST, x, y,
					tamFontHoriz * maxLengh * 1.05 + tamFontHoriz * 2,
					((linhas < 6) ? linhas * tamFontVerti : 5 * tamFontVerti) + tamFontVerti / 2,
					SWP_FRAMECHANGED);
				passed = false;
				limit = timePassed + 5;
				ShowWindow(timedMsg, SW_SHOW);
			}
			else errJanNInit(L"Gen");
		}
	}


	void TryDeleteTimer() {
		if (initialized) {
			if (timedMsg != NULL) {
				if (passed == false && timePassed > limit) {
					deleteTimer();
				}
			}
			else errJanNInit(L"Del");
		}
	}

}uniqueTimer;








//-USO EXCLUSIVO DO ExecutarCorte.hpp -//
//Informacoes do corte, varias utilidades, cada funcao usa uma informacao especifica.
class corteAdicionadoInfo {
private:
    int iddCorte;
	std::string nome;
    long double vlr;
	int qnt;

public:
	corteAdicionadoInfo(int _iddCorte, std::string _nome, long double _vlr, int _qnt) {
		iddCorte = _iddCorte;
		nome = _nome;
		vlr = truncTwo(_vlr);
		qnt = _qnt;
    }

	int getIddCorte() { return iddCorte; }
	std::string getNome() { return nome; }
	long double getVlr() { return vlr; }
	int getQnt() { return qnt; }
};
//
//class tempAddCorte {
//	corteInfo ci;
//	HWND *valor, *quantidade, *total, *chamadora;
//	std::wstring last_valor, last_desconto, last_quantidade;
//public:
//	tempAddCorte(HWND &vlr, HWND& qnt, HWND& tot, HWND& cham)
//		: valor(&vlr), quantidade(&qnt), total(&tot), chamadora(&cham) {
//		last_valor = last_desconto = last_quantidade = L"0.00";
//	}
//	
//	void verifyAtts() {	//Essa funcao eh acessada incessantemente pela chamadora.
//		wchar_t qnt[256];
//		GetWindowText(*quantidade, qnt, 256);
//		wchar_t vlr[256];
//		GetWindowText(*valor, vlr, 256);
//
//		//Se valor, desconto ou total for modificado, recalcular o total.
//		if (std::wstring(qnt) != last_quantidade || std::wstring(vlr) != last_valor) {
//			last_quantidade = qnt;
//			last_valor = vlr;
//
//			ci.setVlr(wcToD(vlr));
//			ci.qnt = wcToD(qnt);
//
//			SetWindowText(*total, _PickMoney(ci.getVlr() * ci.qnt).c_str());
//		}
//	}
//
//	corteInfo getCi() {
//		return ci;
//	}
//};




//-PARA NAO TER QUE EXAGERAR NOS PARAMETROS DA FUNCAO-//
struct typeChildForBCF {
	int type;
	std::wstring arg;
	typeChildForBCF(int _type = 0, std::wstring _arg = L"0") {
		type = _type;
		arg = _arg;
	}
};
//-CLASSE PARA MOVER JANELAS PROPORCIONALMENTE A UMA JANELA PAI-//
class botaoComFilho {
private:
	float multTamFonte;
	HWND hChamadora;			//Handler da janela que esta instanciando essa classe.
	bool mudamLeftmTop;
	bool objetoOk;
	RECT tRc;	//Para definir onde eh o '0x0' das janelas agrupadas.
	struct children {			//Estrutura dos filhos, seu Handler e suas proporcoes em relacao ao pai.
		HWND hChild;
		long double x, y, w, h;
		children(HWND _hwnd, long double x, long double y, long double w, long double h) : hChild(_hwnd), x(x), y(y), w(w), h(h) {};
	};
	
	std::vector<children> childs;
	std::vector<typeChildForBCF> identChilds;
	
	void alteraRectTotal(long double x, long double y) {
		if (childs.size() <= 1) {
			tRc.left = x;
			tRc.right = x;
			tRc.top = y;
			tRc.bottom = y;
			return;
		}

		if (x < tRc.left)	tRc.left = x;
		if (x > tRc.right)	tRc.right = x;
		if (y < tRc.top)	tRc.top = y;
		if (y > tRc.bottom) tRc.bottom = y;
	}
	
	void createIdentChild(typeChildForBCF ident) {
		identChilds.push_back(ident);


		//Verificando se ha erros no argumento.
		switch (ident.type) {
		case 1: {	//ListView, colunas de tamanho unico.
			if (wcToD(ident.arg.c_str()) < 1) {
				MessageBox(hChamadora, L"IdentChild:Type1 - coluna nao pode ser menor que 1", L"CreateIdentChild", MB_OK | MB_ICONERROR);
			}
			break;
		}
		case 2: {
			int deli = 0;
			int eql = 0;

			for (wchar_t& wC : ident.arg) {
				switch (wC) {
				case L';': deli++; break;
				case L'=': eql++; break;
				}
			}

			if ((deli != eql) || (deli + eql < 2)) {
				MessageBox(hChamadora, L"IdentChild:Type2 - deli ou eql", L"CreateIdentChild", MB_OK | MB_ICONERROR);
			}

			break;
		}
		default:
			break;
		}
	}

	
	void adjust(int x, int y, int w, int h) {
		int thisChild = -1;
		for (children& c : childs) {
			SetWindowPos(c.hChild, NULL,
				x + (w * c.x), y + (h * c.y),
				w * c.w, h * c.h, NULL
			);
			SendMessage(c.hChild, WM_SETFONT, (WPARAM)fontePadrao, FALSE);

			//Realizar alteracoes especificas do tipo do CHILD.
			switch (identChilds[++thisChild].type) {
			case 0: {	//Botao padrao, nao ha nada para fazer aqui.
				break;
			}
			case 1: {	//ListView, aqui atualiza o tamanho das colunas de tamanhos identicos.
				//Recebe: type=1, arg=L"inteiro"... inteiro eh a quantidade de coluna.
				//ex: L"4"
				RECT lvRc = { 0 };
				GetClientRect(c.hChild, &lvRc);

				int qntsColunas = wcToD(identChilds[thisChild].arg.c_str());

				for (int i = 0; i < qntsColunas; i++) {
					ListView_SetColumnWidth(c.hChild, i, lvRc.right / qntsColunas);
				}
				break;
			}
			case 2: {	//ListView, colunas de tamanho unico.
				//Recebe: type=2, arg=L"int=double;int=double"... int eh a coluna e double eh a porcentagem do tamanho.
				//ex: L"0=0.3;1=0.7;"

				RECT lvRc = { 0 };
				GetClientRect(c.hChild, &lvRc);

				std::wstring argumento = identChilds[thisChild].arg;


				int inicio = 0;
				int eql = 0;
				int col = 0;
				int deli = 0;
				double percent = 0;

				//Extrair as porcentagens de cada coluna.
				while (deli+1 < argumento.size()) {
					eql = argumento.find(L'=', inicio);
					col = wcToD(argumento.substr(inicio, eql).c_str());
					deli = argumento.find(L';', inicio);
					percent = wcToD(argumento.substr(eql + 1, deli - eql - 1).c_str());
					inicio = deli + 1;


					ListView_SetColumnWidth(c.hChild, col, percent * lvRc.right);
				}
				break;
			}
			}
		}
	}

public:
	botaoComFilho() {
		hChamadora = NULL;
		multTamFonte = NULL;
		mudamLeftmTop = NULL;
		tRc = { 0 };
		childs.clear();
		identChilds.clear();
		objetoOk = false;
	}

	//Definindo o pai e a quem ele pretence.
	void init(HWND _hChamadora, float _multTamFonte = 1, bool _alteraLeft_Top = true) {
		if (!objetoOk) {
			hChamadora = _hChamadora;
			multTamFonte = _multTamFonte;
			mudamLeftmTop = _alteraLeft_Top;
			tRc = { 0 };
			childs.clear();
			identChilds.clear();
			objetoOk = true;
		}
		else MessageBox(_hChamadora, L"Voce esta tentando inicar o objeto, mas nao o finalizou antes.", L"ERRO", MB_OK);
	}
	void finalize() {
		hChamadora = NULL;
		multTamFonte = NULL;
		mudamLeftmTop = NULL;
		tRc = { 0 };
		childs.clear();
		identChilds.clear();
		objetoOk = false;
	}

	//Define a posicao do amontoado de janela, a posicao x e y levara em conta a janela que estiver mais a esquerda-topo.
	void setPosition(int x, int y, int w = 0, int h = 0) {
		if (objetoOk) {
			RECT rec;
			GetClientRect(hChamadora, &rec);
			updateFontSize(rec.right * multTamFonte);

			if (mudamLeftmTop) {
				x -= w * tRc.left;
				y -= h * tRc.top;
			}

			adjust(x, y, w, h);
		}
	}

	//Adiciona uma janela ja criada ao pai.
	void adoptChild(HWND adptdHwnd, long double xPercent, long double yPercent, long double wPercent, long double hPercent, typeChildForBCF tcBCF = typeChildForBCF(0,L"0")) {
		if (objetoOk) {
			alteraRectTotal(xPercent, yPercent);
			childs.push_back(children(adptdHwnd, xPercent, yPercent, wPercent, hPercent));
			createIdentChild(tcBCF);
		}
	}

	//Cria uma janela e a adiciona ao pai.
	HWND& createChild(std::wstring classe, std::wstring nome, UINT styles, long double xPercent, long double yPercent, long double wPercent, long double hPercent, UINT hMenu, typeChildForBCF tcBCF = typeChildForBCF(0,L"0")) {
		if (objetoOk) {
			alteraRectTotal(xPercent, yPercent);

			HWND tmpChild = CreateWindow(classe.c_str(), nome.c_str(),
				styles,
				0, 0, 0, 0,
				hChamadora, (HMENU)hMenu, NULL, NULL);

			childs.push_back(children(tmpChild, xPercent, yPercent, wPercent, hPercent));
			createIdentChild(tcBCF);

			return childs[childs.size() - 1].hChild;
		}
		return NULLHWND;
	}

	//Retorna os multiplicadores que correspondera ao rect total.
	RECT getRectTotal() {
		return tRc;
	}
};




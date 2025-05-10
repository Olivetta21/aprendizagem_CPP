#include <iostream>
#include <Windows.h>
#include "G:\Outros computadores\3050\School\Codigos\CPP\SistemaDeMercado\mercado.hpp"
#include "G:\Outros computadores\3050\School\Codigos\CPP\ApenasNumeros\convertCharToNum.cpp"

using namespace std;
#define tam 0

class prateleira {
private:
	struct produtos {
		/*unsigned*/ int qnts = 0;
		/*unsigned*/ int cod = 0;
		string name = "ProdutoPadrao";
	};

	/*unsigned*/ int qntsTiposProd = tam;

	produtos* TiposProd = new produtos[qntsTiposProd];
public:

	string nameprateleira;

	prateleira(string name = "sem nome") : nameprateleira(name) {};
	~prateleira() { delete[] TiposProd; }

	void renomeiaPrateleira() {
		cout << "Nome da prateleira: ";
		cin >> nameprateleira;
	}

	bool colocaRetiraProduto(bool coloReti = true) {
		cout << "Codigo do Produto: ";
		/*unsigned*/ int tempCodProd = charToNum();

		int tempSearch = procuraProduto(tempCodProd);

		if (tempSearch >= 0) {
			cout << "Quantidade a " << ((coloReti) ? "colocar: " : "retirar: ");
			/*unsigned*/ int tempQntProduto = charToNum();

			adicionaProdutoNaPrateleira(tempSearch, tempQntProduto, coloReti);
			return true;
		}
		else cout << "Produto nao existente!\n";
		return false;
	}

	void criarProduto() {
		cout << "Codigo do Produto: ";
		/*unsigned*/ int tempCodProd = charToNum();

		if (procuraProduto(tempCodProd) < 0) {
			alteraTamanhoDosTipos();

			TiposProd[qntsTiposProd - 1].cod = tempCodProd;

			cout << "Nome do Produto: ";
			string tempProdName;
			cin >> tempProdName;
			TiposProd[qntsTiposProd - 1].name = tempProdName;

			cout << "Quantos sera adicionado: ";
			/*unsigned*/ int tempQntProd = charToNum();
			TiposProd[qntsTiposProd - 1].qnts = tempQntProd;
		}
		else cout << "Produto ja existe na prateleira!\n";
	}

	void destruirProduto() {
		cout << "Codigo do produto que sera destruido: ";
		/*unsigned*/ int tempCodProd = charToNum();

		int tempSearch = procuraProduto(tempCodProd);

		if (tempSearch >= 0) {
			alteraTamanhoDosTipos(-1, tempSearch);
			cout << "Produto " << tempCodProd << " destruido!\n";
		}
		else cout << "Produto nao encontrado!\n";
	}






	void _ordenar() {
		int* temp = new int[qntsTiposProd];

		for (int i = 0; i < qntsTiposProd; i++) {
			temp[i] = TiposProd[i].cod;
		}

		ordena(temp, qntsTiposProd);

		produtos* tempProd = new produtos[qntsTiposProd];

		for (int i = 0, posi; i < qntsTiposProd; i++) {
			posi = procuraProduto(temp[i]);
			tempProd[i].cod = TiposProd[posi].cod;
			tempProd[i].name = TiposProd[posi].name;
			tempProd[i].qnts = TiposProd[posi].qnts;
		}
		for (int i = 0; i < qntsTiposProd; i++) {
			TiposProd[i].cod = tempProd[i].cod;
			TiposProd[i].name = tempProd[i].name;
			TiposProd[i].qnts = tempProd[i].qnts;
		}

		delete[] tempProd, temp;
	}







	void alteraTamanhoDosTipos(short aumentDiminu = 1, /*unsigned*/ int posi = 0) {
		produtos* TempTiposProd = new produtos[qntsTiposProd];

		transfereProdEntrePrateleiras(TiposProd, TempTiposProd);

		delete[] TiposProd;

		qntsTiposProd += aumentDiminu;	//Aumenta por padrao.

		TiposProd = new produtos[qntsTiposProd];

		transfereProdEntrePrateleiras(TempTiposProd, TiposProd, (aumentDiminu == 1) ? 1 : 2, posi);	//Ternario deve ser 1 se: "padrao".

		delete[] TempTiposProd;
	}

	void transfereProdEntrePrateleiras(const produtos origem[], produtos destino[], /*unsigned*/ short minus = 0, /*unsigned*/ int posi = 0) {
		if (minus == 2) {
			for (int i = 0, j = 0; i < qntsTiposProd; i++, j++) {
				if (j == posi) j++;
				destino[i] = origem[j];
			}
		}
		else {
			for (int i = 0; i < qntsTiposProd - minus; i++) {
				destino[i] = origem[i];
			}
		}
	}

	int procuraProduto(/*unsigned*/ int codProd) {
		for (int i = 0; i < qntsTiposProd; i++) {
			if (TiposProd[i].cod == codProd) return i;
		}
		return -1;
	}

	void adicionaProdutoNaPrateleira(/*unsigned*/ int qual, /*unsigned*/ int quantos, bool coloReti) {
		if (coloReti) TiposProd[qual].qnts += quantos;
		else if (TiposProd[qual].qnts - quantos >= 0) TiposProd[qual].qnts -= quantos;
		else cout << "Impossivel!\n";
	}

	void mostre() {
		cout << "0 - Todos\n1 - Especifico\n";
		int especify = charToNum();
		if (especify == 1) {
			cout << "Codigo: ";
			especify = charToNum();
			int tempSearch = procuraProduto(especify);
			if (tempSearch >= 0) {
				cout << "-------------------\nCodProd: " << TiposProd[tempSearch].cod
				<< "\nQntsProd: " << TiposProd[tempSearch].qnts
				<< "\nNameProd: " << TiposProd[tempSearch].name << "\n-------------------\n";
			}
			else cout << "Produto nao encontrado!\n";

			return;
		}

		for (int i = 0; i < qntsTiposProd; i++) {
			cout << "-------------------\nCodProd: " << TiposProd[i].cod
				<< "\nQntsProd: " << TiposProd[i].qnts
				<< "\nNameProd: " << TiposProd[i].name << "\n-------------------\n";
		}
	}

	void manualAdd(int indice, int cod, char name, int qnts) {
		TiposProd[indice].cod = cod;
		TiposProd[indice].name = name;
		TiposProd[indice].qnts = qnts;
	}
};


int main() {
	int qntsPrateleira = 5;
	prateleira* p = new prateleira[qntsPrateleira];

	prateleira* a = &p[0];

	//for (int i = 0; i < tam; i++) {
	//	p1.manualAdd(i, i * 2, (char)i, (i + 1) * 1.5);
	//}

	do {
		cout << "-------------------\n"
			<< a->nameprateleira << endl
			<< "O que deseja fazer:\n"
			<< "1 - Colocar Produto.\n2 - Retirar Produto.\n"
			<< "3 - Criar Novo Produto.\n4 - Destruir Produto.\n"
			<< "5 - Listar Produtos.\n6 - Ordenar.\n"
			<< "7 - Troca Prateleira.\n0 - Fechar Programa."
			<< "\n-------------------\n";
		/*unsigned*/ short option = charToNum();
		system("cls");

		switch (option) {
		case 0: {
			cout << "Fechar Programa?(0/1): ";
			if (charToNum() == 1) return 0;
			break;
		}
		case 1: {
			a->colocaRetiraProduto();
			break;
		}
		case 2: {
			a->colocaRetiraProduto(false);
			break;
		}
		case 3: {
			a->criarProduto();
			break;
		}
		case 4: {
			a->destruirProduto();
			break;
		}
		case 5: {
			a->mostre();
			break;
		}
		case 6: {
			a->_ordenar();
			break;
		}
		case 7: {
			int choose = 1;
			for (int i = 0; i < qntsPrateleira; i++) {
				cout << i + 1 << " - " << p[i].nameprateleira << endl;
			}
			cin >> choose;

			if (choose < 1 || choose > qntsPrateleira) choose = 1;

			choose--;

			a = &p[choose];

			system("cls");
			break;
		}
		case 8: {
			cout << "Estou criando outro sistema de mercado, porque: \n\n"
				<< "prateleira* tempPrateleiras = new prateleira[qntsPrateleira];\n"
				<< "															 \n"
				<< "for (int i = 0; i < qntsPrateleira; i++) {					 \n"
				<< "	tempPrateleiras[i] = p[i];								 \n"
				<< "}															 \n"
				<< "															 \n"
				<< "delete[] p;													 \n"
				<< "qntsPrateleira++;											 \n"
				<< "															 \n"
				<< "p = new prateleira[qntsPrateleira];							 \n"
				<< "															 \n"
				<< "for (int i = 0; i < qntsPrateleira - 1; i++) {				 \n"
				<< "	p[i] = tempPrateleiras[i];								 \n"
				<< "}															 \n"
				<< "															 \n"
				<< "delete[] tempPrateleiras;									 \n"
				<< "nao funcionou.\n";
			break;
		}
		default: 
			cout << "Invalido\n";
			break;
		}


	} while (true);

}
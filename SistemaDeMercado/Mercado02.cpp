#include <iostream>
#include <vector>
using namespace std;
#include "G:\Outros computadores\3050\School\Codigos\CPP\ApenasNumeros\convertCharToNum.cpp"

struct Product {
	int cod = 0;
	string nome = "padrao";
	int qnt = 0;
	
	void showMe(void) {
		cout << "-------------------"
			<< "\nCodigo: " << cod
			<< "\nNome: " << nome
			<< "\nQuantidade: " << qnt
			<< "\n-------------------\n";
	}
};

struct Shelf {

	Shelf(){}

	vector<Product> products;
	string nome = "Prateleira";

	void showMe(void) { cout << nome << endl; }

	void criarProduto(void) {
		cout << "Codigo do produto: ";
		int cod = charToNum();
		if (!encontrouProduto(cod)) {
			Product tempProd;
			tempProd.cod = cod;
			cout << "Nome do produto: ";
			cin >> tempProd.nome;
			cout << "Quantidade a adicionar: ";
			tempProd.qnt = charToNum();
			products.push_back(tempProd);
			cout << "Produto criado!\n";
		}
		else cout << "Produto ja existe!\n";
	}

	void destruirProduto(void) {
		int qnt = 0;
		cout << "Codigo do produto que sera destruido: ";
		int cod = charToNum();
		if (!encontrouProduto(cod)) { cout << "Produto nao encontrado!\n"; return; }
		vector<Product> tempProd;
		for (Product p : products) {
			if (cod == p.cod) { qnt++; continue; }
			tempProd.push_back(p);
		}
		products.clear();
		for (Product p : tempProd) products.push_back(p);
		cout << qnt << (qnt == 1 ? " produto destruido!" : " produtos destruidos!") << endl;
	}

	bool encontrouProduto(int cod) {
		for (Product p : products) if (cod == p.cod) return true;
		return false;
	}

	void showProduct(void) {
		cout << "Todos = 0 / Especifico = 1: "; int temp = charToNum();
		if (temp == 0) for (Product p : products) p.showMe();
		else {
			cout << "Codigo: "; temp = charToNum();
			if (!encontrouProduto(temp)) { cout << "Produto nao encontrado!\n"; return; }
			for (Product p : products) if (temp == p.cod) p.showMe();
		}
	}

};

struct Armazen {
	string nome = "Armazen";
	vector<Shelf> prateleiras;
	Shelf* prats_ptr = nullptr;

	void displayName(void) {
		cout << "Nome do armazen: " << nome << "\nPrateleira selecionada: " << (estaApontando() ? prats_ptr->nome : "nenhuma");
	}

	bool showPrats(void) {
		int numeracao = 1;
		if (prateleiras.size() < 1) { cout << "Nao existe nenhuma prateleira!\n"; return false; }
		for (Shelf prat : prateleiras) { cout << numeracao++ << " - "; prat.showMe(); }
		return true;
	}
	
	void criarPrateleira(void) {
		Shelf prat;
		cout << "Nome da prateleira: ";
		cin >> prat.nome;
		prateleiras.push_back(prat);
	}

	void destruirPrateleiras(void) {
		int escolha = escolherPratValida(); if (escolha < 0) return;
		Shelf* posicao = &prateleiras[escolha];
		vector<Shelf> tempPrats;
		for (Shelf& prat : prateleiras) {
			if (posicao == &prat) continue;
			tempPrats.push_back(prat);
		}
		prateleiras.~vector();
		for (Shelf prat : tempPrats) {
			prateleiras.push_back(prat);
		}
		cout << "Prateleira destruida!\n";
	}

	int escolherPratValida(void) {
		cout << "Escolha uma dessas prateleiras:\n";
		if (!showPrats()) return -1;
		int escolha = charToNum() - 1;
		if (escolha < 0 || escolha > (int)prateleiras.size()) return -1;
		return escolha;
	}

	bool estaApontando(void) {
		for (Shelf& prats : prateleiras) {
			if (prats_ptr == &prats) return true;
		}
		prats_ptr = nullptr;
		return false;
	}

	void gerenciaPrateleiras(void) {
		cout << "-------------------\n"
			<< "O que deseja fazer:\n"
			<< "1 - Criar Prateleira.\n2 - Destruir Prateleira.\n"
			<< "3 - Mostrar Prateleiras.\n4 - Selecionar uma Prateleira"
			<< "\n-------------------\n";
		short option = charToNum();
		system("cls");

		switch (option) {
		case 1: {
			criarPrateleira();
			break;
		}
		case 2: {
			destruirPrateleiras();
			break;
		}
		case 3: {
			showPrats();
			break;
		}
		case 4: {
			int escolha = escolherPratValida(); if (escolha < 0) return;
			prats_ptr = &prateleiras[escolha];
			break;
		}
		case 100: {
			break;
		}
		}
	}
	
	void gerenciarArmazen(short option) {
		if (option <= 6 && !estaApontando()) option = 0;
		switch (option) {
		case 0: {
			cout << "Primeiro, selecione uma prateleira!\n";
			return;
		}
		case 1: {
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			prats_ptr->criarProduto();
			break;
		}
		case 4: {
			prats_ptr->destruirProduto();
			break;
		}
		case 5: {
			prats_ptr->showProduct();
			break;
		}
		case 6: {
			break;
		}
		case 7: {
			gerenciaPrateleiras();
			break;
		}
		case 100: {
			break;
		}
		}
	}
};

int main() {
	vector<Armazen> armazens;
	armazens.resize(1);

	while (true) {
		cout << "-------------------\n";
		armazens[0].displayName();
		cout << "\n-------------------\n" 
			<< "O que deseja fazer:\n"
			<< "1 - Colocar Produto.\n2 - Retirar Produto.\n"
			<< "3 - Criar Novo Produto.\n4 - Destruir Produto.\n"
			<< "5 - Listar Produtos.\n6 - Ordenar.\n"
			<< "7 - Gerencia Prateleira.\n0 - Fechar Programa."
			<< "\n-------------------\n";
		short option = charToNum();
		system("cls");
		if (option == 0) { cout << "Certeza?(1/0): "; if (charToNum() == 1) return 1; }
		else if (option == 100) {
			armazens.~vector();
			armazens.resize(1);
		}
		else armazens[0].gerenciarArmazen(option);	
	}
}

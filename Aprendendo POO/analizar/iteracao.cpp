#include <iostream>
#include <cstring>
#include "G:\Outros computadores\3050\School\Codigos\CPP\Raiz\enesima.cpp"
#include <vector>

using namespace std;

void cbuff(void) {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
};


using namespace std;

// Classe para representar um Produto
class Product {
public:
    Product(string nome, double preco) : nome(nome), preco(preco) {}

    // Função para exibir informações do produto
    void exibirProduto() {
        cout << "Nome: " << nome << ", Preço: R$" << preco << endl;
    }

private:
    string nome;
    double preco;
};

// Classe para representar uma Prateleira
class Shelf {
public:
    Shelf() {}

    // Função para adicionar um produto à prateleira
    void adicionarProduto(Product produto) {
        products.push_back(produto);
    }

    // Função para exibir todos os produtos na prateleira
    void exibirProdutos() {
        cout << "Produtos na Prateleira:" << endl;
        //for (const Produto& produto : produtos) {
        //    produtos[0].exibirProduto();
        //}
        for (auto it = products.begin(); it != products.end(); ++it) {
            Product num = *it;
            num.exibirProduto();
        }
    }

private:
    vector<Product> products;
};

int main() {
    // Criar prateleiras
    Shelf prateleira1;
    Shelf prateleira2;

    // Adicionar produtos às prateleiras
    Product produto1("Sabonete", 2.5);
    Product produto2("Shampoo", 5.0);
    Product produto6("dddoo", 5.0);
    Product produto4("Shamffffo", 5.0);
    Product produto5("Sggggggpoo", 5.0);

    Product produto3("Detergente", 3.0);

    prateleira1.adicionarProduto(produto1);
    prateleira1.adicionarProduto(produto2);
    prateleira1.adicionarProduto(produto4);
    prateleira1.adicionarProduto(produto5);
    prateleira1.adicionarProduto(produto6);

    prateleira2.adicionarProduto(produto5);

    // Exibir produtos nas prateleiras
    cout << "Prateleira 1:" << endl;
    prateleira1.exibirProdutos();

    cout << "\nPrateleira 2:" << endl;
    prateleira2.exibirProdutos();

    return 0;
}

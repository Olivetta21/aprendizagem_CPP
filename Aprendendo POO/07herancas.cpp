#include <iostream>
using namespace std;

class pessoa {
public:
	string nome;
	int idade;
	int altura;
};

class trabalhador : virtual public pessoa {
	string profissao;
	int anosServico;
public:
	void mostra(void) {
		cout << profissao << endl << anosServico << endl;
	}
};

class aposentados : virtual public pessoa {
	string empresaPagadora;
	int tempoDeContribuicao;
public:
	void mostra(void) {
		cout << empresaPagadora << endl << tempoDeContribuicao << endl;
	}
};

class pensionistas : public trabalhador, public aposentados {

};

void alteraNome(pessoa p) {
	cin >> p.nome;
}


int main() {
	trabalhador grupoTrabalhadores[2];
	aposentados grupoAposentados[2];
	pensionistas grupoPensionistas[2];


	alteraNome(grupoPensionistas[0]);

	int tp;
	cout << "Trabalhador 0, Aposentado 1: ";
	cin >> tp;

}
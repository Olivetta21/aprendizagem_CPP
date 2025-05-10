#include <iostream>
using namespace std;

class mainBanco {
public:
	mainBanco(char, double);
	double getSaldo(void);
	void depositar(double);
	void sacar(double);
private:
	char pessoa;
	double saldo;
};

mainBanco::mainBanco(char pessoa = '*', double saldo = 0) {
	this->pessoa = pessoa;
	this->saldo = saldo;
}

double mainBanco::getSaldo(void) {
	cout << this->pessoa << ": ";
	return saldo;
}

void mainBanco::depositar(double valor) {
	const double aux = saldo;
	saldo += valor;
	const double aux2 = saldo;
	if (aux2 - valor == aux && aux + valor == aux2) cout << "Deposito de " << valor << "R$ realizado com sucesso!\n";
	else {
		saldo = aux;
		cout << "Erro ao depositar!\n";
	}
}

void mainBanco::sacar(double valor) {
	if (saldo - valor >= 0) {
		const double aux = saldo;
		saldo -= valor;
		const double aux2 = saldo;
		if (aux2 + valor == aux && aux - valor == aux2) cout << "Saque de " << valor << "R$ realizado com sucesso!\n";
		else {
			saldo = aux;
			cout << "Erro ao sacar!\n";
		}
	}
	else cout << "Saldo insuficiente!\n";
}

int main() {
	mainBanco banco('i', 1234);

	for (int opcao = 0; opcao >= 0;) {
		cout << "Saldo de "; cout << banco.getSaldo() << "\n";
		cout << "| Deposito: 1 | Saque: 2 | Sair: 0 |\n-opcao: ";
		cin >> opcao;
		double valor = 0;
		switch (opcao) {
			default: {
				opcao = -1;
				break;
			}
			case 1: {
				cout << "Valor de deposito: ";
				cin >> valor;
				if (valor <= 0) break;
				banco.depositar(valor);
				break;
			}
			case 2: {
				cout << "Valor de saque: ";
				cin >> valor;
				if (valor <= 0) break;
				banco.sacar(valor);
				break;
			}
		}		
	}

	cout << "Saldo final de "; cout << banco.getSaldo();
}
//Um sistema de banco.
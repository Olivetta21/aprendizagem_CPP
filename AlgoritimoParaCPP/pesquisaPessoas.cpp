#include <iostream>
using namespace std;

class pesquisa {
public:
	string nome = "null";
	int idade = 0;
	int sexo = 0;
};

int main() {
	pesquisa pessoa[5];
	int gender = 1;

	for (int i = 0; i < 5; i++) {
		cout << "Nome: ";
		cin >> pessoa[i].nome;
		cout << "Idade: ";
		cin >> pessoa[i].idade;
		cout << "Sexo (1=Homem, 0=Mulher): ";
		cin >> pessoa[i].sexo;
		cout << endl;
	}
	
	for (int i = 0; i < 5; i++) {
		if (i == 0) {
			if (gender == 1) cout << "\nLista de Homens:\n";
			else cout << "Lista de Mulheres:\n";
		}
		if (pessoa[i].sexo == gender) {
			cout << "Nome: " << pessoa[i].nome << endl;
			cout << "Idade: " <<  pessoa[i].idade << endl;
			cout << "Sexo: ";
			if (pessoa[i].sexo == 1) cout << "Homem\n\n";
			else cout << "Mulher\n\n";
		}
		if (i >= 4 && gender == 1) {
			gender = 0;
			i = -1;
		}
	}
}
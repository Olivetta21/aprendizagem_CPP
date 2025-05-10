#include <iostream>
using namespace std;

class cabecaCubo {
private:
	int tamanho = 0;
	int lado = 0;

public:
	cabecaCubo(void) {

	}
	cabecaCubo(int a) {
		this->lado = a;
	}

	int tamanhoo(void) {
		if (lado > 50) {
			if (lado % 10 == 0) this->tamanho = lado / 10;
			else if (lado % 20 == 0) this->tamanho = lado / 20;
			else if (lado % 2 == 0) this->tamanho = lado / 2;
			else this->tamanho = 0;
		}
		else this->tamanho = lado;
		return tamanho;
	}
};

class Cubos {
private:
	int lado1 = 0;
	cabecaCubo cabeca;

public:
	Cubos(void) {
		this->lado1 = 10;
	}

	Cubos(int a, int b=1) {
		this->lado1 = a * b;
	}

	int tamanhoDaCabeça() {
		cabecaCubo cabeca(lado1);
		return cabeca.tamanhoo();
	}

	int calcularTamanho() {
		return lado1 + 100;
	}

};

int main() {
	const int a = 30;
	Cubos arrayCubo[a];

	for (int i = 0; i < a; i++) {
		arrayCubo[i] = Cubos(3 * i, 25 + (i * (i + 1)));
	}
	for (int i = 0; i < a; i++) {
		cout << "array" << i << ": Tamanho-> " << arrayCubo[i].calcularTamanho() << " Cabeca-> " << arrayCubo[i].tamanhoDaCabeça() << "\n";
	}



	cout << "Criando objetos \"Cubo\"(s)...\n";

	Cubos Cubo0;
	Cubos Cubo1(50);
	Cubos Cubo2(3, 25);



	cout
		<< "Tamanho final: " << Cubo0.calcularTamanho() << "\n"
		<< "Tamanho final: " << Cubo1.calcularTamanho() << "\n"
		<< "Tamanho final: " << Cubo2.calcularTamanho() << "\n";

	cout
		<< "Tamanho Cabeca: " << Cubo0.tamanhoDaCabeça() << "\n"
		<< "Tamanho Cabeca: " << Cubo1.tamanhoDaCabeça() << "\n"
		<< "Tamanho Cabeca: " << Cubo2.tamanhoDaCabeça() << "\n";


}
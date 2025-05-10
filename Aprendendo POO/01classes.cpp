#include <iostream>
using namespace std;

void aumente(int* a) {
	*a += 3;
}

void diminua(int* a) {
	if (*a - 3 <= 0) cout << "impossivel! numero menor ou igual a zero, retornando ";
	else *a -= 3;
}

class Cubos {
private:
	int lado1 = 0;
	int lado2 = 0;
	int lado3 = 6;

public:
	Cubos(void) {
		this->lado1 = 22;
		this->lado2 = 22;
		cout << "\n\nISSO NAO DEVERIA APARECER\n\n"; 
	}
	Cubos(int l1, int l2) {
		this->lado1 = l1;
		this->lado2 = l2;
	}

	float calculoPadrao(int a, int b) {
		float aa = a + b;
		aa = aa / 2;
		aa += b - a;
		aa /= lado3;
		return aa;
	}

	void aumenteLado3(void) {
		cout << "Lado3 aumentado de " << lado3 << " ";
		aumente(&lado3);
		cout << "para " << lado3 << "\n";
	}

	void diminuaLado3(void) {
		cout << "Lado3 diminuido de " << lado3 << " ";
		diminua(&lado3);
		cout << "para " << lado3 << "\n";
	}

	float calculoMatheus() {
		return calculoPadrao(lado1 + 100, lado2 + 200);
	}

	float calculoLucas() {
		return calculoPadrao(lado1 + 50, lado2 + 150);
	}

	void mostraLados() {
		cout
			<< "Lado1: " << lado1 << "\t"
			<< "Lado2: " << lado2 << "\t"
			<< "Lado3: " << lado3 << "\n";
	}
};

int main() {
	cout << "Criando objeto \"Cubo\"...\n";
	Cubos lCubo;
	lCubo.mostraLados();

	Cubos Cubo(30, 50);

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nRealiza calculo do Matheus: ";
	cout << Cubo.calculoMatheus();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nRealiza calculo do Lucas: ";
	cout << Cubo.calculoLucas();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nAumenta lado3:\n";
	Cubo.aumenteLado3();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nAumenta lado3:\n";
	Cubo.aumenteLado3();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nRealiza calculo do Matheus: ";
	cout << Cubo.calculoMatheus();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nRealiza calculo do Lucas: ";
	cout << Cubo.calculoLucas();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nDiminui duas vezes o lado3:\n";
	Cubo.diminuaLado3();
	Cubo.diminuaLado3();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nDiminui o lado3:\n";
	Cubo.diminuaLado3();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();

	cout << "\nDiminui o lado3:\n";
	Cubo.diminuaLado3();

	cout << "\nMostrando lados:\n";
	Cubo.mostraLados();
	

}

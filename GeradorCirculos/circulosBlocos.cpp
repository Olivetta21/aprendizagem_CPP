#include <iostream>
#include "raizepotencia.hpp"
#include <Windows.h>
#include <iomanip>

using namespace std;

class circulo {
public:
	
	circulo(int raio = 0, float espessura = 0) :
		raio(raio),
		espessura(espessura),
		par((this->raio % 2 == 0) ? true : false),
		tamMatrix(raio * 2 + 1),
		a(0),
		matrix(new int* [tamMatrix])
	{
		for (int i = 0; i < tamMatrix; i++) {
			matrix[i] = new int[tamMatrix];
		}
	}
	~circulo(){
		for (int i = 0; i < tamMatrix; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void allZero(void) {
		for (int i = 0; i < tamMatrix; i++) {
			for (int j = 0; j < tamMatrix; j++) {
				matrix[i][j] = 0;
			}
		}
	}

	void showMatrix(void) {
		for (int i = 0; i < tamMatrix; i++) {
			for (int j = 0; j < tamMatrix; j++) {
				cout << (
					(matrix[i][j] == 1) ? '@' :
					(matrix[i][j] == 2) ? 'X' :
					' '
					) << " ";
			}
			cout << endl;
		}
	}


	void prepare() {
		for (int i = 0; i < tamMatrix; i++) {
			int distX = raio - i;
			for (int j = 0; j < tamMatrix; j++) {
				int distY = raio - j;
				matrix[i][j] = pinte(distX, distY);
			}
		}
	}
	
	int pinte(int x, int y) {
		if (x < 0) x *= -1;
		if (y < 0) y *= -1;
		double distancia = raizquadrada(potencia(x, 2) + potencia(y, 2));

		//cout << fixed << setprecision(2) << setw(5) << setfill('0') << distancia; cout << " | ";
		//a++;
		//if (a >= tamMatrix) { cout << endl; a = 0; }

		if (distancia <= raio+0.2 && distancia >= (double)raio * espessura) return 1;

		return 0;
	}

	void showInfo(void) {
		cout << "\nraio: " << raio;
		cout << "\npar: " << ((par) ? "sim" : "nao");
		cout << endl;
	}

private:
	const int raio;
	const float espessura;
	const bool par;
	const int tamMatrix;
	int** matrix;
	int a;

};


int main() {
	int raio = 0;
	float wlinha = 0;
	do {
		cout << "Raio: ";
		do {
			raio = -1;
			float temp = 0;
			cin >> temp;
			if (temp < 0) {
				wlinha = (100 + temp) * 0.01;
				cout << "Espessura da linha definido para: " << temp * -1 << "%\n";
			}
			else raio = temp;

		} while (raio < 0);
		
		//system("cls");
		circulo novo(raio, wlinha);
		novo.prepare();
		novo.showMatrix();
	} while (true);

	//while (true) {
	//	while(raio <= 500) {
	//		circulo novo(raio, 1);
	//		novo.prepare();
	//		//system("cls");
	//		//novo.showMatrix();
	//		raio++;
	//	}
	//	cout << "1";
	//	while (raio > 0) {
	//		circulo novo(raio, 1);
	//		novo.prepare();
	//		//system("cls");
	//		//novo.showMatrix();
	//		raio--;
	//	}
	//	cout << "2";
	//}

}
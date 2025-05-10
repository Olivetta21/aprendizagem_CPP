#include <iostream>
#include <random>
using namespace std;
#define tam 2


mt19937 gen(0);
uniform_int_distribution<int> distribution(-3, 3);

int main() {
	int matA[tam][tam];
	int matB[tam][tam];
	int matC[tam][tam];

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			matA[i][j] = distribution(gen);
			matB[i][j] = distribution(gen);
			matC[i][j] = 0;
		}
	}


	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			for (int k = 0; k < tam; k++) {
				
				matC[i][j] = (matA[i][j] * matB[k][i]) + matC[i][j];

			}
		}
	}


	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			cout << matA[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			cout << matB[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			cout << matC[i][j] << " ";
		}
		cout << endl;
	}

}
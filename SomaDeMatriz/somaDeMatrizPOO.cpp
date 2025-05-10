#include <iostream>
#include <random>
using namespace std;
#define tam 2

mt19937 gen(9);
uniform_int_distribution<int> distribution(1, 10);

class matriz {
public:
	matriz(int taman = tam) : t(taman) {
		mat = new int* [t];

		for (int i = 0; i < t; i++) {
			mat[i] = new int[t];
		}
		for (int i = 0; i < t; i++) {
			for (int j = 0; j < t; j++) {
				mat[i][j] = 0;
			}
		}
	}

	matriz(const matriz& copy) : t(copy.t){
		mat = new int*[t];
		for (int i = 0; i < t; i++) {
			mat[i] = new int[t];
		}

		for (int i = 0; i < t; i++) {
			for (int j = 0; j < t; j++) {
				mat[i][j] = 0;
			}
		}
	}

	~matriz() {
		for (int i = 0; i < t; i++) {
			delete[] mat[i];
		}
		delete[] mat;
	}

	matriz operator+(const matriz& sec) const {
		matriz temp(sec);

		for (int i = 0; i < t; i++) {
			for (int j = 0; j < t; j++) {
				for (int k = 0; k < t; k++) {
					temp.mat[i][j] = (this->mat[i][j] * sec.mat[k][i]) + temp.mat[i][j];
				}
			}
		}

		return temp;
	}

	void insMatriz(int i, int j, int value) {
		mat[i][j] = value;
	}

	void showMatriz(void) {
		for (int i = 0; i < t; i++) {
			for (int j = 0; j < t; j++) {
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

private:
	int** mat;
	int t;

};

void aleatorize(matriz& esse) {
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			esse.insMatriz(i, j, distribution(gen));
		}
	}
}


int main() {
	int qnts;
	cout << "Quantos: ";
	cin >> qnts;
	matriz* conjunto = new matriz[qnts];

	for (int i = 0; i < qnts; i++) {
		aleatorize(conjunto[i]);
	}
	for (int i = 0; i < qnts - 4; i++) {
		(conjunto[i] + conjunto[i + 1] + conjunto[i + 2] + conjunto[i + 3] + conjunto[i + 4]).showMatriz();
	}
	cin >> qnts;


	//matriz um;
	//matriz dois;
	//int valor = 1;
	//for (int i = 0; i < tam; i++) {
	//	for (int j = 0; j < tam; j++) {
	//		um.insMatriz(i, j, valor);
	//		dois.insMatriz(j, i, valor);
	//		valor++;
	//	}
	//}
	//
	//matriz res = (um + dois);
	//matriz res2 = (dois + um);
	//um.showMatriz();
	//dois.showMatriz();
	//res.showMatriz();
	//res2.showMatriz();


}

/*
int main() {
	int matA[tam][tam]{
		{1,2},
		{3,4},
	};
	int matB[tam][tam]{
		{1,3},
		{2,4},
	};
	int matC[tam][tam]{
		{0,0},
		{0,0},
	};

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			matA[i][j] = distribution(gen);
			matB[i][j] = distribution(gen);
			matC[i][j] = distribution(gen);
		}
	}


	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			int bk = matA[i][j];
			matA[i][j] = 0;
			for (int k = 0; k < tam; k++) {
				matA[i][j] += bk * matB[k][i];
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
*/
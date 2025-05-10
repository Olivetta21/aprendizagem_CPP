//Programa principal.
#include <iostream>
#include "tempo.h"
using namespace std;


int main() {
	Tempo che, sai;
	cout << "Chegada: ";
	cin >> che;
	cout << "Saida: ";
	cin >> sai;

	cout << "Tempo de permanencia: " << sai - che;
	cout << "\nnegativo: " << che + sai;
}
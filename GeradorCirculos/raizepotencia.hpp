//#include <iostream>
//using namespace std;

double potencia(double num, const int pot = 2) {
	cout << "Dasativado por conta de muitas mudancas, utilize:\n"
		<< "G:\\Outros computadores\\3050\\School\\Codigos\\CPP\\Raiz\\enesima.cpp";
	while (true) { cin.get(); }

	if (pot < 0) return 0;

	double resp = 1;
	for (int i = 1; i <= pot; i++) {
		resp *= num;
	}
	return resp;
}

double raizquadrada(const double raizDe, const int indice = 2) {
	cout << "Dasativado por conta de muitas mudancas, utilize:\n"
		<< "G:\\Outros computadores\\3050\\School\\Codigos\\CPP\\Raiz\\enesima.cpp";
	while (true) { cin.get(); }

	if (raizDe < 0 || indice < 1) return 0;

	double resposta = (raizDe == 0) ? 0 : 1;
	double testar = 0;

	while (testar < raizDe - 0.00001 || testar > raizDe + 0.00001) {
		resposta =
			(
				(raizDe / (potencia(resposta, indice - 1)))
				+
				((indice - 1) * resposta)
			)
			*
			((double)1 / indice);

		testar = potencia(resposta, indice);
	}

	return resposta;
}

//int main() {
//	cout << potencia(4) << endl << potencia(4, 3) << endl << raizquadrada(10) << endl << raizquadrada(10, 3);
//}
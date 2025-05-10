#include <iostream>
#include <limits>
using namespace std;
#define TAM 30

float soma(float g[TAM], int& tot) {
	float sum = 0;
	for (int i = 0; i < tot; i++) {
		sum += g[i];
	}
	return sum;
}

void copy(float from[TAM], int& tot, float to[TAM]) {
	for (int i = 0; i < tot; i++) {
		to[i] = from[i];
	}
}

void show(float g[TAM], int& tot){
	cout << "Melhor soma: " << soma(g, tot);
	cout << "\nNumeros:\n";
	for (int i = 0; i < tot; i++) {
		cout << "+ " << g[i] << " ";
	}
}


int main() {
	float vectors[TAM]{
1472.44,
665.03,
1051.49,
5129.07,
1079.06,
1625.45,
1295.01,
812.11,
1708.93,
2220.14,
1085.43,
458.10,
1871.63,
2173.85,
660.00,
1061.18,
1630.00,
842.74,
1262.39,
1193.29,
1444.48,
1918.39,
919.22,
3110.94,
1190.28,
1639.67,
949.40,
1699.00,
1751.47,
4870.39
	    };
	float melhor = numeric_limits<int>::max();	//Necessario para calculo.

	float melhorGrupo[TAM];
	int limite = 0;	//Necessario para imprimir somente o necessario.
	float objetivo = 5188.35;

	long calculos = 0;
	long long interCalculos = 0;

	for (int i = (1 << TAM); i >= 0; i--) {
		calculos++;
		float grupoAtual[TAM];
		int counter = 0;	//Onde eh o fim do atual grupo.
		for (int j = 0; j < TAM; j++) {
			interCalculos++;
			if (i & (1 << j)) {	//Compara bit-a-bit o numero "i": se "i" conter algum bit 1 na mesma posicao que "1 << j" = TRUE,
				grupoAtual[counter++] = vectors[j];											//Isso faz todas combinacoes possiveis.
			}
		}
		float diff = soma(grupoAtual, counter) - objetivo;
		diff = (diff < 0) ? diff * -1 : diff;	//Diferenca bruta.
		if (diff < melhor) {	//Definir o grupo que teve a menor diferenca perante objetivo.
			melhor = diff;
			limite = counter;
			copy(grupoAtual, counter, melhorGrupo);
			if (!melhor) break;	//Se a diferenca for exatamente 0, entao ja encontrou o melhor resultado possivel.
		}
	}

	show(melhorGrupo, limite);
	cout << "\n\nTestes realizados: " << calculos << "\nComparacoes: " << interCalculos;

	return 0;
}

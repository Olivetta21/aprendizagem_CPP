#include <iostream>
#include <cmath>
using namespace std;

#define TAM 30


void invert(long double& a, long double& b) {
    long double tmp = a;
    a = b;
    b = tmp;
}




//Selecionar o pivo, e colocar os menores a esquerda e maiores a direita.
int particionar(long double v[], int low, int high) {
    long double pivo = v[high]; //pivo.
    int i = (low - 1);  //indice menor elemento.

    for (int j = low; j < high; j++) {
        if (v[j] <= pivo) {
            i++; //inverter o menor atual pelo oque esta no indice.
            invert(v[i], v[j]);
        }
    }
    invert(v[i + 1], v[high]);
    return (i + 1);
}
void ordenar(long double v[], int low, int high) {
    if (low < high) {
        int pi = particionar(v, low, high);

        // Ordena antes e depois da partição
        ordenar(v, low, pi - 1);
        ordenar(v, pi + 1, high);
    }
}


//Define onde o bitMap comeca, evitando que ele some os numeros pequenos, já que é impossível de chegar no pretendido com eles.
int eliminarPequenos(long double v[], int tam, long double limite){
	int comecarEm = -1;
	long double somas = 0;

    cout << "\nPequenos: ";
	for (int i = tam-1; i >= 0; i--){
		somas += v[i];
		if (somas >= limite) {
            cout << "\nComecar em:" << comecarEm << "\n";
			return comecarEm;
		}
		cout << v[i] << "|";
		comecarEm = tam - 1 - i;
	}

	return -1;
}

long double soma(long double g[TAM], int& tot) {
	long double sum = 0;
	for (int i = 0; i < tot; i++) {
		sum += g[i];
	}
	return sum;
}

void copyVec(long double from[TAM], int& tot, long double to[TAM]) {
	for (int i = 0; i < tot; i++) {
		to[i] = from[i];
	}
}

void desc(long double v[], int tam){
    long double tmp[tam];

    for (int i = 0; i < tam; i++){
        tmp[tam-1-i] = v[i];
    }

    copyVec(tmp, tam, v);
}

void showVec(long double v[], int tam) {
    for (int i = 0; i < tam; i++) {
        cout << "|" << v[i];
    }
    cout << "|\n";
}



void show(long double g[TAM], int& tot){
	cout << "Melhor soma: " << soma(g, tot);
	cout << "\nNumeros:\n";
	for (int i = 0; i < tot; i++) {
		cout << "+ " << g[i] << " ";
	}
}



int main(){
	long double valores[TAM]{
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
	long double melhorGrupo[TAM]; int limite = 0;
	long double pretendido = 14037.98;
	long double melhor = -1;

	int calculos = 0, subc = 0;

	ordenar(valores, 0, TAM -1);
	desc(valores, TAM);
	showVec(valores, TAM);


	int start = eliminarPequenos(valores, TAM, pretendido);
	//cout << "\nStart: " << start << "\n";
	if (start < 0) return 22;


	for (int i = (1 << start); i < (1 << TAM-1); i++) {
        calculos++;

		long double grupoAtual[TAM];
		int counter = 0;	//Onde eh o fim do atual grupo.

		for (int j = 0; j < TAM; j++) {
            subc++;
			if (i & (1 << j)) {	//Compara bit-a-bit o numero "i": se "i" conter algum bit 1 na mesma posicao que "1 << j" = TRUE,
				grupoAtual[counter++] = valores[TAM - 1 - j];											//Isso faz todas combinacoes possiveis.
			}
		}

        //cout << "\nGrupo atual: "<< "\n";
        //showVec(grupoAtual, counter);
        //cout << "\nSoma: " << soma(grupoAtual, counter) << "\n";


		long double diff = soma(grupoAtual, counter);

		if (diff <= pretendido) {	//Definir o grupo que teve a menor diferenca perante objetivo.
			limite = counter;
			copyVec(grupoAtual, limite, melhorGrupo);
			if (diff == pretendido) break;	//Se a diferenca for exatamente 0, entao ja encontrou o melhor resultado possivel.
		}
		else break;
	}

    cout << "Calculos: " << calculos << " - Subc: " << subc << "\n";
	show(melhorGrupo, limite);

}








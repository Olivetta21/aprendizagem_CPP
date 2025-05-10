#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

//Gerador de números aleatórios-------------------------------------//
mt19937 gen(9);
uniform_int_distribution<int> distribution(0, 1000000);
//------------------------------------------------------------------//

bool INFORMACOES[]{
	1,			//Tamanho do vetor.
	0,			//Mostrar grupo.
	0,			//Mostrar resultado.
	0,			//Mostrar calculos.
	1,			//Mostrar tempo de execucao.
};

//Prototipos das funcoes.-------------------------------------------//
void definirValoresAOrdenar(void);
int testeErro(void);
int contarGruposNaoInt(void);
void encontrarLimites(void);
int maiorDoGrupoX(int);
int menorDoGrupoY(int);
void mostrarGrupo(int);
void trocarDoisValores(int&, int&);
//------------------------------------------------------------------//

//Constantes.-------------------------------------------------------//
/*150 para numeros grandes*/
int	_tVt = 100000, //A fins de testes, o tamanho do vetor, e tamanho do grupo sao 11 e 3.
			_tGp = 420;

const int _tamanhoDoGrupoNaoInt = _tVt % _tGp;
/* 11 MOD 3 = 2 */
const int _qntsGruposInt = _tVt / _tGp;
/* 11/3 = 3.666 = 3 */
const bool _qntsGruposNaoInt = contarGruposNaoInt();
/* 1 */
const int _totalGrupos = _qntsGruposInt + _qntsGruposNaoInt;
/* 3 + 1 = 4 */
int contarGruposNaoInt(void) {
	int qntsGruposNaoInt = 1;	//Soh e possivel existir um grupo nao inteiro.
	if (_tamanhoDoGrupoNaoInt == 0)  qntsGruposNaoInt = 0;	//Se o resto da divisao for zero, entao nao existe grupos nao inteiros.
	return qntsGruposNaoInt;
}
//------------------------------------------------------------------//

//Principais variaveis----------------------------------------------//
int* _vetPrinc = new int[_tVt];
//------------------------------------------------------------------//

//Descobrir o inicio e fim de cada grupo no vetor.------------------------------//
int* _inicioDoGrupo = new int[_totalGrupos];
int* _fimDoGrupo = new int[_totalGrupos];
void encontrarLimites(void) {
	for (int grupo = 1; grupo <= _totalGrupos; grupo++) {
		_inicioDoGrupo[grupo-1] = grupo * _tGp - _tGp;
		/* 2 * 3 = 6 - 3 = 3 */
		_fimDoGrupo[grupo-1] = _inicioDoGrupo[grupo-1] + _tGp - 1;
		/* 3 + 3 = 6 - 1 = 5 */
	}
	if (_tamanhoDoGrupoNaoInt > 0) {
		_fimDoGrupo[_totalGrupos - 1] = _inicioDoGrupo[_totalGrupos - 1] - 1 + _tamanhoDoGrupoNaoInt;
		/* 9 - 1 = 8 + 1 = 9 */
	}
}
//------------------------------------------------------------------//

//Encontrar o maior do grupo----------------------------------------//
int _posiMenorY = -999999;
int _posiMaiorX = -999999;
int maiorDoGrupoX(int grupoX) {
	_posiMaiorX = _inicioDoGrupo[grupoX - 1];
	int maior = _vetPrinc[_posiMaiorX];

	for (int i = _inicioDoGrupo[grupoX - 1] + 1; i <= _fimDoGrupo[grupoX - 1]; i++) {
		if (_vetPrinc[i] > maior) {
			maior = _vetPrinc[i];
			_posiMaiorX = i;
		}
	}
	return maior;
}
int menorDoGrupoY(int grupoY) {
	_posiMenorY = _inicioDoGrupo[grupoY - 1];
	int menor = _vetPrinc[_posiMenorY];

	for (int i = _inicioDoGrupo[grupoY - 1] + 1; i <= _fimDoGrupo[grupoY - 1]; i++) {
		if (_vetPrinc[i] < menor) {
			menor = _vetPrinc[i];
			_posiMenorY = i;
		}
	}
	return menor;
}
//------------------------------------------------------------------//

//Realizar a troca dos valores--------------------------------------//
void trocarDoisValores(int &a, int &b) {
	int aux = a;
	a = b;
	b = aux;
}
//------------------------------------------------------------------//

//Mostrar o conteudo do grupo---------------------------------------//
void mostrarGrupo(int grupo) {
	for (int i = _inicioDoGrupo[grupo - 1]; i <= _fimDoGrupo[grupo - 1]; i++) {
		cout << _vetPrinc[i] << ";";
	}
}
//------------------------------------------------------------------//

int main() {
	if (testeErro() == 1) return 1;
	definirValoresAOrdenar(); //Os numeros que serao ordenados serao definidos aqui.
	encontrarLimites();	//Encontrar onde comeca e termina cada grupo.

	if (INFORMACOES[0]) {	//Informacoes dos grupos.
		cout
			<< "Tamanho do vetor: " << _tVt
			<< "\nTamanho maximo dos grupos: " << _tGp
			<< "\n----------------------------"
			<< "\nGrupos inteiros : " << _qntsGruposInt
			<< "\nGrupos nao inteiros: " << _qntsGruposNaoInt
			<< "\nTotal de grupos: " << _totalGrupos
			<< "\nTamanho do grupo nao inteiro: " << _tamanhoDoGrupoNaoInt;
	}
	if (INFORMACOES[1]) {	//Mostrar o grupo e o inicio e fim dele.
		cout << "\n\n----------------------------\n";
		for (int grupo = 1; grupo <= _totalGrupos; grupo++) {
			cout << "~ ~ ~ ~ Grupo " << grupo << ": ~ ~ ~ ~\n";
			mostrarGrupo(grupo);	//Mostra o conteudo dentro do grupo atual.
			cout << "\nInicio: " << _inicioDoGrupo[grupo - 1] << "\tFim: " << _fimDoGrupo[grupo - 1] << "\n\n";
		}
	}

	if (INFORMACOES[3]) cout << "----------------------------\n";
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	for (int grupoX = 1; grupoX < _totalGrupos; grupoX++) {
		for (int grupoY = grupoX + 1, maiorX = maiorDoGrupoX(grupoX); grupoY <= _totalGrupos;) {
			if (maiorX <= menorDoGrupoY(grupoY)) grupoY++;
			else {
				if (INFORMACOES[3]) cout << "mX:" << _vetPrinc[_posiMaiorX] << " mY:" << _vetPrinc[_posiMenorY] << "\n";
				trocarDoisValores(_vetPrinc[_posiMaiorX], _vetPrinc[_posiMenorY]);
				maiorX = maiorDoGrupoX(grupoX);
			}
		}
	}
	high_resolution_clock::time_point endTime = high_resolution_clock::now();

	//Mostrar Ordenado
	if (INFORMACOES[2]) {
		cout << "\n----------------------------";
		for (int grupo = 1; grupo <= _totalGrupos; grupo++) {
			cout << "\nGrupo " << grupo << ":\n";
			mostrarGrupo(grupo);	//Mostra o conteudo dentro do grupo atual.
		}
	}
	if (INFORMACOES[4]) {
		cout << "\n\n----------------------------\n";
		auto duration = duration_cast<milliseconds>(endTime - startTime).count();
		cout << "Tempo de execucao: " << duration << "ms";
		if (INFORMACOES[3]) cout << " - Os calculos estao ativados, o tempo de execucao nao esta correto!\n";
	}

	cout << "\n\nFinalizado\n\n";
	system("pause");
	return 0;
}

//Definir os valores do vetor que sera ordenado---------------------//
void definirValoresAOrdenar(void) {
	int* definirVetor = new int[_tVt] {
		4,1,7,10,7,9,6,7,5,10,2	//Vetor principal, onde os numeros a ser ordenados virao.
	};
	if (true) {	//ALEATORIO?
		for (int i = 0; i < _tVt; i++) {	//Colocar numeros aleatorios no vetor.
			definirVetor[i] = distribution(gen);
		}
	}
	for (int i = 0; i < _tVt; i++) {	//Pegar o vetor digitado pelo usuario e passar para o vetor dos calculos.
		_vetPrinc[i] = definirVetor[i];
	}
	delete[] definirVetor;
}
//------------------------------------------------------------------//

int testeErro(void) {
	bool comErro = 0;
	int tgp = _tGp;
	int tvt = _tVt;

	if (_tamanhoDoGrupoNaoInt > tgp - 1) { cout << "\nTamanho do grupo nao-inteiro esta maior que o maximo."; comErro = 1; }
	if (_qntsGruposInt * tgp + _tamanhoDoGrupoNaoInt != tvt) { cout << "\nA soma do tamanho dos grupos inteiros com os nao-interios nao resulta no tamanho do vetor."; comErro = 1; }
	if (tgp > tvt) { cout << "\nO tamanho do grupo nao pode ser maior que o tamanho do vetor."; comErro = 1; }

	return comErro;
}

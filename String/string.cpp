#include <iostream>
#include <string>
using namespace std;

bool isPalindr(string linha) {	//Recebe uma linha e retorna verdade ou falso.
	for (int i = 0, j = linha.size() - 1; i < j; i++, j--) {
		//i: comeco da linha. j:final da linha. size() pega o tamanho da linha, -1 pois "linha" eh um vetor.
		if (linha[i] != linha[j]) {	/*Percorre do começo e fim até se encontrarem, verificando se os caracteres 
									sao iguais.*/
			return false;	//Se sequer um for diferente: retorne com "falso", pois ja deixa de ser palindromo.
		}
	}
	return true;	//Se todos forem iguais: retorne com "verdadeiro".
}

int main() {
	string linha;	//Variavel para armazenar a linha.
	while (true){	//Loop infinito para digitar varias linhas.
		cout << "Digite uma linha: ";
		getline(cin, linha);	//Leitura atraves do cin para a variavel "linha".
		
		if (isPalindr(linha)) cout << "Palindromo!\n\n";	//Se o retorno da funcao for "true": palindromo.
		else cout << "NAO palindromo!\n\n";	//Senao: nao eh palindromo.
	}
}

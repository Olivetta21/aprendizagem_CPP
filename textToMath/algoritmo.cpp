/*string arg = 2 * (1 + 3)


etpa1
(1 + (1 - (2 + 3)) * (2 + 2) - 1 + (2 * (9 - 5)))

etpa1
4:12  7 : 11  14 : 18  22 : 30  25 : 29  1 : 31

etpa1
7 : 11 0 2 + 3 5
14 : 18 0 2 + 2 4
25 : 29 0 9 - 5 4
-- -
4 : 12 1
22 : 30 1
1 : 31 5

* ********
etpa2
(1 + (1 - 5) * 4 - 1 + (2 * 4))

etpa2
4:8 0
14 : 18 0
-- -
1 : 19 2

* *********
etpa3
(1 + -4 * 4 - 1 + 8)

etpa3
1:12 0 1-16-1+8 = -16+8 = -8
*/


#include <iostream>
#include <vector>
#include <string>
#include "E:\SINCRO GDRIVE\School\Codigos\CPP\ApenasNumeros\convertCharToNum.cpp"
using namespace std;







class Parentese {
public:
	Parentese(int in = 0, int ou = 0, unsigned int al = -1, string cont = "") : _in(in), _ou(ou), _al(al), conteudo(cont) {}
//_ou - _in SEMPRE DEVE SER MAIOR DO QUE 1
	int _in;
	int _ou;
	unsigned int _al;
	string conteudo;
};

bool validarCaracteres();
bool validarAbreFechaParente();


int math(string &arg) {

	vector<Parentese> Parentesis;
	vector<int> init;

	//Percorre a string procurando pela abertura e fechadura dos parenteses.
	for (int i = 0; i < arg.size(); i++) {
		if (arg[i] == '(') {
			//No caso de encontrar uma abertura, criar um novo indice no vetor, e armazenar a posição dela.
			init.push_back(i);
		}
		else if (arg[i] == ')') {
			if (init.size() <= 0) return -9999999;
			//No caso de encontrar uma fechadura, criar uma instancia do "Parentese" com a abertura mais recente do vetor "init" e o indice "i" como fechadura.
			Parentesis.push_back(Parentese(init[init.size() - 1], i));
			init.resize(init.size() - 1);
		}
	}
	if (init.size() != 0) return -9999999;

	for (Parentese &a : Parentesis) {
		//O conteudo entre a abertura e fachamento dos parenteses.
		a.conteudo = arg.substr(a._in + 1, a._ou - a._in - 1);
		a._al = 0;
		for (Parentese& b : Parentesis) {
			//Descobrir se ha mais parenteses dentro, pra fazer os calculos nos que nao tem primeiro.
			if (b._in > a._in && b._ou < a._ou) a._al++;
		}
		cout << a._in << ":" << a._ou << "\nConteudo: " << a.conteudo << "\nAltitude: " << a._al << "\n-----------------\n";
	}
	cout << "\n\n";

	return init.size();
}



struct Resposta{
	string lPart;
	string rPart;
	string lStrNum;
	string rStrNum;
	int resp;
	
	void clearStrs(){
		lStrNum.clear(); rStrNum.clear(); lpart.clear(); rpart.clear(); lNum = 0; rNum = 0;
	}
	
	bool calc(char op){
		if (op == '*'){
			resp = charToNum(lStrNum) * charToNum(rStrNum);
		}
		else if (op == '/') {
			if (charToNum(rStrNum) == 0) return 0;	//Se divisor for zero, retornar.
			resp = charToNum(lStrNum) / charToNum(rStrNum);
		}
		else if (op == '+'){
			resp = charToNum(lStrNum) + charToNum(rStrNum);
		}
		else if (op == '-'){
			resp = charToNum(lStrNum) - charToNum(rStrNum);
		}
		return 1;	//Calculo realizado com sucesso.
	}
	
	void desvirarStr(){
		//Desvirando o numero esquerdo.
		string temp = lStrNum;
		for (int j = lStrNum.size() - 1, k = 0; j > -1;) {
			lStrNum[j--] = temp[k++];
		}
	}
	
	void remont(string &str){//Remontando a string com a resposta.
		string temp;
		temp += lpart;
		temp += to_string(resp);
		temp += rpart;
		str = temp;
	}
	
	
};

int calcular(string& str) {
	int resp = 0;
	string sLeft, sRight, lpart, rpart;

	int qntsDivMult = 0;
	for (char& ch : str) if (ch == '/' || ch == '*') qntsDivMult++;

	int bkpos = 0;
	for (int i = 0; i < str.size(); i++) {
		sLeft.clear(); sRight.clear(); lpart.clear(); rpart.clear();

		if (qntsDivMult > 0) {
			if (str[i] == '*' || str[i] == '/') {
				qntsDivMult--;
				bkpos = i;
				i--;
				while (i >= 0 && str[i] > 47 && str[i] < 58) {	//Enquanto ele for numero....
					sLeft += str[i];	//Definindo numero a esquerda.
					i--;
				}
				i++;
				lpart = str.substr(0, i);	//Definindo o que sobrou do lado esquerdo.

				i = bkpos + 1;
				while (i < str.size() && str[i] > 47 && str[i] < 58) {	//Enquanto ele for numero....
					sRight += str[i];	//Definindo numero a direita.
					i++;
				}
				rpart = str.substr(i, str.size() - i);	//Definindo o que sobrou do lado direito.

				{	//Desvirando o numero esquerdo.
					string temp = sLeft;
					for (int j = sLeft.size() - 1, k = 0; j > -1;) {
						sLeft[j--] = temp[k++];
					}
				}

				if (str[bkpos] == '*') resp = charToNum(sLeft) * charToNum(sRight);
				else if (str[bkpos] == '/') {
					if (charToNum(sRight) == 0) return -9999999;	//Se divisor for zero, retornar.
					resp = charToNum(sLeft) / charToNum(sRight);
				}

				{	//Remontando a string com a resposta.
					string temp;
					temp += lpart;
					temp += to_string(resp);
					temp += rpart;
					str = temp;
				}
				i = 0;
			}
		}
		else {
			if (str[i] == '+' || str[i] == '-') {

				if (str[bkpos] == '+') resp = charToNum(sLeft) + charToNum(sRight);
				else if (str[bkpos] == '-') resp = charToNum(sLeft) - charToNum(sRight);

				{	//Remontando a string com a resposta.
					string temp;
					temp += lpart;
					temp += to_string(resp);
					temp += rpart;
					str = temp;
				}

				i = 0;
			}

		}
	}

	return resp;
}

int main() {
	//string linha = "(3(2)(444((55)6666)(777)))\n";
	string linha = "5*-5";
	cout << linha;
	cout << "\nParentesis: \n\n";

	return calcular(linha);

}
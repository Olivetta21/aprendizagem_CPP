#include <iostream>
#include <vector>
#include <string>
#include "E:\SINCRO GDRIVE\School\Codigos\CPP\ApenasNumeros\convertCharToNum.cpp"
using namespace std;

bool calcular(string&);
int math(string&);

class Parentese {
public:
	Parentese(int in = 0, int ou = 0, string cont = "") : _in(in), _ou(ou), conteudo(cont) {}
//_ou - _in SEMPRE DEVE SER MAIOR DO QUE 1
	int _in;
	int _ou;
	string conteudo;
};

//bool validarCaracteres();
bool validarAbreFechaParente(string& arg) {
	int aux = 0;
	string removeSpace;
	removeSpace += "(";
	for (const char& ch : arg) {
		if (ch != ' ') removeSpace += ch;
		if (ch == '(') aux++;
		else if (ch == ')') aux--;
		if (aux < 0) return 1;
	}
	if (aux != 0) return 1;
	removeSpace += ")";
	arg = removeSpace;
	return 0;
}


int math(string &arg) {
	if (validarAbreFechaParente(arg)) return 1;



	int numT = 1;
	do {
		cout << "\nCalculo: " << numT++ << "\nCompleta: " << arg ;
		int abertura = -1;
		Parentese a;

		//Percorre a string procurando pela abertura e fechadura dos parenteses.
		for (int i = 0; i < arg.size(); i++) {
			if (arg[i] == '(') {
				//No caso de encontrar uma abertura, defini-la, e ir renovando sempre que uma nova aparecer, ate que se encontre a fechadura.
				abertura = i;
			}
			else if (arg[i] == ')') {
				//No caso de encontrar uma fechadura, criar uma instancia do "Parentese" com a abertura mais recente e o indice "i" como fechadura.
				a = Parentese(abertura, i);
				break;	//Na hora que fecha, estamos pronto para os calculos.
			}
		}
		
		//O conteudo entre a abertura e fechamento dos parenteses.
		a.conteudo = arg.substr(a._in + 1, a._ou - a._in - 1);
		cout << "\n" << a._in << ":" << a._ou << "\nConteudo: " << a.conteudo;

		//Fazer o calculo dos interiores dos parenteses.
		string leftPart = arg.substr(0, a._in);	//Armazenar o que tem antes do abre parenteses.
		string rightPart = arg.substr(a._ou + 1, arg.size() - a._ou - 1);	//Armazenar o que tem depois do fecha parenteses.

		if (calcular(a.conteudo)) { arg = a.conteudo; return 1; }	//Calcular o conteudo.
		cout << "\nConteudo calculado: " << a.conteudo << "\n---------\n";

		//Aqui remontamos a string principal.
		arg.clear();
		arg += leftPart;
		arg += a.conteudo;
		arg += rightPart;

		//Se ainda tiver parenteses, recomece.
	} while (arg.find('(') != string::npos || arg.find(')') != string::npos);

	return 0;
}



class Resposta{
public:
	Resposta() {
		lPart = "";
		rPart = "";
		lStrNum = "";
		rStrNum = "";
		resp = 0;
	}
	string lPart;
	string rPart;
	string lStrNum;
	string rStrNum;
	int resp;
	
	void clearStrs(){
		lStrNum.clear(); rStrNum.clear(); lPart.clear(); rPart.clear();
	}
	
	bool calc(const char &op){
		//No caso de um dos lados nao houver numero, denifi-lo para algum valido, de acordo com o operador.
		if (op == '/' || op == '*') {
			if (rStrNum == "") rStrNum = "1";
			if (lStrNum == "") lStrNum = "0";
		}
		else {
			if (rStrNum == "") rStrNum = "0";
			if (lStrNum == "") lStrNum = "0";
		}

		
		if (op == '*') resp = charToNum(lStrNum) * charToNum(rStrNum);
		else if (op == '/') {
			if (charToNum(rStrNum) == 0) return 1;	//Se divisor for zero, retornar.
			resp = charToNum(lStrNum) / charToNum(rStrNum);
		}
		else if (op == '+') resp = charToNum(lStrNum) + charToNum(rStrNum);
		else if (op == '-') resp = charToNum(lStrNum) - charToNum(rStrNum);
				
		return 0;	//Calculo realizado com sucesso.
	}
	
	void desvirarStr(string &str){
		//Desvirando o numero esquerdo.
		string temp = str;
		for (int j = str.size() - 1, k = 0; j > -1;) {
			str[j--] = temp[k++];
		}
	}
	
	string remont(){//Remontando a string com a resposta.
		string temp;
		temp += lPart;
		temp += to_string(resp);
		temp += rPart;
		return temp;
	}
};

bool calcular(string& str) {
	Resposta R;
	
	int qntsDivMult = 0;
	int opPos = -1;
	
	//Analisar e contar os Multi e Divis.
	for (char& ch : str) if (ch == '/' || ch == '*') qntsDivMult++;

	for (int i = 0; i < str.size(); i++) {
		if (qntsDivMult > 0) {
			//Caso houver multi ou divis entao execute somente esse teste.
			if (str[i] != '*' && str[i] != '/') continue;
			qntsDivMult--;
		}
		else {
			//Quando nao houver multi ou divis, so execute esse teste.
			if (str[i] != '+' && str[i] != '-') continue;
			if (i == 0) continue;	//Se ele for '+' ou '-' mas esta na posicao 0, pule.
		}

		cout << "\nAtual: " << str;
		
		R.clearStrs();	//Reset resposta.
		
		opPos = i;	//Se estamos aqui, eh porque foi encontrado um operador valido, entao guardamos sua posicao.

		i--;
		while (i >= 0 && str[i] > 47 && str[i] < 58) {	//Enquanto ele for numero....
			R.lStrNum += str[i];	//Definindo numero a esquerda.
			i--;
		}
		//Adicionar o sinal do numero, caso existir.
		if (str[i] == '+' || str[i] == '-') {
			if (i > 0) {
				if (str[i - 1] < 48 || str[i - 1] > 57) R.lStrNum += str[i--];
			}
			else R.lStrNum += str[i--];
		}
		
		i++;
		if(i > 0)R.lPart = str.substr(0, i);	//Definindo o que sobrou do lado esquerdo.

		i = opPos + 1;
		if (str[i] == '-' || str[i] == '+') {	//Para os casos de por exemplo 5*-5.
			R.rStrNum += str[i];
			i++;
		}
		while (i < str.size() && str[i] > 47 && str[i] < 58) {	//Enquanto ele for numero....
			R.rStrNum += str[i];	//Definindo numero a direita.
			i++;
		}
		if (i < str.size()) R.rPart = str.substr(i, str.size() - i);	//Definindo o que sobrou do lado direito.

		//Desvirando o numero esquerdo.
		R.desvirarStr(R.lStrNum);

		//Efetuando calculo usando o operador que foi encontrado em str[opPos].
		if (R.calc(str[opPos])) return 1;

		//Remontando a string com os novos valores.
		str = R.remont();
		
		//Sempre voltar no comeco da string apos cada operacao.
		i = 0;

		cout << "\nResp: " << R.resp;
	}
	cout << "\nMandando resposta.......................................";
	return 0;
}


int main() {
	//345+1-(3+334)-((-4-3*45-(3*5)+(3-7))+32/4)+(32+21*(6-3+(4*6+(5-1+(2*2)-4)-76)+7)*4)/2;
	//1+-798*-4

	string linha = "(3 - (4* 8)) * (30 / 6) * -(10-5)";
	cout << linha;
	cout << "\nParentesis: \n\n";
	getline(cin, linha);
	//cin >> linha;
	cout << (math(linha) ? "\nErro: " : "\nResposta: ");
	cout << linha << "\n\n\n";

	return 0;
}
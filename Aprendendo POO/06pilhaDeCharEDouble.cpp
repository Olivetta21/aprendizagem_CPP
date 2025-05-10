#include <iostream>
using namespace std;

template <typename type>

class pilha {
public:
	pilha(int tam) : vet(new type[tam]), tam(tam) {
	}
	~pilha() {
		delete[] vet;
	}

	void mostre(void) {
		cout << endl;
		for (int i = 0; i < topo; i++) {
			cout << "n" << i << ": " << vet[i] << endl;
		}
	}

	void inserir(type info) {
		if (!cheio()) {
			vet[topo] = info;
			max();
			return;
		}
		cout << "!max";
	}

	void remover(void) {
		if (!vazio()) {
			min();
			if ((type)128 == (int)128) vet[topo] = 0;
			else vet[topo] = '@';
			return;
		}
		cout << "!min";
	}

	bool cheio(void) {
		return (topo < tam) ? false : true;
	}
	bool vazio(void) {
		return (topo < 1) ? true : false;
	}

	void max(void) {
		if (!cheio()) {
			topo++;
		}
	}

	void min(void) {
		if (!vazio()) {
			topo--;
		}
	}

private:
	type* vet;
	int tam;
	int topo = 0;
};

int main() {
	pilha<int> _int(10);
	pilha<char> _char(10);

	_int.mostre();
	_char.mostre();
	
	_int.inserir(9);
	_int.inserir(19);
	_char.inserir('I');
	_char.inserir('V');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.inserir(19);
	_char.inserir('I');
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();
	_int.remover();
	_char.remover();

	_int.inserir(19);
	_char.inserir('I'); 


	_int.mostre();
	_char.mostre();
}
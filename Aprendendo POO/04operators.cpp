#include <iostream>
using namespace std;

class MinhaClasse {
public:
    MinhaClasse(int num) {
        this->valor = num;
        this->bala = valor;
    }

    MinhaClasse(int numero, int bola) {
        this->valor = numero;
        this->bala = bola;
    }

    MinhaClasse operator=(const MinhaClasse& outra) {
        this->valor = outra.valor * 100;
        this->bala = outra.bala * 100;
        return *this;
    }

    MinhaClasse operator/(const MinhaClasse& outra) const {
        return MinhaClasse(this->valor / outra.valor, this->bala / outra.bala);
    }
    void operator-(const MinhaClasse& outra) {
        if (this->valor - outra.valor < 0) cout << "::O valor nao pode ser negativo";
        else {
            this->valor -= outra.valor;
            cout << "::sucess";
        }
        if (this->bala - outra.bala < 0) cout << "::A bala nao pode ser negativa";
        else {
            this->bala -= outra.bala;
            cout << "::sucess";
        }
        cout << endl;
    }
    MinhaClasse operator+(const MinhaClasse& outra) const {
        MinhaClasse a (this->valor + outra.valor);
        a.bala *= 2;
        return a;
    }
    MinhaClasse operator*(const MinhaClasse& outra) const {
        return this->valor * outra.valor;
    }
    bool operator==(const MinhaClasse& outra) const {
        return valor == outra.valor && bala == outra.bala;
    }

    int getValor() const {
        return valor;
    }
    int getBala() const {
        return bala;
    }

    void setAllTo(int num) {
        this->bala = num;
        this->valor = num;
    }

    void duplicaVlr() {
        this->valor *= 2;
    }
    void duplicaBala() {
        this->bala *= 2;
    }

private:
    int valor = 0;
    int bala = 0;
};

int main() {
    MinhaClasse obj1(11);
    MinhaClasse obj2(55);
    MinhaClasse objSomado(obj1 + obj2);

    cout << "obj1\tValor: " << obj1.getValor() << "\tBala: " << obj1.getBala() << "\n";
    cout << "obj2\tValor: " << obj2.getValor() << "\tBala: " << obj2.getBala() << "\n\n";

    cout << "Somas ->\tValor: " << objSomado.getValor() << " --x2-> Bala: " << objSomado.getBala() << "\n\n";

    cout << "Duplicando \"Bala obj1\" e \"Valor obj2\"...\n\n";
    obj1.duplicaBala();
    obj2.duplicaVlr();

    cout << "obj1\tValor: " << obj1.getValor() << "\tBala: " << obj1.getBala() << "\n";
    cout << "obj2\tValor: " << obj2.getValor() << "\tBala: " << obj2.getBala() << "\n\n";
    cout << "Somas ->\tValor manual: " << (obj1 + obj2).getValor() << " --x2-> Bala manual: " << (obj1 + obj2).getBala() << "\n\n";

    cout << "Multiplicando \"valor obj1\" com \"valor obj2\": " << (obj1 * obj2).getValor() << "\n\n";

    cout << "Setando obj2 para 11 e duplicando bala\n";
    obj2.setAllTo(11);
    obj2.duplicaBala();
    cout << "Valor: " << obj2.getValor() << "\tBala: " << obj2.getBala() << "\n\n";

    cout << "Removendo o obj1 do obj2:\n";
    obj2 - obj1;
    cout << "Valor: " << obj2.getValor() << "\tBala: " << obj2.getBala() << "\n\n";

    cout << "Objeto por divisao, objSomado / obj1:\n";
    objSomado.duplicaVlr();
    objSomado.duplicaBala();
    MinhaClasse objDiv(objSomado / obj1);
    cout << "Div ->\tValor: " << objDiv.getValor() << " Bala: " << objDiv.getBala() << "\n\n";

    cout << "Criando objeto com operator= no obj1:\n";
    MinhaClasse opera(0);
    opera = obj1;
    cout << "Valor: " << opera.getValor() << "\tBala: " << opera.getBala() << "\n\n";
    cout << "obj1\tValor: " << obj1.getValor() << "\tBala: " << obj1.getBala() << "\n";



    return 0;
}

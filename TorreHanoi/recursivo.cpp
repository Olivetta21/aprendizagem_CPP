#include <iostream>
using namespace std;

void hanoi(int n, char from, char temp, char to) {
    if ( n != 0 ) {

    hanoi(n-1, from, to, temp);
    cout << "Mova disco " << n << " de " << from << " para " << to << endl;
    hanoi(n-1, temp, from, to);
    }
}

int main() {
    int i = 1;

    hanoi(i, 'A', 'B', 'C');

    return 0;
}















Algoritmo TorreDeHanoiRecursivo
DECLARE
procedimento hanoi(n: inteiro, from, temp, to: caractere)
INICIO
    se (n != 0) entao
        hanoi(n-1, from, to, temp);
        Escreva("Mova disco ", n ," de ", from ," para ", to);
        hanoi(n-1, temp, from, to);
    fimse;
fimprocedimento;

INICIO
    hanoi(4, 'A', 'B', 'C');
fimalgoritmo;






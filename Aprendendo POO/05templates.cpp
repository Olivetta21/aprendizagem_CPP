#include <iostream>
using namespace std;

template <typename T>
class Vetor {
private:
    T* elementos;
    int tamanho;

public:
    Vetor(int tamanho) : tamanho(tamanho) {
        elementos = new T[tamanho];
    }

    ~Vetor() {
        delete[] elementos;
    }

    T& operator==(int indice) {
        return elementos[indice];
    }
    T& operator[](int indice) {
        return elementos[indice];
    }

    void toVector(int index, T num) {
        elementos[index] = num;
    }

    void mostre() {
        for (int i = 0; i < this->tamanho; i++) {
            cout << "n" << i << ": " << elementos[i] << endl;
        }
        cout << endl;
    }
};

int main() {
    Vetor<int> intVector(5);
    intVector == 0 = 4; //So para mostrar que isso é possivel.
    intVector[1] = 20;
    intVector == (intVector == 0) = 200;

    intVector.mostre();

    for (int i = 0; i<5; i++){
        intVector.toVector(i, i*10);
    }
    intVector.mostre();
    
    Vetor<double> doubleVector(8);
    doubleVector[0] = 3.14;
    doubleVector[1] = 2.71;
    
    doubleVector.mostre();

    for (int i = 0; i < 8; i++) {
        doubleVector == i = (double)i / 7.0;
    }
    doubleVector.mostre();


    Vetor<char> charVector(3);
    charVector[0] = 'A';
    charVector[1] = 'i';

    charVector.mostre();

    return 0;
}
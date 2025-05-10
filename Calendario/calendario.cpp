#include <iostream>
using namespace std;
int calcD = 0, calcM = 0, calcA = 0;


int validDay(int dia, int mes, int ano){
    calcD++;
    int maxPossible = 0;
    if (mes % 2 == 0){
        if (mes == 2){
            if (ano % 4 == 0) maxPossible = 29;
            else maxPossible = 28;
        }
        else if (mes < 8) maxPossible = 30;
        else maxPossible = 31;
    }
    else{
        if (mes < 8) maxPossible = 31;
        else maxPossible = 30;
    }

    if (dia <= maxPossible) return dia;
    else return maxPossible;
}

int diasDoAno(int ano, int mes, int dia){
    calcM++;
    if (mes > 12) mes = 12;
    if (mes == 1) return validDay(dia, mes, ano);
    else return validDay(dia, mes, ano) + diasDoAno(ano, mes-1, validDay(99, mes-1, ano));
}

//renomear funções por favor que negocio confuso
int anos(int ano, int mes, int dia){
    calcA++;
    if (ano < 1901) return diasDoAno(ano, mes, dia);
    else return diasDoAno(ano, mes, dia) + anos(ano-1, 99, 99);
}

int main(){
    int ano, mes, dia;
    cout <<"Ano mes dia: ";
    cin >> ano >> mes >> dia;

    cout << anos(ano, mes, dia - anos(2022, 12, 31));
    cout << "\nCalculo dia: " << calcD;
    cout << "\nCalculo mes: " << calcM;
    cout << "\nCalculo ano: " << calcA;
    cout << "\nTotal: " << calcA+calcD+calcM;
}

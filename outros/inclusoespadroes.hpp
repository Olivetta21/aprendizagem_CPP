#include <iostream>
#include <iomanip>
#include <chrono>
#define PI 3.141592

using namespace std;
using namespace chrono;

int qntDigts(int x){
	int tam=0;
	while(x>0){
		x/=10;
		tam++;
	}
	return tam;
}

struct pessoa { char nome[10]; int idade; float altura; };
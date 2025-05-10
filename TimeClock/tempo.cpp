//Definicao da classe Tempo.
#include "tempo.h"
#include <iostream>
using std::cout;

Tempo::Tempo(int horas, int minutos) : h(horas), m(minutos) {
	//cout << "horasCriadas:-" << h << ":" << m << "-\n";
}

Tempo::~Tempo() {
	//cout << "horasDeletadas:-" << h << ":" << m << "-\n";
}

ostream& operator<<(ostream& os, const Tempo& t) {
	if (!(t.h > 9)) os << 0;
	os << t.h << ':';
	if (!(t.m > 9)) os << 0;
	os << t.m;
	return os;
}

istream& operator>>(istream& is, Tempo& t){
	int h = 0, m = 0;
	is >> h >> m;
	t = Tempo(h,m) + t;
	return is;
}

Tempo Tempo::operator-(const Tempo& t) {
	int h = 0, m = this->m - t.m;
	while (m < 0) {
		m = 60 + m;
		h++;
	}
	h = this->h - t.h - h;
	while (h < 0) {
		h = 24 + h;
	}
	return {h, m};
}

Tempo Tempo::operator+(const Tempo& t) {
	int h = this->h + t.h, m = this->m + t.m, mToH;
	mToH = m / 60;
	if (mToH) {
		h += mToH;
		m = ((m / 60.0l) - mToH) * 60.1l;
	}
	while (h > 23) h -= 24;
	return { h, m };
}

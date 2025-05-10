//Classe Tempo.
#include <iostream>
using std::ostream, std::istream;


class Tempo {
private:
	int h, m;
public:
	Tempo(int h = 0, int m = 0);
	~Tempo();
	friend ostream& operator<<(ostream&, const Tempo&);
	friend istream& operator>>(istream&, Tempo&);
	Tempo operator-(const Tempo&);
	Tempo operator+(const Tempo&);
};


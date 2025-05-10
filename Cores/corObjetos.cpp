#include <iostream>
using namespace std;

class Cor {
private:
	int R, G, B;
public:
	Cor(int r = 0, int g = 0, int b = 0) : R(r), G(g), B(b) {}
	friend ostream& operator<<(ostream&, const Cor&);
	
};

ostream& operator<<(ostream& os, const Cor& c) {
	if (c.R < 0 || c.G < 0 || c.B < 0) os << "\x1b[0m";
	else os << "\x1b[38;2;" << c.R << ';' << c.G << ';' << c.B << 'm';
	return os;
}

//nt main() {
//	Cor verm(255, 0, 0);
//	cout << verm << "Ivan" << Cor{0, 0, 0} << " luiz" << Cor(0,255,255) << " Pivetta" << Cor(-1,0,0);
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Data {
private:
    time_t rawtime;
    struct tm timeinfo;
    int d, m, y;
    bool dataAtual() {
        // Obter a hora atual
        time(&rawtime);
        // Converter a hora para uma estrutura tm usando localtime_s
        if (localtime_s(&timeinfo, &rawtime) != 0) {
            cout << "\nErro ao obter a data e hora.\n";
            system("pause");
            return 0;
        }
        return 1;
    }
public:
    Data() {
        if (dataAtual()) {
            d = timeinfo.tm_mday;
            m = timeinfo.tm_mon + 1;
            y = timeinfo.tm_year + 1900;
        }
    }
    string _cmp(void){
        if (!dataAtual()) return "00000000";
        return to_string(d) + to_string(m) + to_string(y); 
    }
    int _d(void) { if (dataAtual()) return d; else return 0; }
    int _m(void) { if (dataAtual()) return m; else return 0; }
    int _y(void) { if (dataAtual()) return y; else return 0; }
};



class Barbeiros {
private:
	string nome;
	int cod;
	int qntsCortesMes;
	int totaisCortes;
	float lucroMes;
	float totaisLucros;
public:
	void addCorte() {
		
	}
};
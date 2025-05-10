//#include "G:\Outros computadores\3050\School\Codigos\CPP\Raiz\enesima.cpp"
using namespace std;

int charToNum(string chars = "") {
    if (chars == "") cin >> chars;

    int finalResult = 0, maisPesado = 0;

    for (int i = chars.length(), cont = 0, tempValue = 0; i >= 0; i--) {
        switch (chars[i]) {
        case '0': {
            tempValue = 0;
            break;
        }
        case '1': {
            tempValue = 1;
            break;
        }
        case '2': {
            tempValue = 2;
            break;
        }
        case '3': {
            tempValue = 3;
            break;
        }
        case '4': {
            tempValue = 4;
            break;
        }
        case '5': {
            tempValue = 5;
            break;
        }
        case '6': {
            tempValue = 6;
            break;
        }
        case '7': {
            tempValue = 7;
            break;
        }
        case '8': {
            tempValue = 8;
            break;
        }
        case '9': {
            tempValue = 9;
            break;
        }
        default:
            continue;
        }

        maisPesado = i;
        finalResult += tempValue * pow(10, cont);
        cont++;
    }

    for (int i = 0; i < maisPesado; i++) {
        if (chars[i] == '-') return finalResult * -1;
    }

    return finalResult;
}
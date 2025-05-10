#include <iostream>
#include <string>

using namespace std;

const char XOR_KEY = 0x00;  // Mesma chave usada no programa principal

void encryptPassword(const string& password) {
    cout << "Senha criptografada: {";
    for (size_t i = 0; i < password.size(); i++) {
        cout << "0x" << hex << (int)(password[i] ^ XOR_KEY);
        if (i < password.size() - 1) cout << ", ";
    }
    cout << ", 0x00};" << endl;  // Finalizador
}

int main() {
    string password;
    cout << "Digite a senha para criptografar: ";
    cin >> password;

    encryptPassword(password);
    return 0;
}

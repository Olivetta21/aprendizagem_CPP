#include <windows.h>
#include <iostream>
#include <string>


//Lembre-se de escapar as barras:
#define CAMINHO_PSEXEC "C:\\Program Files\\Sysinternals Suite\\"
//Ponto final significa usuario local
#define DOMINIO "."
#define USUARIO "Administrador"
//precisa estar dentro das chaves
#define SENHA_CRIPTO {0x00}
//caminho completo do programa (escape as barras), ou algum que esteja no PATH
#define CAMINHO_PROGRAMA "C:\\Scripts\\comLog.exe"
//veja o resultado, sem executar nada
#define VER_RESULTADO_COMANDO false


using namespace std;

// Chave para ofuscação
const char XOR_KEY = 0x00;  // Pode ser qualquer valor fixo

// Senha "criptografada" com XOR
const char encrypted_password[] = SENHA_CRIPTO;  // Exemplo

// Função para descriptografar a senha
string decryptPassword(const char* encrypted) {
    string decrypted;
    for (int i = 0; encrypted[i] != 0; i++) {
        decrypted += encrypted[i] ^ XOR_KEY;
    }
    return decrypted;
}

// Função para executar o PsExec
void executePsExec(const string& password) {

    string command = "\"" + string(CAMINHO_PSEXEC) + "PsExec.exe\" -u \"" + string(DOMINIO) + "\\" + string(USUARIO) + "\" -p \"" + string(password) + "\" \"" + string(CAMINHO_PROGRAMA) + "\"";

    if (VER_RESULTADO_COMANDO) {
        std::cout << command << std::endl;
        system("pause");
        return;
    }

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    if (CreateProcess(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        cerr << "Erro ao executar PsExec. Código: " << GetLastError() << endl;
    }
}

int main() {
    string password = decryptPassword(encrypted_password);

    if (!password.empty()) {
        executePsExec(password);
    } else {
        cerr << "Falha ao recuperar senha." << endl;
    }

    return 0;
}

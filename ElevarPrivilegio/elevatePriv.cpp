#include <windows.h>
#include <iostream>
#include <string>


//Lembre-se de escapar as barras:
#define CAMINHO_PSEXEC "C:\\Program Files\\Sysinternals Suite\\"
//Ponto final significa usuario local
#define DOMINIO "."
#define USUARIO "Administrador"
//precisa estar dentro das chaves
#define SENHA_CRIPTO_ADMIN {0x00}
#define SENHA_CRIPTO_USER_FOLDER {0x00}
//caminho completo do programa (escape as barras), ou algum que esteja no PATH
#define CAMINHO_PROGRAMA "cmd"
//veja o resultado, sem executar nada
#define VER_RESULTADO_COMANDO false


using namespace std;
// Caminho do log
const string LOG_PATH = "C:\\Scripts\\InitializeXdrive.log";

// Função para obter a data e hora atual
string getCurrentTime() {
    time_t now = time(0);
    struct tm t;
    localtime_s(&t, &now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &t);
    return string(buffer);
}

// Função para adicionar mensagens ao log
void logMessage(const string& message) {
    ofstream logFile(LOG_PATH, ios::app);
    if (logFile.is_open()) {
        logFile << "│" << getCurrentTime() << "    " << message << "│" << endl;
        logFile.close();
    }
}


// Chave para ofusca��o
const char XOR_KEY = 0x00;  // Pode ser qualquer valor fixo
// Senha "criptografada" com XOR
const char encrypted_password[] = SENHA_CRIPTO_ADMIN;
const char encrypted_password_user_folder[] = SENHA_CRIPTO_USER_FOLDER;



// Funcao para descriptografar a senha
string decryptPassword(const char* encrypted) {
    string decrypted;
    for (int i = 0; encrypted[i] != 0; i++) {
        decrypted += encrypted[i] ^ XOR_KEY;
    }
    return decrypted;
}



// Funcao para executar o PsExec
void executeCommand(const string& command) {
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
        cerr << "Erro ao executar comando. Codigo: " << GetLastError() << endl;
    }
}


int main( int argc, char *argv[] ) {
    string del_ou_add = "";
    if (argc > 1) {
        del_ou_add = argv[1];
    } else {
        cerr << "Argumento faltando. Use 'del' ou 'add'." << endl;
        return 3;
    }

    string password = decryptPassword(encrypted_password);
    string password_user_folder = decryptPassword(encrypted_password_user_folder);
    string command = "\"" + string(CAMINHO_PSEXEC) + "PsExec.exe\" -u \"" + string(DOMINIO) + "\\" + string(USUARIO) + "\" -p \"" + password + "\" \"" + string(CAMINHO_PROGRAMA) + "\" /c \"C:\\Program Files\\Sysinternals Suite\\PsExec.exe\" -i -s net use Z: ";

    if (del_ou_add == "del") {
        command += "/delete /y";
    }
    else if (del_ou_add == "add") {
        command += "\\\\10.8.0.1\\compartilhamento /user:? " + password_user_folder;
    }
    else {
        cerr << "Argumento invalido. Use 'del' ou 'add'." << endl;
        return 1;
    }


    if (!password.empty()) {
        executeCommand(command);
    } else {
        cerr << "Falha ao recuperar senha." << endl;
        return 2;
    }

    return 0;
}

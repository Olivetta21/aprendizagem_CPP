#include <windows.h>
#include <iostream>
#include <fstream>
#include <ctime>

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

// Função para executar um comando do sistema
void executeCommand(const string& command) {
    system(command.c_str());
}

int main() {
    logMessage("entrando");

    // Verifica se a unidade Z: existe
    if (GetDriveTypeA("Z:\\") != DRIVE_NO_ROOT_DIR) {
        executeCommand("C:\\Scripts\\Xdrive.exe del");
        logMessage("deletado");
        Sleep(2000); // Espera 2 segundos (equivalente ao timeout /t 2)
    }

    // Adiciona o drive novamente
    executeCommand("C:\\Scripts\\Xdrive.exe add");
    logMessage("mapeado");

    logMessage("saindo");

    return 0;
}

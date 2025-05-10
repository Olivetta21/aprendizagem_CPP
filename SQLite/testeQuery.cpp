#include <iostream>
#include "E:/SINCRO GDRIVE/School/Codigos/CPP/SQLite/sqlite3.h"
#include "E:/SINCRO GDRIVE/School/Codigos/CPP/SQLite/sqlite3.lib"

int main() {
    sqlite3* db;
    char* errMsg = 0;

    // Abre ou cria o banco de dados
    int rc = sqlite3_open("E:/SINCRO GDRIVE/School/Codigos/CPP/SQLite/exemplo.db", &db);

    if (rc) {
        std::cerr << "Erro ao abrir ou criar o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Cria uma tabela
    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS exemplo_table (id INT, nome TEXT);";
    rc = sqlite3_exec(db, createTableQuery, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }

    // Insere dados na tabela
    const char* insertDataQuery = "INSERT INTO exemplo_table (id, nome) VALUES (1, 'Exemplo1'), (2, 'Exemplo2');";
    rc = sqlite3_exec(db, insertDataQuery, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao inserir dados na tabela: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }

    // Consulta dados na tabela
    const char* selectDataQuery = "SELECT * FROM exemplo_table;";
    rc = sqlite3_exec(db, selectDataQuery, [](void* data, int argc, char** argv, char** /*columnName*/) -> int {
        for (int i = 0; i < argc; ++i) {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
        return 0;
        }, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao consultar dados na tabela: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }

    // Fecha o banco de dados
    //sqlite3_close(db);
    //
    //return 0;
}

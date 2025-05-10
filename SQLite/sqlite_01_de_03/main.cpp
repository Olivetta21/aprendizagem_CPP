#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

int sqlite3_retorno(void *NotUsed, int argc, char **argv, char **coluna)
{
    for( int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", coluna[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}



int criarTabela(sqlite3& banco, char* &msgErr) {
    string temp;
    string comand;
    cout << "Nome da tabela: ";
    getline(cin, temp);


    comand += "CREATE TABLE ";
    comand += temp;

    cout << "Infos: ";
    getline(cin, temp);

    comand += "(";
    comand += temp;
    comand += ")";


  // criando uma tabela dentro do arquivo
  int rc = sqlite3_exec( &banco, comand.c_str(), sqlite3_retorno, 0, &msgErr );

  if ( rc != SQLITE_OK )
  {
      cout << "ERRO ao criar tabela: " << sqlite3_errmsg(&banco) << "\n";
      sqlite3_close(&banco);
      return 1;
  }

  cout << "Tabela criada.\n";
  return 0;
}

void inserirNaTabela(sqlite3& banco, char*& msgErr) {

}
void atualizarTabela() {

}
void verTabela() {

}
int deletarTabela(sqlite3& banco, char*& msgErr) {
    string nomeTab;
    cout << "Nome da tabela: ";
    getline(cin, nomeTab);

    string temp = "DROP TABLE IF EXISTS ";
    temp += nomeTab;

    int rc = sqlite3_exec(&banco, temp.c_str(), sqlite3_retorno, 0, &msgErr);

    if (rc != SQLITE_OK)
    {
        cout << "ERRO ao deletar tabela: " << sqlite3_errmsg(&banco) << "\n";
        sqlite3_close(&banco);
        return 1;
    }

    cout << "Tabela deletada.\n";
    return 0;
}





int main()
{
    sqlite3 * db = 0;
    char * mensagem_erro = 0;

    printf("versao: %s\n", sqlite3_libversion());

    int rc = sqlite3_open( "E:/SINCRO GDRIVE/School/Codigos/CPP/SQLite/database.db3", &db );

    if ( rc != SQLITE_OK )
    {
        printf( "ERRO ao abrir: %s\n", sqlite3_errmsg( db ) );
        sqlite3_close( db );
        return 1;
    }

    //deletarTabela(*db, mensagem_erro);
    //criarTabela(*db, mensagem_erro);

    return 1;

 //  // criando uma tabela dentro do arquivo
 //  char create[] = "CREATE TABLE certificados( "
 //                  "cod INTEGER PRIMARY KEY, "
 //                  "nome TEXT,"
 //                  "local TEXT )";
 //
 //  rc = sqlite3_exec( db, create, sqlite3_retorno, 0, &mensagem_erro );
 //
 //  if ( rc != SQLITE_OK )
 //  {
 //      printf( "ERRO ao criar tabela: %s\n", sqlite3_errmsg( db ) );
 //      sqlite3_close( db );
 //      return 1;
 //  }
 //
 //  printf( "Tabela criada.\n" );



 //  // incluir dados na tabela
 //  char insert[] = "insert into certificados(cod,nome,local) "
 //                  "values( 1, 'ivan', 'pag18') ";
 //
 //  rc = sqlite3_exec( db, insert, sqlite3_retorno, 0, &mensagem_erro );
 //
 //  if ( rc != SQLITE_OK )
 //  {
 //      printf( "ERRO no insert tabela: %s\n", sqlite3_errmsg( db ) );
 //      sqlite3_close( db );
 //      return 1;
 //  }
 //
 //  printf( "Insert da tabela executada.\n" );



    // obter um registro
    //char query[] = "select * from funcionario where id=1";
    char query[] = "select * from funcionario"; // todos os registros


    rc = sqlite3_exec( db, query, sqlite3_retorno, 0, &mensagem_erro );

    if ( rc != SQLITE_OK )
    {
        printf( "ERRO ao consultar funcionario: %s\n", sqlite3_errmsg( db ) );
        sqlite3_close( db );
        return 1;
    }

    printf( "Consulta executada com sucesso.\n" );



//    // atualizar registro
//    char update[] = "update funcionario set nome='qualquer nome', "
//                                          "nascimento='99/99/99' "
//                                          "where id=1";
////    char update[] = "select * from funcionario"; // todos os registros
//
//
//    rc = sqlite3_exec( db, update, sqlite3_retorno, 0, &mensagem_erro );
//
//    if ( rc != SQLITE_OK )
//    {
//        printf( "ERRO ao atualizar funcionario: %s\n", sqlite3_errmsg( db ) );
//        sqlite3_close( db );
//        return 1;
//    }
//
//    printf( "Atualizacao executada com sucesso.\n" );

 //   // consultar se atualizacao teve efeito
 //   char query[] = "select * from funcionario where id=2";
 //
 //   rc = sqlite3_exec( db, query, sqlite3_retorno, 0, &mensagem_erro );
 //
 //   if ( rc != SQLITE_OK )
 //   {
 //       printf( "ERRO ao consultar funcionario: %s\n", sqlite3_errmsg( db ) );
 //       sqlite3_close( db );
 //       return 1;
 //   }
 //
 //   printf( "Consulta executada com sucesso.\n" );


    // DROP TABLE IF EXISTS funcionario

    sqlite3_free( mensagem_erro );
    sqlite3_close(db);

    return 0;
}


/** documentacao sqlite
 *  https://www.sqlite.org/index.html
 */

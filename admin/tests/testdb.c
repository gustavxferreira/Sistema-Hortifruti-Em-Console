#include <stdio.h>
#include <stdlib.h>
#include "../headers/sqlite3.h"

int callback_test(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int testConnection()
{
   sqlite3 * db = 0;


   int rc = sqlite3_open("db.db3", &db);

   if(rc != SQLITE_OK) {
    printf("ERRO ao abrir abrir");
    return 1;
   }

   printf("Banco de Dados SQLite Versao %s\n", sqlite3_libversion());
   const char *sql = "SELECT 1 as ConnectionOk FROM users LIMIT 1;";
   char *zErrMsg = 0;
   rc = sqlite3_exec(db, sql, callback_test, 0, &zErrMsg);


   sqlite3_free(zErrMsg);
   sqlite3_close(db);

   return 0;
}

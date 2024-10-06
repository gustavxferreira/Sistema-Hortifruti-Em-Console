#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/login.h"
#include "../headers/sqlite3.h"

int callback(void *data, int argc, char **argv, char **azColName) {
    UserData *user = (UserData *)data;

    if (argc >= 3) {
        strncpy(user->username, argv[0] ? argv[0] : "NULL", sizeof(user->username) - 1);
        user->username[sizeof(user->username) - 1] = '\0';
        strncpy(user->password, argv[1] ? argv[1] : "NULL", sizeof(user->password) - 1);
        user->password[sizeof(user->password) - 1] = '\0';
        user->isAdmin = argv[2] ? atoi(argv[2]) : 0;
    }

    return 0;
}

int login() {
    sqlite3 *db = 0;
    int rc = sqlite3_open("db.db3", &db);

    if (rc != SQLITE_OK) {
        printf("ERRO ao abrir o banco de dados\n");
        return 1;
    }

    printf("Banco de Dados SQLite Versão %s\n", sqlite3_libversion());

    const char *sql = "SELECT username, password, isAdmin FROM users LIMIT 1;";
    char *zErrMsg = 0;
    UserData user = {"", "", 0};

    rc = sqlite3_exec(db, sql, callback, &user, &zErrMsg);

    if (rc != SQLITE_OK) {
        printf("ERRO na consulta: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Username: %s\n", user.username);
        printf("Password: %s\n", user.password);
        printf("isAdmin: %d\n", user.isAdmin);
    }

    sqlite3_close(db);
    return 0;
}

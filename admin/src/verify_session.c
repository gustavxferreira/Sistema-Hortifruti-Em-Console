#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/verify_session.h"
#include "../headers/sqlite3.h"

int userCallback(void *data, int argc, char **argv, char **azColName) {
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

    char typed_username[50];
    char typed_password[50];

    clear();
    printw("Insira seu usuário: ");
    getnstr(typed_username, sizeof(typed_username) - 1);

    printw("\nInsira sua senha: ");

    getnstr(typed_password, sizeof(typed_password) - 1);
    echo();

    sqlite3 *db = 0;
    int rc = sqlite3_open("db.db3", &db);

    if (rc != SQLITE_OK) {
        printf("ERRO ao abrir o banco de dados\n");
        return 0;
    }

    char sql[200];
snprintf(sql, sizeof(sql), "SELECT username, password, isAdmin FROM users WHERE username = '%s' AND password = '%s';",
         typed_username, typed_password);
    char *zErrMsg = 0;
    UserData user = {"", "", 0};

    rc = sqlite3_exec(db, sql, userCallback, &user, &zErrMsg);

    if (rc != SQLITE_OK) {
        printf("ERRO na consulta: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
         sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }

     if (strcmp(typed_username, user.username) != 0 || strcmp(typed_password, user.password) != 0 || user.isAdmin == 0) {
        printw("\nAcesso negado\n");
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        refresh();
        return 0;
    }

    sqlite3_close(db);
    printw("\nBem vindo!\n");
    refresh();
    return 1;
}

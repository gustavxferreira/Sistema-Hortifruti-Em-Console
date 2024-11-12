#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "../headers/verify_session.h"
#include "../headers/administrator/administrator_display.h"
#include "../headers/common_user/common_user_display.h"
#include <locale.h>
#include "../headers/sqlite3.h"

enum sessionStatus {
    LOGGED_IN = 1,
    NOT_LOGGED_IN = 0
};

enum UserType {
    ADMIN_USER = 1,
    COMMON_USER = 2
};

int main() {

    initscr();
    cbreak();
    curs_set(0);

    int* permissionAndSession = NULL;

        while (permissionAndSession == NULL || permissionAndSession[0] == NOT_LOGGED_IN) {
        permissionAndSession = login();

        printw("Carregando...");

        refresh();
        napms(1000);
    }

    switch(permissionAndSession[1]) {
    case ADMIN_USER: administrator_display();  break;
    case COMMON_USER: common_user_display(); break;
    }

    endwin();
    return 0;
}

#include <curses.h>
#include "../../headers/product/product_display_common_user.h"
#include <curses.h>
#include <string.h>

void common_user_display() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(0, 1, "Bem-vindo ao Sistema de Hortifruti");
    attroff(COLOR_PAIR(2) | A_BOLD);
    mvprintw(1, 1, "");

    mvprintw(2, 1, "1. Produtos");
    mvprintw(3, 1, "2. Sair");

    refresh();
    char option = getch();

    switch(option) {

    case '1': product_display_common_user();
        break;
    case '2': endwin(); return 0;
        break;
        default:
        clear();
        mvprintw(1, 1, "Insira uma opcao valida");
        refresh();
        napms(100);
        administrator_display();
        break;
    }
}

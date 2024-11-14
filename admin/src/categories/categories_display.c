#include <curses.h>
#include "../../headers/administrator/administrator_display.h"
void categories_display() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();

    mvprintw(1, 1, "Lista de categorias");
    mvprintw(3, 1, "Frutas pereciveis");
    mvprintw(4, 1, "Frutas citricas");
    mvprintw(5, 1, "Frutas tropicais");
    mvprintw(6, 1, "Frutas de caroço");
    mvprintw(8, 1, "1. Voltar");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();
    char option = getch();

     switch(option) {
    case '1':
        administrator_display();
        break;
    default:
        clear();
        mvprintw(1, 1, "Insira uma opcao valida");
        refresh();
        napms(100);
        categories_display();
        break;
    }
}

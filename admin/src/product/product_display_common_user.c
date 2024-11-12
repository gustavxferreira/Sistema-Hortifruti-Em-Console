#include <curses.h>
#include "../../headers/product/fetch_product.h"
#include "../../headers/common_user/common_user_display.h"

void product_display_common_user() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(0, 1, "+-----------------+");
    mvprintw(1, 1, "|     PRODUTOS    |");
    mvprintw(2, 1, "+-----------------+");
    mvprintw(3, 1, "1. Listar Produtos");
    mvprintw(4, 1, "2. Voltar");
    attroff(COLOR_PAIR(1) | A_BOLD);
    char option = getch();
    clear();
    refresh();
    switch(option) {
    case '1':
        fetch_product(0);
        break;
         case '2':

        common_user_display();
        break;
    default:
        clear();
        mvprintw(1, 1, "Insira uma opcao valida");
        refresh();
        napms(100);
        product_display_common_user();
        break;
    }
}

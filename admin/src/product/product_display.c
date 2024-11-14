#include <curses.h>
#include "../../headers/administrator/administrator_display.h"
#include "../../headers/product/fetch_product.h"
#include "../../headers/product/create_product.h"
#include "../../headers/product/delete_product.h"
#include "../../headers/product/update_product.h"

void product_display() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(0, 1, "+-----------------+");
    mvprintw(1, 1, "|     PRODUTOS    |");
    mvprintw(2, 1, "+-----------------+");
    mvprintw(3, 1, "1. Listar Produtos");
    mvprintw(4, 1, "2. Cadastrar Produtos");
    mvprintw(5, 1, "3. Atualizar Produtos");
    mvprintw(6, 1, "4. Excluir Produtos");
    mvprintw(7, 1, "5. Voltar");
    attroff(COLOR_PAIR(1) | A_BOLD);
    char option = getch();
    clear();
    refresh();
    switch(option) {
    case '1':
        fetch_product();
        break;
    case '2':
        create_product();
        break;
        case '3':
            update_product();
        break;
    case '4':

        delete_product();
        break;
         case '5':

        administrator_display();
        break;
    default:
        clear();
        mvprintw(1, 1, "Insira uma opcao valida");
        refresh();
        napms(100);
        product_display();
        break;
    }
}

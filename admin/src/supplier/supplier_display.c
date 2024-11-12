#include <curses.h>
#include "../../headers/administrator/administrator_display.h"
void supplier_display() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();

    mvprintw(4, 1, "1. Listar Fornecedores");
    mvprintw(5, 1, "2. Criar Fornecedores");
    mvprintw(6, 1, "3. Atualizar Fornecedores");
    mvprintw(7, 1, "3. Excluir Fornecedores");
    mvprintw(8, 1, "4. Voltar");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();
    char option = getch();

    switch(option) {
    case '1':
        product_display();
        break;
    case '2':
        supplier_display();
        break;
        case '3':
            categories_display();
        break;
    case '4':
        administrator_display();
        break;
    }
}

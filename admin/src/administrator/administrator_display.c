#include <curses.h>
#include "../../headers/product/product_display.h"
#include "../../headers/supplier/supplier_display.h"
#include "../../headers/categories/categories_display.h"
#include "../../headers/more_information/more_information_display.h"
#include <curses.h>
#include <string.h>

void administrator_display() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(0, 1, "Bem-vindo ao Sistema de Hortifruti");
    attroff(COLOR_PAIR(2) | A_BOLD);
    mvprintw(1, 1, "");

    mvprintw(2, 1, "1. Produtos");
    mvprintw(3, 1, "2. Fornecedores");
    mvprintw(4, 1, "3. Categorias");
    mvprintw(5, 1, "4. Informacoes");
    mvprintw(6, 1, "5. Sair");

    refresh();
    char option = getch();

    switch(option) {

    case '1': product_display();
        break;
    case '2': supplier_display();
        break;
    case '3': categories_display();
        break;
    case '4': more_information_display(); return 0;
    case '5': endwin(); return 0;
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

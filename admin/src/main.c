#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "../headers/verify_session.h"

void administrator_display() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    clear();
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(1, 1, "Bem-vindo ao Sistema de Hortifruti Usuario - Var");
    mvprintw(2, 1, "");
    mvprintw(3, 1, "Por favor, escolha uma opcao:");

    mvprintw(4, 1, "1. Produtos");
    mvprintw(5, 1, "2. Fornecedores");
    mvprintw(6, 1, "3. Categorias");
    mvprintw(7, 1, "4. Sair");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();
    getch();
}

int main() {
    initscr();

    // se for 0 o usuario ainda não está logado
    int verify_session = 0;

     while (verify_session == 0) {
        verify_session = login();
        printw("Carregando...");
        refresh();
        napms(1000);
    }

    napms(1000);

    administrator_display();

    endwin();
    return 0;
}

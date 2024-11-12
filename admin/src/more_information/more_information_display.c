#include <curses.h>
#include <string.h>
#include "../../headers/administrator/administrator_display.h"

void more_information_display() {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    clear();
    resize_term(50, 100);
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(0, 1, "+----------------------------------------------+");
    mvprintw(1, 1, "|                 INFORMACOES                  |");
    mvprintw(2, 1, "+----------------------------------------------+");
    attroff(COLOR_PAIR(2) | A_BOLD);

    cbreak();
    noecho();
    curs_set(0);
    WINDOW *win = newwin(LINES, COLS, 0, 0);
    scrollok(win, TRUE);
    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(3, 1, "Qual e a melhor forma de cadastrar os meus produtos?");
    attroff(A_BOLD | COLOR_PAIR(2));
    mvprintw(4, 1, "\n");

    attron(A_BOLD);
    mvprintw(5, 1, "Frutas pereciveis - 2 a 10 Dias:");
    attroff(A_BOLD);
    mvprintw(6, 1, "Algumas frutas pereciveis, como morangos, framboesas, amoras, uvas, pessegos, ");
    mvprintw(7, 1, "abacaxis, mangas, kiwis, bananas, macas, peras, cerejas, melancias, meloes, ");
    mvprintw(8, 1, "mamoes e figos, tendem a estragar mais rapidamente. Seu prazo de validade pode ");
    mvprintw(9, 1, "ser curto, geralmente de 2 a 10 dias quando armazenadas adequadamente na geladeira.");
    mvprintw(10, 1, "\n");

    attron(A_BOLD);
    mvprintw(11, 1, "Frutas citricas - 7 a 14 Dias:");
    attroff(A_BOLD);
    mvprintw(12, 1, "Frutas citricas, como laranjas, limoes e grapefruits, podem durar mais tempo em ");
    mvprintw(13, 1, "comparação com frutas perecveis. Elas podem ser armazenadas por ate 1-2 semanas ");
    mvprintw(14, 1, "na geladeira, dependendo do grau de maturacao e das condicoes de armazenamento.");
    mvprintw(15, 1, "\n");

    attron(A_BOLD);
    mvprintw(16, 1, "Frutas tropicais - 2 a 6 Dias:");
    attroff(A_BOLD);
    mvprintw(17, 1, "Frutas tropicais, como bananas, abacaxis, mangas, cocos, mamoes, kiwis, maracujas ");
    mvprintw(18, 1, "e guavas, podem durar varios dias a uma semana em temperatura ambiente, dependendo ");
    mvprintw(19, 1, "do grau de maturação. No entanto, e importante monitorar sua condicao de perto, pois ");
    mvprintw(20, 1, "elas podem amadurecer rapidamente e ficar excessivamente maduras.");
    mvprintw(21, 1, "\n");

    attron(A_BOLD);
    mvprintw(22, 1, "Frutas de caroço - 3 a 5 Dias:");
    attroff(A_BOLD);
    mvprintw(23, 1, "Frutas de caroco, como pessegos, ameixas e nectarinas, geralmente tem um prazo de ");
    mvprintw(24, 1, "validade de 3-5 dias na geladeira, mas tambem podem ser armazenadas em temperatura ");
    mvprintw(25, 1, "ambiente por alguns dias.");
    mvprintw(26, 1, "\n");

    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(27, 1, "Porque a importancia de saber disso?");
    attroff(A_BOLD | COLOR_PAIR(2));
    mvprintw(28, 1, "\n");

    mvprintw(29, 1, "Na hora de realizar o cadastro de seus produtos, escolher a categoria ");
    mvprintw(30, 1, "ira te ajudar, pois o sistema ira determinar uma data limite para a fruta.");


    mvprintw(32, 1, "1. Voltar");
    refresh();
    char option = getch();

    switch(option) {
        case '1': administrator_display();

        break;
        default:
        clear();
        mvprintw(1, 1, "Insira uma opcao valida");
        refresh();
        napms(100);
        more_information_display();
        break;
    }
}

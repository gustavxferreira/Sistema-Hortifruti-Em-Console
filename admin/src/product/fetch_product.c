#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/sqlite3.h"
#include <curses.h>
#include "../../headers/product/product_display.h"
#include "../../headers/product/product_display_common_user.h"

int callBackFetchProduct(void *arg, int argc, char **argv, char **column)
{
    static int headerPrinted = 0;
    headerPrinted = 0;
    int counter = 0;
    int initialSize = 10;
    static int rowCount = 0;

    if (!headerPrinted) {
        mvprintw(0, 1, "+------+------------------------+---------+-------+");
        mvprintw(1, 1, "| ID   | Nome                   | Preco   |  Qtd  |");
        mvprintw(2, 1, "+------+------------------------+---------+-------+");
        headerPrinted = 1;
    }

    if (argc >= 4) {
        mvprintw(3 + rowCount, 1, "| %-4.4s | %-22.22s | %-7.7s | %-5.5s |",
                 argv[0] ? argv[0] : "NULL",
                 argv[1] ? argv[1] : "NULL",
                 argv[2] ? argv[2] : "NULL",
                 argv[3] ? argv[3] : "NULL");
        rowCount++;
    }

    if (rowCount >= 15) {
        mvprintw(4 + rowCount, 1, "+----+------------------------+--------+-----------+");
        refresh();
        printw("\n Pressione qualquer tela ir a proxima pagina");
        getch();
        clear();
        rowCount = 0;
        headerPrinted = 0;
    }
    refresh();
}

int fetch_product(int adm) {

    sqlite3 *db = 0;
    char *zErrMsg = 0;

    int rc = sqlite3_open("db.db3", &db);

    if (rc != SQLITE_OK) {
        printf("ERRO ao abrir o banco de dados\n");
        return 0;
    }

    char fetch[] = "select * from product";

    clear();
    refresh();
    rc = sqlite3_exec(db, fetch, callBackFetchProduct, 0, &zErrMsg);
    printw("\n");
    printw("\nFim da listagem\n");
    printw("\n");
    printw("Pressione qualquer tecla para redirecionar ao inicio");
    printw("\n");
    refresh();
    noecho();
    getch();
    printw("Redirecionando...");
    refresh();
    napms(1000);
    sqlite3_close(db);
    if(adm == 0) {
        product_display_common_user();
    }
    product_display();

}

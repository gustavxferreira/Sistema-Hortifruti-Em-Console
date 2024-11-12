#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/sqlite3.h"
#include <curses.h>
#include "../../headers/product/product_display.h"

int delete_product() {
    char product_id_string[11];
    int product_id;

    char product_name[50];
    char unit_type[11];
    char category[20];
    double price;
    int product_quantity;
    int product_found = 0;
    int callBackGetProductForBeDeleted(void *arg, int argc, char **argv, char **column) {

        if (argc >= 5) {

            strcpy(product_name, argv[1]);
            price = atof(argv[2]);
            strcpy(unit_type, argv[3]);
            product_quantity = atoi(argv[4]);
            strcpy(category, argv[5]);
            product_found++;
            return 0;
        }
    }

    void validationRedirection(const char *message) {
        clear();
        printw("Insira campos validos!\n%s", message);
        refresh();
        napms(2500);
        delete_product();
    }

    clear();
    echo();
    mvprintw(0, 1, "+------+------------+");
    mvprintw(1, 1, "|  Deletar Produto  |");
    mvprintw(2, 1, "+------+------------+");
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\n Insira Q Para Cancelar");
    attroff(COLOR_PAIR(1) | A_BOLD);

    printw("\n");
    printw("\n Insira o codigo (id) do produto: ");
    getnstr(product_id_string, sizeof(product_id_string) - 1);

    if (strcmp(product_id_string, "Q") == 0 || strcmp(product_id_string, "q") == 0) {
        product_display();
        return 0;
    }
    product_id = strtol(product_id_string, NULL, 10);

    if (product_id <= 0) {
        validationRedirection(" O valor nao pode ser menor ou igual a 0 ou diferente de um numero");
        return 0;
    }

    sqlite3 *db = 0;
    char *zErrMsg = 0;
    int rc = sqlite3_open("db.db3", &db);
    if (rc != SQLITE_OK) {
        printw("ERRO ao abrir o banco de dados\n");
        refresh();
        getch();
        return 0;
    }

    char sql[100];
    sprintf(sql, "SELECT * FROM product WHERE id = %d", product_id);
    rc = sqlite3_exec(db, sql, callBackGetProductForBeDeleted, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        printw("Erro ao executar o SELECT: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        refresh();
        getch();
        sqlite3_close(db);
        return 0;
    }

    if(!product_found) {
        printw("\n");
        printw(" ID nao encontrado no sistema!\n Redirecionando...");
        refresh();
        napms(1000);
        sqlite3_close(db);
        product_display();
        return 0;
    }
    clear();
    mvprintw(0, 1, "+------+------------------------+---------+-------+");
    mvprintw(1, 1, "| ID   | Nome                   | Preco   |  Qtd  |");
    mvprintw(2, 1, "+------+------------------------+---------+-------+");

    mvprintw(3, 1, "| %-4d | %-22s | %.-2f  | %-5d |",
         product_id,
         product_name,
         price,
         product_quantity
    );
    mvprintw(4, 1, "+------+------------------------+---------+-------+");
    noecho();
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\n\n Y - Confirmar Exclusao do Produto");
    attroff(COLOR_PAIR(1) | A_BOLD);
      attron(COLOR_PAIR(2) | A_BOLD);
    printw("\n Qualquer Tecla - Cancelar Exclusao do Produto");
    attroff(COLOR_PAIR(2) | A_BOLD);
    char userChoose = getch();

    if (userChoose == 'Y' || userChoose == 'y') {
        sprintf(sql, "DELETE FROM product WHERE id = %d", product_id);
        rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

        attron(COLOR_PAIR(3) | A_BOLD);
        clear();
        printw("\n Produto deletado com sucesso!");
        refresh();
        attroff(COLOR_PAIR(3) | A_BOLD);
    }else {
        clear();
        printw(" ACAO CANCELADA!");
        refresh();
    }
    printw("\n Redirecionando...");
    refresh();
    napms(1000);
    sqlite3_close(db);
    product_display();
    return 0;
}

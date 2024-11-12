#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/sqlite3.h"
#include <curses.h>
#include "../../headers/product/product_display.h"

int create_product() {
    int callBack(void *arg, int argc, char **argv, char **column)
    {}

    void validationRedirection(char *message) {
        clear();
        printw("Insira campos validos!");
        printw("\n%s", message);
        refresh();
        napms(2500);
        create_product();
    }

    char product_name[50];
    char unit_type[11];

    char category_string[20] = "";

    float price;
    char price_string[11];

    int product_quantity;
    char quantity_string[11];
    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    clear();
    echo();
    mvprintw(0, 1, "+------+------------+");
    mvprintw(1, 1, "| Cadastrar Produto |");
    mvprintw(2, 1, "+------+------------+");
    printw("\n");
    printw(" Insira nome do produto: ");
    getnstr(product_name, sizeof(product_name) - 1);

    if(strlen(product_name) < 4 || strlen(product_name) >= 49) {
    char message[] = "O campo precisa ter entre 4 a 49 caracteres";
    validationRedirection(message);
    }
    printw("\n Insira a categoria: ");
    printw("\n 1. Frutas pereciveis");
    printw("\n 2. Frutas citricas");
    printw("\n 3. Frutas tropicais");
    printw("\n 4. Frutas de caroco");
    noecho();
    char category_id_string = getch();
    switch(category_id_string) {
        case '1':
            strcpy(category_string, "Frutas pereciveis"); break;
        case '2':
            strcpy(category_string, "Frutas citricas"); break;
        case '3':
            strcpy(category_string, "Frutas tropicais"); break;
        case '4': strcpy(category_string, "Frutas de caroco"); break;
    }

     if(strlen(category_string) == NULL || strlen(category_string) <= 0) {
    char message[] = " Escolha um valor valido!";
    validationRedirection(message);
    }

    int category_id = category_id_string - '0';
    printw("\n");
    echo();
    printw("\n Insira o preco: ");
    getnstr(price_string, sizeof(price_string) - 1);
    // colocar . no lugar da vírgula
    for (int i = 0; i < strlen(price_string); i++) {
    if (price_string[i] == ',') {
        price_string[i] = '.';
    }
    }
    price = strtof(price_string, NULL);

    if(price == 0) {
    char message[] = " O valor nao pode ser menor ou igual a 0 ou diferente de um numero";
    validationRedirection(message);
    }

    printw("\n Insira o tipo de quantidade a ser armazenada: ");
    printw("\n 1. Unidade ");
    printw("\n 2. Caixa");
    printw("\n 3. KG ");
    noecho();
    char userChoose = getch();

    switch(userChoose) {
        case '1':
            strcpy(unit_type, "Unidade");
    break;
        case '2':
            strcpy(unit_type, "Caixa");
    break;
        case '3':
            strcpy(unit_type, "KG");
        default:
    validationRedirection("Insira uma opcao valida"); break;
    break;
    }

    if(strlen(unit_type) == NULL || strlen(unit_type) <= 0) {
    char message[] = " Escolha um valor valido!";
    validationRedirection(message);
    }
    printw("\n");
    echo();
    printw("\n Insira a quantidade de %s: ", unit_type);

    getnstr(quantity_string, sizeof(quantity_string) - 1);
    product_quantity = strtol(quantity_string, NULL, 10);

    if(product_quantity <= 0) {
    char message[] = " O valor nao pode ser menor ou igual a 0 ou diferente de um numero";
    validationRedirection(message);
    }

    clear();

    printw("\n Dados do produtos a ser inserido");

    mvprintw(1, 1, "+-----------------+------------+----------+------------------------+");
    mvprintw(2, 1, "| Nome            | Preco      |  Qtd     | Categoria              |");
    mvprintw(3, 1, "+-----------------+------------+----------+------------------------+");

    mvprintw(4, 1, "| %-15.15s | %-10.2f | %-8d | %-22.22s |",
         product_name,
         price,
         product_quantity,
         category_string
    );
    mvprintw(5, 1, "+-----------------+--------------+--------+------------------------+");

    noecho();
    printw("\n");
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\n Y - Confirmar Insercao do Produto");
    attroff(COLOR_PAIR(1) | A_BOLD);
    attron(COLOR_PAIR(2) | A_BOLD);
    printw("\n Qualquer Tecla - Cancelar Insercao do Produto");
    attroff(COLOR_PAIR(2) | A_BOLD);
    userChoose = getch();

    char sql[256];
    sprintf(sql,
    "INSERT INTO product (product_name, price, quantity, category_id, unit_type) VALUES ('%s', %.2f, %d, %d, '%s')",
    product_name, price, product_quantity, category_id, unit_type);

    sqlite3 *db = 0;
    char *zErrMsg = 0;

    int rc = sqlite3_open("db.db3", &db);

    if(userChoose == 'y' || userChoose == 'Y'){


    if (rc != SQLITE_OK) {
        printw("ERRO ao abrir o banco de dados\n");
        refresh();
        getch();
        return 0;
    }

    rc = sqlite3_exec(db, sql, callBack, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
    printw("Erro ao executar o INSERT: %s\n", zErrMsg);
    refresh();
    sqlite3_free(zErrMsg);
    getch();
    return 0;
    }
    clear();

    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\n Produto inserido com sucesso!");
    attroff(COLOR_PAIR(1) | A_BOLD);
    } else {
        clear(); printw("ACAO CANCELADA!"); refresh();;
    }

    printw("\n Redirecionando...");
    refresh();
    napms(1000);
    sqlite3_close(db);
    product_display();
}

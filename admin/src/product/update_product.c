#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/sqlite3.h"
#include <curses.h>
#include "../../headers/product/product_display.h"

int update_product() {
    char product_id_string[11];
    int product_id;

    char product_name[50];
    char unit_type[11];
    int category_id;
    char category_name[20];
    double price;
    int product_quantity;

    char edit_product_name[50];
    char edit_unit_type[11];
    char edit_category[20];
    char edit_price_string[11];
    double edit_price;
    int edit_product_quantity;

    int product_found = 0;
    int callBackGetProductForBeUpdated(void *arg, int argc, char **argv, char **column) {

        if (argc >= 6) {

            strcpy(product_name, argv[0]);
            price = atof(argv[1]);

            product_quantity = atoi(argv[2]);
            category_id = atoi(argv[3]);
            strcpy(unit_type, argv[4]);

            strcpy(category_name, argv[5]);
            product_found++;
            return 0;
        }
    }

    void validationRedirection(const char *message) {
        clear();
        printw("Insira campos validos!\n%s", message);
        refresh();
        napms(2500);
        update_product();
    }

    clear();
    echo();
    mvprintw(0, 1, "+------+----------------+");
    mvprintw(1, 1, "|   Atualizar Produto   |");
    mvprintw(2, 1, "+------+----------------+");
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

    char sql[220];
    sprintf(sql, "SELECT product_name, price, quantity, category_id, unit_type, category_name FROM product LEFT JOIN categories c ON product.category_id = c.id WHERE product.id = %d", product_id);
    rc = sqlite3_exec(db, sql, callBackGetProductForBeUpdated, 0, &zErrMsg);

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
    mvprintw(1, 1, "+-----------------+------------+----------+--------------------------------------+");
    mvprintw(2, 1, "| Nome            | Preco      |  Qtd     | Categoria              |  Tipo       |");
    mvprintw(3, 1, "+-----------------+------------+----------+--------------------------------------+");

    mvprintw(4, 1, "| %-15.15s | %-10.2f | %-8d | %-22.22s | %-11.11s |",
         product_name,
         price,
         product_quantity,
         category_name,
         unit_type
    );
   mvprintw(5, 1, "+-----------------+--------------+--------+--------------------------------------+");
    curs_set(1);
    printw("\n");
    printw("\n Atualizar Nome: => ", edit_product_name);
    getnstr(edit_product_name, sizeof(edit_product_name) - 1);

    if(strlen(edit_product_name) < 4 || strlen(edit_product_name) >= 49) {
    char message[] = "O campo precisa ter entre 4 a 49 caracteres";
    validationRedirection(message);
    }

    printw("\n Categoria Atualizada: ");
    printw("\n 1. Frutas pereciveis");
    printw("\n 2. Frutas citricas");
    printw("\n 3. Frutas tropicais");
    printw("\n 4. Frutas de caroco");
    noecho();
    char category_id_string = getch();

    switch(category_id_string) {
        case '1':
            strcpy(edit_category, "Frutas pereciveis"); break;
        case '2':
            strcpy(edit_category, "Frutas citricas"); break;
        case '3':
            strcpy(edit_category, "Frutas tropicais"); break;
        case '4': strcpy(edit_category, "Frutas de caroco"); break;
    }

     if(strlen(edit_category) == NULL || strlen(edit_category) <= 0) {
    char message[] = " Escolha um valor valido!";
    validationRedirection(message);
    }
    echo();
    int edit_category_id = category_id_string - '0';
    printw("\n");
    printw("\n Atualizar preco => ");
    getnstr(edit_price_string, sizeof(edit_price_string) - 1);
    // colocar . no lugar da vírgula
    for (int i = 0; i < strlen(edit_price_string); i++) {
    if (edit_price_string[i] == ',') {
        edit_price_string[i] = '.';
    }
    }
    edit_price = strtof(edit_price_string, NULL);

    if(edit_price == 0) {
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
            strcpy(edit_unit_type, "Unidade");
    break;
        case '2':
            strcpy(edit_unit_type, "Caixa");
    break;
        case '3':
            strcpy(edit_unit_type, "KG");
        default:
    validationRedirection("Insira uma opcao valida"); break;
    break;
    }

    if(strlen(edit_unit_type) == NULL || strlen(edit_unit_type) <= 0) {
    char message[] = " Escolha um valor valido!";
    validationRedirection(message);
    }

    printw("\n");
    echo();
    printw("\n Quantidade Atualizada de %s => ", edit_unit_type);
    char quantity_string[11];
    getnstr(quantity_string, sizeof(quantity_string) - 1);
    edit_product_quantity = strtol(quantity_string, NULL, 10);

    if(edit_product_quantity <= 0) {
    char message[] = " O valor nao pode ser menor ou igual a 0 ou diferente de um numero";
    validationRedirection(message);
    }

    clear();

    printw("\n Nome: %s => %s",product_name, edit_product_name);
    printw("\n Quantidade: %d => %d",product_quantity, edit_product_quantity);
    printw("\n Tipo: %s => %s", unit_type, edit_unit_type);
    printw("\n Preco: %.2f => %.2f", price, edit_price);
    printw("\n Categoria: %s => %s", category_name, edit_category);

    noecho();
    attron(COLOR_PAIR(3) | A_BOLD);
    printw("\n\n Y - Confirmar Atualizacao do Produto");
    attroff(COLOR_PAIR(3) | A_BOLD);
      attron(COLOR_PAIR(2) | A_BOLD);
    printw("\n Qualquer Tecla - Cancelar Atualizacao do Produto");
    attroff(COLOR_PAIR(2) | A_BOLD);
    userChoose = getch();

    if (userChoose == 'Y' || userChoose == 'y') {
        sprintf(sql, "UPDATE product SET product_name = '%s', quantity = %d, category_id = %d, price = %.2f, unit_type = '%s' where id = %d", edit_product_name, edit_product_quantity, edit_category_id, edit_price, edit_unit_type, product_id);
        rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

        attron(COLOR_PAIR(3) | A_BOLD);
        clear();
        printw("\n Produto atualizado com sucesso!");
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

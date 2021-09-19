#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by VladB on 08-Mar-21.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "ui.h"
#include "../utils/comparators_and_filters.h"

#define INITIAL_CAPACITY 4

void print_menu();

void print_product(Product *p);

void ui_print_category_convention();

UI *create_ui(Service *srv) {
    UI *ui = (UI *) malloc(sizeof(UI));
    ui->srv = srv;
    return ui;
}

void destroy_ui(UI *ui) {
    free(ui);
}

void ui_print_all_products(UI *ui) {
    int i, products_count = srv_get_no_products(ui->srv);
    if (products_count == 0) {
        printf("\nThere are no products in the repository.\n");
        return;
    }
    DynamicArray *all_products = get_service_products(ui->srv);
    Product *current_product;
    printf("\nThese are all the products from the repository:\n");
    for (i = 0; i < products_count; i++) {
        current_product = (Product*) get_elem_from_position(all_products, i);
        printf("\t%2d) ", i + 1);
        print_product(current_product);
    }
}

void *strip_string(char str[]) {
    while (isspace((unsigned char) *str)) {
        str++;
    }
    if (*str == 0) {
        return str;
    }
    char *end = str + strlen(str) - 1;
    while (end > str && (isspace((unsigned char) *end))) {
        end--;
    }
    end[1] = '\0';
    return str;
}

void ui_add_product(UI *ui) {
    char user_input[256], name[256];
    int category, day, month, year, response;
    double quantity;
    printf("\nPlease give the name of the product: ");
    scanf("%s", name);
    strip_string(name);

    ui_print_category_convention();
    printf("Please give the category: ");
    scanf("%s", user_input);
    category = atoi(user_input);
    if (category == 0) {
        printf("\nError! The category should be an integer.\n");
        return;
    }

    printf("\nPlease give the quantity of the product (kg): ");
    scanf("%s", user_input);
    quantity = atof(user_input);
    if (fabs(quantity) < 0.00001) {
        printf("\nError! The quantity should be a real number.\n");
        return;
    }

    printf("\nPlease give the day of the product's expiration date: ");
    scanf("%s", user_input);
    day = atoi(user_input);
    if (day == 0) {
        printf("\nError! The day should be an integer.\n");
        return;
    }

    printf("\nPlease give the month of the product's expiration date: ");
    scanf("%s", user_input);
    month = atoi(user_input);
    if (month == 0) {
        printf("\nError! The month should be an integer.\n");
        return;
    }

    printf("\nPlease give the year of the product's expiration date: ");
    scanf("%s", user_input);
    year = atoi(user_input);
    if (year == 0) {
        printf("\nError! The year should be an integer.\n");
        return;
    }

    response = srv_add_product(ui->srv, name, category, quantity, day, month, year);
    if (response == 0) {
        printf("\nProduct added.\n");
    } else if (response == 1) {
        printf("\nQuantity added to existing product.\n");
    } else if (response < 0) {
        printf("\nThe product could not be added because:\n");
        if (response % 3 == 0) {
            printf("\tThe given name is invalid.\n");
        }
        if (response % 5 == 0) {
            printf("\tThe given category is invalid.\n");
        }
        if (response % 7 == 0) {
            printf("\tThe given quantity is invalid.\n");
        }
        if (response % 11 == 0) {
            printf("\tThe given date is invalid.\n");
        }
    }
}

void ui_remove_product(UI *ui) {
    char user_input[256], name[256];
    int category;
    printf("\nPlease give the name of the product: ");
    scanf("%s", name);
    strip_string(name);
    ui_print_category_convention();
    printf("Please give the category: ");
    scanf("%s", user_input);
    category = atoi(user_input);
    if (category == 0) {
        printf("\nError! The category should be an integer.\n");
        return;
    }
    if (srv_remove_product(ui->srv, name, category) == -1) {
        printf("\nError! The given product is not in the repository.\n");
    } else {
        printf("\nProduct removed.\n");
    }
}

void ui_update_product(UI *ui) {
    char name[256], user_input[256];
    int category, new_day, new_month, new_year;
    double new_quantity;

    printf("\nPlease give the name of the product: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    strip_string(name);

    ui_print_category_convention();
    printf("Please give the category: ");
    fgets(user_input, sizeof(user_input), stdin);
    category = atoi(user_input);
    if (category == 0) {
        printf("\nError! The category should be an integer.\n");
        return;
    }

    printf("\nGive the new quantity (press ENTER if you want to keep this as is): ");
    fgets(user_input, sizeof(user_input), stdin);
    new_quantity = atof(user_input);
    if (new_quantity == 0) {
        printf("\nThe quantity will not be updated.\n");
    }

    printf("\nGive the new expiration day (press ENTER if you want to keep this as is): ");
    fgets(user_input, sizeof(user_input), stdin);
    new_day = atoi(user_input);
    if (new_day == 0) {
        printf("\nThe expiration day will not be updated.\n");
    }

    printf("\nGive the new expiration month (press ENTER if you want to keep this as is): ");
    fgets(user_input, sizeof(user_input), stdin);
    new_month = atoi(user_input);
    if (new_month == 0) {
        printf("\nThe expiration month will not be updated.\n");
    }

    printf("\nGive the new expiration year (press ENTER '-' if you want to keep this as is): ");
    fgets(user_input, sizeof(user_input), stdin);
    new_year = atoi(user_input);
    if (new_year == 0) {
        printf("\nThe expiration year will not be updated.\n");
    }

    if (srv_update_product(ui->srv, name, category, new_quantity, new_day, new_month, new_year) == 0) {
        printf("\n\nThe update has been successful.\n");
    } else {
        printf("\n\nError! The given product is not in the repository. The update has been unsuccessful.\n");
    }
}

void ui_name_ascending_filter_with_quantity(UI* ui) {
    char s[256];
    int response, product_count;
    double quantity;
    Product *current_product;
    printf("\nYou want to filter the products which have a quantity of at most: ");
    getchar();
    fgets(s, sizeof(s), stdin);
    strip_string(s);
    quantity = atof(s);
    if (quantity == 0) {
        printf("\nError! Invalid quantity given!\n");
        return;
    }
    DynamicArray *result = create_dynamic_array(INITIAL_CAPACITY);
    response = filter_by_quantity(get_service_products(ui->srv), result, quantity, less_than_quantity_filter);
    if (response == 1) {
        printf("Error! The given quantity must be a positive real number.\n");
        return;
    }

    generic_sort_products(result, ascending_name_comp);
    product_count = get_dynamic_array_size(result);
    if (product_count == 0) {
        printf("\nThere are no products with the given filter.\n");
        destroy_dynamic_array(result);
        return;
    }
    printf("\nThese are the filtered products sorted in descending order by name:\n");
    for (int i = 0; i < product_count; i++) {
        current_product = get_elem_from_position(result, i);
        printf("\t%2d) ", i + 1);
        print_product(current_product);
    }
    destroy_dynamic_array(result);
}

void ui_quantity_ascending_filter_with_string(UI *ui) {
    DynamicArray *result = create_dynamic_array(INITIAL_CAPACITY);
    char s[256];
    int product_count, i;
    Product *current_product;
    printf("\nPlease give the string: ");
    getchar();
    fgets(s, sizeof(s), stdin);
    strip_string(s);

    filter_by_name(get_service_products(ui->srv), result, s, string_filter);
    generic_sort_products(result, ascending_quantity_comp);
    product_count = get_dynamic_array_size(result);
    if (product_count == 0) {
        printf("\nThere are no products with the given filter.\n");
        destroy_dynamic_array(result);
        return;
    }

    printf("\nThese are the filtered products sorted in ascending order by quantity:\n");
    for (i = 0; i < product_count; i++) {
        current_product = get_elem_from_position(result, i);
        printf("\t%2d) ", i + 1);
        print_product(current_product);
    }
    destroy_dynamic_array(result);
}

void ui_name_descending_filter_by_string(UI *ui) {
    DynamicArray *result = create_dynamic_array(INITIAL_CAPACITY);
    char s[256];
    int product_count, i;
    Product *current_product;
    printf("\nPlease give the string: ");
    getchar();
    fgets(s, sizeof(s), stdin);
    strip_string(s);

    filter_by_name(get_service_products(ui->srv), result, s, string_filter);

    generic_sort_products(result, descending_name_comp);
    product_count = get_dynamic_array_size(result);
    if (product_count == 0) {
        printf("\nThere are no products with the given filter.\n");
        destroy_dynamic_array(result);
        return;
    }
    printf("\nThese are the filtered products sorted in descending order by name:\n");
    for (i = 0; i < product_count; i++) {
        current_product = get_elem_from_position(result, i);
        printf("\t%2d) ", i + 1);
        print_product(current_product);
    }
    destroy_dynamic_array(result);
}

void ui_filter_category_and_close_expiration(UI *ui) {
    char user_input[256];
    int category, nr_days, response, product_count, i, sorting_type;
    DynamicArray *filtered1 = create_dynamic_array(INITIAL_CAPACITY);
    Product *current_product;
    ui_print_category_convention();
    printf("Please give the category: ");
    getchar();
    fgets(user_input, sizeof(user_input), stdin);
    strip_string(user_input);
    if (strlen(user_input) == 0 || (strlen(user_input) == 1 && user_input[0] == '\n')) {
        category = -1;
    } else {
        category = atoi(user_input);
    }
    if (category == 0) {
        printf("\nError! The category should be an integer.\n");
        return;
    }
    response = filter_by_category(get_service_products(ui->srv), filtered1, category, category_filter);
    if (response == 1) {
        printf("\nError! Invalid category given.\n");
        destroy_dynamic_array(filtered1);
        return;
    }
    printf("\nSee the chosen products which expire in X days. Please give X: ");
    fgets(user_input, sizeof(user_input), stdin);
    strip_string(user_input);
    nr_days = atoi(user_input);
    if (nr_days == 0) {
        printf("\nError! Invalid number of days given.\n");
        destroy_dynamic_array(filtered1);
        return;
    }
    DynamicArray *filtered2 = create_dynamic_array(INITIAL_CAPACITY);

    response = filter_by_expiration(filtered1, filtered2, nr_days, expiration_date_filter);
    if (response == 1) {
        printf("\nError! Invalid number of days given.\n");
        destroy_dynamic_array(filtered1);
        destroy_dynamic_array(filtered2);
        return;
    }

    printf("\nIn which order do you want the results printed:\n");
    printf("\t1 - Ascending by expiration date\n"
           "\t2 - Descending by expiration date\n"
           "Please give the sorting type: ");
    fgets(user_input, sizeof(user_input), stdin);
    strip_string(user_input);
    sorting_type = atoi(user_input);
    if (sorting_type == 1) {
        generic_sort_products(filtered2, ascending_expiration_comp);
    } else if (sorting_type == 2) {
        generic_sort_products(filtered2, descending_expiration_comp);
    } else if (sorting_type == 0) {
        printf("\nError! Invalid sorting type given.\n");
        destroy_dynamic_array(filtered1);
        destroy_dynamic_array(filtered2);
        return;
    }

    product_count = get_dynamic_array_size(filtered2);
    if (product_count == 0) {
        printf("\nThere are no products which obey the given filters.\n");
    } else {
        printf("\nThese are the filtered products:\n");
        for (i = 0; i < product_count; i++) {
            current_product = (Product *) get_elem_from_position(filtered2, i);
            printf("\t%2d) ", i + 1);
            print_product(current_product);
        }
    }
    destroy_dynamic_array(filtered1);
    destroy_dynamic_array(filtered2);
}

void ui_undo(UI *ui) {
    if (apply_undo(ui->srv) == 0) {
        printf("\nLast command undone.\n");
    } else {
        printf("\nNo undos left!\n");
    }
}

void ui_redo(UI *ui) {
    if (apply_redo(ui->srv) == 0) {
        printf("\nLast command redone.\n");
    } else {
        printf("\nNo redos left!\n");
    }
}

void run_ui(UI *ui) {
    char cmd[256];
    int cmd_as_int, continue_to_run = 1;
    while (continue_to_run) {
        print_menu();
        printf("Please enter a command: ");
        scanf("%s", cmd);
        cmd_as_int = atoi(cmd);
        switch (cmd_as_int) {
            case 1:
                ui_print_all_products(ui);
                break;
            case 2:
                ui_add_product(ui);
                break;
            case 3:
                ui_remove_product(ui);
                break;
            case 4:
                ui_update_product(ui);
                break;
            case 5:
                ui_quantity_ascending_filter_with_string(ui);
                break;
            case 6:
                ui_name_descending_filter_by_string(ui);
                break;
            case 7:
                ui_name_ascending_filter_with_quantity(ui);
                break;
            case 8:
                ui_filter_category_and_close_expiration(ui);
                break;
            case 9:
                ui_undo(ui);
                break;
            case 10:
                ui_redo(ui);
                break;
            case 11:
                continue_to_run = 0;
                break;
            default:
                printf("Invalid command.\n");
                break;
        }
    }
}

void print_menu() {
    printf("\nThese are the currently implemented commands:\n"
           "\t 1 - Print all products\n"
           "\t 2 - Add a product\n"
           "\t 3 - Remove a product\n"
           "\t 4 - Update a product\n"
           "\t 5 - Filter products by string and print in ascending order of quantity\n"
           "\t 6 - Filter products by string and print in descending order of name\n"
           "\t*7 - Filter products by quantity and print in ascending order of name\n"
           "\t*8 - Filter products by category and print those with close expiration dates\n"
           "\t*9 - Undo\n"
           "\t*10 - Redo\n"
           "\t11 - Exit\n"
           "* - Added for A4\n");
}

void print_product(Product *p) {
    int day, month, year;
    char category[256];
    switch (get_product_category(p)) {
        case 1:
            strcpy(category, "Dairy(Category 1)");
            break;
        case 2:
            strcpy(category, "Sweets(Category 2)");
            break;
        case 3:
            strcpy(category, "Meat(Category 3)");
            break;
        case 4:
            strcpy(category, "Fruit(Category 4)");
            break;
    }
    printf("Name: %s\n", get_product_name(p));
    printf("\t    Category: %s\n", category);
    printf("\t    Quantity: %.2f kg\n", get_product_quantity(p));
    day = get_product_expiration_day(p);
    month = get_product_expiration_month(p);
    year = get_product_expiration_year(p);
    printf("\t    Expiration date: %d.%d.%d (DD/MM/YYYY)\n\n", day, month, year);
}

void ui_print_category_convention() {
    printf("\nThe available categories are:\n"
           "\t1 - Dairy\n"
           "\t2 - Sweets\n"
           "\t3 - Meat\n"
           "\t4 - Fruit\n");
}

#pragma clang diagnostic pop
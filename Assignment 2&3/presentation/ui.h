//
// Created by VladB on 08-Mar-21.
//

#ifndef A23_BVLAD917_UI_H
#define A23_BVLAD917_UI_H

#include "../business/service.h"

typedef struct {
    Service *srv;
} UI;

UI *create_ui(Service *srv);

void destroy_ui(UI *ui);

void run_ui(UI *ui);

void ui_print_all_products(UI* ui);

void ui_add_product(UI* ui);

void ui_remove_product(UI *ui);

void ui_update_product(UI *ui);

void ui_name_ascending_filter_with_quantity(UI* ui);

void ui_quantity_ascending_filter_with_string(UI* ui);

void ui_name_descending_filter_by_string(UI *ui);

void ui_filter_category_and_close_expiration(UI *ui);

void ui_undo(UI *ui);

void ui_redo(UI *ui);

#endif //A23_BVLAD917_UI_H

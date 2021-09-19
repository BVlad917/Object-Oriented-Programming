//
// Created by VladB on 21-Mar-21.
//

#ifndef A45_BVLAD917_UI_H
#define A45_BVLAD917_UI_H


#include "../business/service.h"

class UI {
private:
    Service &srv;

    static void ui_print_admin_menu();

    static void ui_print_user_menu();

    void ui_set_app_permissions();

    void ui_add_trench_coat();

    void ui_remove_trench_coat();

    void ui_update_trench_coat();

    void ui_print_all_trench_coats();

    void ui_see_filtered_1_by_1();

    static void ui_print_shopping_options();

    void ui_print_shopping_cart();

    void ui_display_shopping_cart_in_file();

    static void strip_string(std::string& str);

    bool ui_handle_admin_mode();

    bool ui_handle_user_mode();

    static void ui_print_formatted_coat(TrenchCoat &coat);

public:
    void run_app();
    explicit UI(Service& srv);
};


#endif //A45_BVLAD917_UI_H

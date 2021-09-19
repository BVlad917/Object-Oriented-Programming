//
// Created by VladB on 05-Apr-21.
//

#ifndef T1_BVLAD917_1_UI_H
#define T1_BVLAD917_1_UI_H


#include <set>
#include "../business/service.h"

class UI {
private:
    Service &srv;
    static void ui_print_menu();

    void ui_add_gene();

    void ui_print_decreasing_genes();

    void ui_print_filtered_genes();

    void ui_longest_subsequence();

public:
    explicit UI(Service &srv);

    void start();
};


#endif //T1_BVLAD917_1_UI_H

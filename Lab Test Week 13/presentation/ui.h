//
// Created by VladB on 26-Apr-21.
//

#ifndef T2_BVLAD917_1_UI_H
#define T2_BVLAD917_1_UI_H


#include "../business/service.h"

class UI {
private:
    Service& srv;

public:
    explicit UI(Service& srv);

    static void print_menu();

    void ui_addMeasurement();

    void ui_print_all_measurements();

    void ui_is_healthy();

    void ui_save_to_file();

    void start();
};


#endif //T2_BVLAD917_1_UI_H

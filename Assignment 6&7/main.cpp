#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by VladB on 19-Mar-21.
//

#include <iostream>
#include "tests/all_tests.h"
#include "business/service.h"
#include "presentation/ui.h"
#include "persistency/basket_csv_repo.h"
#include "persistency/basket_html_repo.h"
#include "persistency/sql_repo.h"

int main() {
    AllTests::void_run_all_tests();
    std::string user_input, file_name;
    int user_input_as_int = -1;
    while (user_input_as_int != 1 && user_input_as_int != 2) {
        std::cout << "What type of file would you like the shopping basket to be?\n"
                     "\t1 - CSV\n"
                     "\t2 - HTML\n"
                     "Please make a choice: ";
        std::cin >> user_input;
        user_input_as_int = std::atoi(user_input.c_str());
    }
    if (user_input_as_int == 1) {
        file_name = "csv_basket_repo.csv";
        BasketCSVRepo shopping_cart{file_name};

//        file_name = "store_repo.txt";
//        FileRepo file_repo{file_name};
        file_name = "sql_store_repo.db";
        SQLRepo file_repo{file_name};

        Service srv{file_repo, shopping_cart};
        UI ui{srv};
        ui.run_app();
    }
    else {
        file_name = "html_basket_repo.html";
        BasketHTMLRepo shopping_cart{file_name};

//        file_name = "store_repo.txt";
//        FileRepo file_repo{file_name};
        file_name = "sql_store_repo.db";
        SQLRepo file_repo{file_name};

        Service srv{file_repo, shopping_cart};
        UI ui{srv};
        ui.run_app();
    }
    return 0;
}
#pragma clang diagnostic pop
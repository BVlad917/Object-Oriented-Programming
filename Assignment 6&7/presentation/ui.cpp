#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by VladB on 21-Mar-21.
//

#include <iostream>
#include <algorithm>

#include "ui.h"
#include "../utils/size_filter.h"
#include "../errors/exceptions.h"

UI::UI(Service &srv) : srv(srv) {}

void UI::ui_print_admin_menu() {
    std::cout << "\nAdministrator commands:\n"
                 "\t1 - Print all trench coats\n"
                 "\t2 - Add a new trench coat\n"
                 "\t3 - Remove a trench coat\n"
                 "\t4 - Update a trench coat\n"
                 "\t5 - Change permissions\n"
                 "\t6 - Exit app\n";
}

void UI::ui_print_user_menu() {
    std::cout << "\nUser commands:\n"
                 "\t1 - See the trench coats one by one, filtered by size\n"
                 "\t2 - See the shopping cart and the full price\n"
                 "\t3 - Display the shopping basket (CSV/HTML)\n"
                 "\t4 - Change permissions\n"
                 "\t5 - Exit app\n";
}

void UI::ui_set_app_permissions() {
    int user_choice;
    char user_input[256];
    std::cin.ignore();
    std::cout << "In which mode do you want to run the app in?\n";
    std::cout << "\t1 - User mode\n"
                 "\t2 - Administrator mode\n";
    while (true) {
        std::cout << "In which mode do you want to run the app in: ";
        std::cin.getline(user_input, sizeof(user_input));
        user_choice = atoi(user_input);
        if (user_choice == 1) {
            this->srv.change_app_permissions("User");
            return;
        } else if (user_choice == 2) {
            this->srv.change_app_permissions("Admin");
            return;
        } else {
            std::cout << "\nInvalid permission chosen. Choose again.\n";
        }
    }
}

void UI::ui_add_trench_coat() {
    std::string size, colour, photo_link, user_input;
    int quantity;
    double price;

    std::cout << "\nGive the size of the trench coat: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, size);
    UI::strip_string(size);

    std::cout << "\nGive the colour of the trench coat: ";
    std::getline(std::cin, colour);
    UI::strip_string(colour);

    std::cout << "\nGive the price of the trench coat: ";
    std::getline(std::cin, user_input);
    UI::strip_string(user_input);
    price = atof(user_input.c_str());

    std::cout << "\nGive the quantity of the trench coat: ";
    std::getline(std::cin, user_input);
    UI::strip_string(user_input);
    quantity = atoi(user_input.c_str());

    std::cout << "\nGive the website link to the trench coat: ";
    std::getline(std::cin, photo_link);
    UI::strip_string(photo_link);

    this->srv.add_trench(size, colour, price, quantity, photo_link);
    std::cout << "\nTrench coat added.\n";
}

void UI::ui_remove_trench_coat() {
    std::string size, colour;
    std::cout << "\nGive the size of the trench coat: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, size);
    UI::strip_string(size);

    std::cout << "\nGive the colour of the trench coat: ";
    std::getline(std::cin, colour);
    UI::strip_string(colour);

    this->srv.remove_trench(size, colour);
    std::cout << "\nTrench coat removed.\n";
}

void UI::ui_update_trench_coat() {
    std::string size, colour, photo_link, user_input;
    int quantity;
    double price;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nGive the size of the trench coat: ";
    std::getline(std::cin, size);
    UI::strip_string(size);

    std::cout << "\nGive the colour of the trench coat: ";
    std::getline(std::cin, colour);
    UI::strip_string(colour);

    std::cout << "\nGive the new price of the trench coat (leave empty to not change): ";
    std::getline(std::cin, user_input);
    UI::strip_string(user_input);
    price = atof(user_input.c_str());

    std::cout << "\nGive the new quantity of the trench coat (leave empty to not change): ";
    std::getline(std::cin, user_input);
    UI::strip_string(user_input);
    quantity = atoi(user_input.c_str());

    std::cout << "\nGive the new website link to the trench coat (leave empty to not change): ";
    std::getline(std::cin, photo_link);
    UI::strip_string(photo_link);

    this->srv.update_trench(size, colour, price, quantity, photo_link);
    std::cout << "\nTrench coat updated.\n";
}

void UI::ui_print_formatted_coat(TrenchCoat &coat) {
    std::cout << "Proper Trench Coat, size " << coat.get_trench_size() << ", " << coat.get_trench_colour() << "\n";
    std::cout << "\t   Price: " << coat.get_trench_price() << "$\n";
    std::cout << "\t   Quantity in stock: " << coat.get_trench_quantity() << "\n";
    std::cout << "\t   Link: " << coat.get_trench_photograph() << "\n";
}

void UI::ui_print_all_trench_coats() {
    std::vector<TrenchCoat> all_trench_coats = this->srv.get_all_trenches_from_repo();
    if (all_trench_coats.empty()) {
        std::cout << "\nThere are no trench coats in the repository.\n";
        return;
    }
    std::cout << "\nThese are all the trench coats in the repository:\n";
    int i = 1;
    for (auto &trench: all_trench_coats) {
        std::cout << "\t" << i++ << ") ";
        this->ui_print_formatted_coat(trench);
        std::cout << "\n";
    }
}

void UI::ui_print_shopping_options() {
    std::cout << "\nAvailable commands:\n";
    std::cout << "\n\t1. Add to shopping cart\n"
                 "\t2. Next trench coat\n"
                 "\t3. Open website page\n"
                 "\t4. Exit\n";
}

void UI::ui_see_filtered_1_by_1() {
    std::string user_size, user_command, open_web;
    std::cout << "\nWhat is the size of trench coats you want to see: ";
    std::cin.ignore();
    std::getline(std::cin, user_size);
    SizeFilter filter{user_size};
    std::vector<TrenchCoat> filtered = this->srv.filter_by(filter);

    if (filtered.empty()) {
        std::cout << "\nThere are no trench coats with the given size.\n";
        return;
    }
    std::cout << "\nThese are the filtered trench coats from the shop:\n";
    int command_as_int, index = 1;
    auto it = filtered.begin();
    bool keep_running = true;
    while (keep_running) {
        std::cout << "\n\t   " << index << ") ";
        this->ui_print_formatted_coat(*it);
        this->ui_print_shopping_options();
        std::cout << "\nWhat do you want to do: ";
        std::getline(std::cin, user_command);
        command_as_int = std::atoi(user_command.c_str());
        switch (command_as_int) {
            case 1:
                try {
                    this->srv.put_trench_in_shopping_cart(*it);
                    std::cout << "\nTrench coat added to the shopping cart.\n";
                    std::cout << "\nThe total price is: " << this->srv.get_total_price() << "$\n";
                }
                catch (ServiceException& se) {
                    std::cout << se.what();
                }
                break;
            case 2:
                it++;
                index++;
                if (index == filtered.size() + 1) index = 1;
                if (it == filtered.end()) it = filtered.begin();
                break;
            case 3:
                open_web = "start " + (*it).get_trench_photograph();
                system(open_web.c_str());
                break;
            case 4:
                keep_running = false;
                break;
            default:
                std::cout << "\nInvalid command given\n";
                break;
        }
    }
}

void UI::ui_print_shopping_cart() {
    std::vector<TrenchCoat> shopping_cart_coats = this->srv.get_all_trenches_from_shopping_cart();
    if (shopping_cart_coats.empty()) {
        std::cout << "\nThere are no trench coats in the repository.\n";
        return;
    }
    std::cout << "\nThese are all the trench coats in the repository:\n";
    int i = 1;
    for (auto &trench: shopping_cart_coats) {
        std::cout << "\t" << i++ << ") ";
        this->ui_print_formatted_coat(trench);
        std::cout << "\n";
    }
}

void UI::ui_display_shopping_cart_in_file() {
    this->srv.open_shopping_basket_file();
}

bool UI::ui_handle_admin_mode() {
    std::string user_input;
    int user_command;
    this->ui_print_admin_menu();
    std::cout << "Give a command: ";
    std::cin >> user_input;
    UI::strip_string(user_input);
    user_command = atoi(user_input.c_str());
    try {
        switch (user_command) {
            case 1:
                this->ui_print_all_trench_coats();
                break;
            case 2:
                this->ui_add_trench_coat();
                break;
            case 3:
                this->ui_remove_trench_coat();
                break;
            case 4:
                this->ui_update_trench_coat();
                break;
            case 5:
                this->srv.change_app_permissions("User");
                break;
            case 6:
                return false;
            default:
                std::cout << "\nInvalid command given.\n";
                break;
        }
    }
    catch (RepositoryException &re) {
        std::cout << re.what();
    }
    catch (ValidationException &ve) {
        std::cout << ve.what();
    }
    catch (ServiceException &se) {
        std::cout << se.what();
    }
    catch (DynamicArrayException &de) {
        std::cout << de.what();
    }
    return true;
}

bool UI::ui_handle_user_mode() {
    std::string user_input;
    int user_command;
    this->ui_print_user_menu();
    std::cout << "Give a command: ";
    std::cin >> user_input;
    UI::strip_string(user_input);
    user_command = atoi(user_input.c_str());
    try {
        switch (user_command) {
            case 1:
                this->ui_see_filtered_1_by_1();
                break;
            case 2:
                this->ui_print_shopping_cart();
                std::cout << "\nFull price: " << this->srv.get_total_price() << "$\n";
                break;
            case 3:
                this->ui_display_shopping_cart_in_file();
                break;
            case 4:
                this->srv.change_app_permissions("Admin");
                break;
            case 5:
                return false;
            default:
                std::cout << "\nInvalid command given.\n";
                break;
        }
    }
    catch (RepositoryException &re) {
        std::cout << re.what();
    }
    catch (ValidationException &ve) {
        std::cout << ve.what();
    }
    catch (ServiceException &se) {
        std::cout << se.what();
    }
    catch (DynamicArrayException &de) {
        std::cout << de.what();
    }
    return true;
}

void UI::run_app() {
    bool keep_running = true;
    std::cout << "\n\nHello!\n";
    this->ui_set_app_permissions();
    // Since we're using a file repository, we don't need to fill the repository with dummy instances every time
    // we run the program. We just need to do it once. If we run this command twice we'd get a repository exception
    // since we would be trying to add the same instance multiple times to the repository
//    this->srv.fill_repo();
    while (keep_running) {
        if (this->srv.get_app_permissions() == "User") {
            keep_running = this->ui_handle_user_mode();
        } else if (this->srv.get_app_permissions() == "Admin") {
            keep_running = this->ui_handle_admin_mode();
        }
    }
    std::cout << "\nHave a great day!\n";
}

void UI::strip_string(std::string &str) {
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
    for (int i = 1; str[i + 1];) {
        if (str[i - 1] != ' ' && str[i] == ' ' && str[i + 1] == ' ') {
            str = str.substr(0, i) + str.substr(i + 1);
        } else {
            i++;
        }
    }
}

//
// Created by VladB on 26-Apr-21.
//

#include <iostream>
#include "ui.h"
#include "../domain/bmi.h"
#include "../domain/bp.h"

UI::UI(Service &srv): srv(srv) {}

void UI::ui_addMeasurement() {
    std::string type, date;
    int sys_value, dis_value;
    double value;
    std::cout << "\nGive the measurement type (BMI or BP): ";
    std::cin >> type;
    if (type == "BMI") {
        std::cout << "\nGive the date (10 characters, <year.month.day> format): ";
        std::cin >> date;
        std::cout << "\nGive the value: ";
        std::cin >> value;
        Measurement* m = new BMI{date, value};
        this->srv.srv_addMeasurement(m);
        std::cout << "\nMeasurement added.\n";
        if (m->isNormalValue()) {
            std::cout << "The measurement has normal values.\n";
        }
        else {
            std::cout << "CAREFUL! The measurement is NOT normal.\n";
        }
    }
    else if (type == "BP") {
        std::cout << "\nGive the date (10 characters, <year.month.day> format): ";
        std::cin >> date;
        std::cout << "\nGive the systolic value: ";
        std::cin >> sys_value;
        std::cout << "\nGive the diastolic value: ";
        std::cin >> dis_value;
        Measurement* m = new BP{date, sys_value, dis_value};
        this->srv.srv_addMeasurement(m);
        std::cout << "\nMeasurement added.\n";
        if (m->isNormalValue()) {
            std::cout << "The measurement has normal values.\n";
        }
        else {
            std::cout << "CAREFUL! The measurement is NOT normal.\n";
        }
    }
    else {
        throw std::runtime_error("Invalid measurement type given.\n");
    }

}

void UI::print_menu() {
    std::cout << "Available commands:\n";
    std::cout << "\t1 - Add new measurement\n"
                 "\t2 - Print all measurements\n"
                 "\t3 - Is person healthy?\n"
                 "\t4 - Save measurements newer than date\n"
                 "\t5 - Exit\n";
}

void UI::ui_print_all_measurements() {
    std::vector<Measurement*> all_measurements = this->srv.getAllMeasurements();
    std::cout << "Person Name: " + this->srv.srvGetPersonName() << "\n";
    for (Measurement* m: all_measurements) {
        std::cout << m->toString() << "\n";
    }
}

void UI::ui_is_healthy() {
    if (this->srv.getAllMeasurements().empty()) {
        std::cout << "\nNo measurements\n";
        return;
    }
    std::string month;
    int month_as_int;
    std::cin.ignore();
    std::cout << "\nGive the month: ";
    std::cin >> month;
    if (month[0] == '0') {
        month_as_int = std::atoi(month.substr(1,1).c_str());
    }
    else {
        month_as_int = std::atoi(month.c_str());
    }
    if (this->srv.isPersonHealthy(month_as_int)) {
        std::cout << "Good job! The person is healthy.\n";
    }
    else {
        std::cout << "Careful! The person is not healthy.\n";
    }
}

void UI::ui_save_to_file() {
    std::string file_name, date;
    std::cout << "\nGive file name: ";
    std::cin >> file_name;
    std::cout << "\nGive date: ";
    std::cin >> date;
    this->srv.srv_save(file_name, date);
    std::cout << "\nData saved.\n";
}


void UI::start() {
    std::string cmd;
    int cmd_as_int;
    while (true) {
        this->print_menu();
        std::cout << "Give your command: ";
        std::cin >> cmd;
        cmd_as_int = std::atoi(cmd.c_str());
        try{
            if (cmd_as_int == 1) {
                this->ui_addMeasurement();
            }
            else if (cmd_as_int == 2) {
                this->ui_print_all_measurements();
            }
            else if (cmd_as_int == 3) {
                this->ui_is_healthy();
            }
            else if (cmd_as_int == 4) {
                this->ui_save_to_file();
            }
            else if (cmd_as_int == 5) {
                break;
            }
        }
        catch (std::runtime_error& e) {
            std::cout << e.what();
        }
        std::cout << "\n\n";
    }
}






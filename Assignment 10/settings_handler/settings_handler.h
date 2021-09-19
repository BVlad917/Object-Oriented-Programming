//
// Created by VladB on 10-May-21.
//

#ifndef A67_BVLAD917_SETTINGS_HANDLER_H
#define A67_BVLAD917_SETTINGS_HANDLER_H


#include <string>

class SettingsHandler {
private:
    std::string settings_file;
    std::string store_repo_type;
    std::string store_repo_file;
    std::string basket_repo_type;
    std::string basket_repo_file;
    std::string ui_type;
    bool gui = false;
    void set_properties();
    void check_validity();

public:
    explicit SettingsHandler(std::string settings_file);

    std::string get_store_repo_type() const { return this->store_repo_type; }

    std::string get_store_repo_file() const { return this->store_repo_file; }

    std::string get_basket_repo_type() const { return this->basket_repo_type; }

    std::string get_basket_repo_file() const { return this->basket_repo_file; }

    bool is_gui() const { return this->gui; }
};


#endif //A67_BVLAD917_SETTINGS_HANDLER_H

//
// Created by VladB on 10-May-21.
//

#include <vector>
#include <fstream>
#include "settings_handler.h"
#include "../persistency/file_repo.h"
#include "../errors/exceptions.h"

SettingsHandler::SettingsHandler(std::string settings_file) : settings_file(std::move(settings_file)) {
    this->set_properties();
    this->check_validity();
}

void SettingsHandler::set_properties() {
    std::string line;
    std::vector<std::string> split_line;
    std::ifstream fin("settings.properties");
    if (!fin.good()) {
        throw SettingsException{"ERROR: Could not open settings file.\n"};
    }
    while (std::getline(fin, line)) {
        split_line = FileRepo::tokenize(line, ' ');
        // If the current line is a comment, then this line is skipped
        if (split_line.size() < 2 || split_line[0] == "#") {
            continue;
        }

        if (split_line[0] == "store_repository_type") {
            this->store_repo_type = split_line[2];
        } else if (split_line[0] == "store_repository_file") {
            this->store_repo_file = split_line[2];
        } else if (split_line[0] == "basket_repository_type") {
            this->basket_repo_type = split_line[2];
        } else if (split_line[0] == "basket_repository_file") {
            this->basket_repo_file = split_line[2];
        } else if (split_line[0] == "ui") {
            this->ui_type = split_line[2];
            if (split_line[2] == "GUI") {
                this->gui = true;
            }
        }
    }
}

void SettingsHandler::check_validity() {
    // Check that everything was set
    if (this->store_repo_type.empty()) {
        throw SettingsException{"ERROR: The settings file does not provide store repository type.\n"};
    }
    if (this->store_repo_file.empty()) {
        throw SettingsException{"ERROR: The settings file does not provide store repository file.\n"};
    }
    if (this->basket_repo_type.empty()) {
        throw SettingsException{"ERROR: The settings file does not provide basket repository type.\n"};
    }
    if (this->basket_repo_file.empty()) {
        throw SettingsException{"ERROR: The settings file does not provide basket repository file.\n"};
    }
    // Check that the set values are valid values
    if (this->store_repo_type != "database" && this->basket_repo_type != "text" && this->basket_repo_type != "inmemory") {
        throw SettingsException{"ERROR: Invalid store repository type provided in the settings file.\n"};
    }
    if (this->basket_repo_type != "CSV" && this->basket_repo_type != "HTML") {
        throw SettingsException{"ERROR: Invalid basket repository type provided in the settings file.\n"};
    }
    if (this->ui_type != "console" && this->ui_type != "GUI") {
        throw SettingsException{"ERROR: Invalid UI type provided in the settings file.\n"};
    }
}



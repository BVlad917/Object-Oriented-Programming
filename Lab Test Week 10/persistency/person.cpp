//
// Created by VladB on 26-Apr-21.
//

#include "person.h"

#include <utility>
#include <sstream>
#include <fstream>

Person::Person(std::string name) : name(std::move(name)) {}

void Person::addMeasurement(Measurement *m) {
    this->measurements.push_back(m);
}

std::vector<Measurement *> Person::getAllMeasurements() {
    return this->measurements;
}

std::vector<Measurement *> Person::getMeasurementsByMonth(int month) {
    std::vector<Measurement *> filtered;
    for (Measurement *m: this->measurements) {
        int month_as_int;
        if (std::stoi(m->getDate().substr(5, 1)) == 0) {
            month_as_int = std::stoi(m->getDate().substr(6, 1));
        } else {
            month_as_int = std::stoi(m->getDate().substr(5, 2));
        }
        if (month_as_int == month) {
            filtered.push_back(m);
        }
    }
    return filtered;
}

bool Person::isHealthy(int month) {
    for (Measurement *m: this->measurements) {
        int month_as_int;
        if (std::stoi(m->getDate().substr(5, 1)) == 0) {
            month_as_int = std::stoi(m->getDate().substr(6, 1));
        } else {
            month_as_int = std::stoi(m->getDate().substr(5, 2));
        }
        if (month == 1) {
            if (month_as_int == 1) {
                if (!m->isNormalValue()) {
                    return false;
                }
            }
        } else {
            if (month_as_int == month || month_as_int == month - 1) {
                if (!m->isNormalValue()) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::vector<std::string> tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::vector<Measurement *> Person::getMeasurementsNewerThanDate(std::string date) {
    std::vector<Measurement *> filtered;
    std::vector<std::string> given_date_vec, date_vec;

    for (Measurement *m: this->measurements) {
        if (strcmp(date.c_str(), m->getDate().c_str()) > 0){
            filtered.push_back(m);
        }
    }
    return filtered;
}

void Person::writeToFile(std::string filename, std::string date) {
    std::vector<Measurement*> all_m = this->getMeasurementsNewerThanDate(date);
    std::ofstream fout(filename);
    for (Measurement* m: all_m) {
        fout << m->toString() << "\n";
    }
}

std::string Person::getPersonName() {
    return this->name;
}

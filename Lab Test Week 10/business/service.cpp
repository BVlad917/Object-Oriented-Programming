//
// Created by VladB on 26-Apr-21.
//

#include <stdexcept>
#include "service.h"

Service::Service(Person &p): p(p) {}

void Service::srv_addMeasurement(Measurement *new_m) {
    if (new_m->getDate().length() != 10) {
        throw std::runtime_error("Invalid date given.\n");
        delete new_m;
    }
    this->p.addMeasurement(new_m);
}

std::vector<Measurement *> Service::getAllMeasurements() {
    return this->p.getAllMeasurements();
}

std::string Service::srvGetPersonName() {
    return this->p.getPersonName();
}

bool Service::isPersonHealthy(int month) {
    return this->p.isHealthy(month);
}

void Service::srv_save(std::string file_name, std::string date) {
    this->p.writeToFile(file_name, date);
}



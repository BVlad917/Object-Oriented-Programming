//
// Created by VladB on 26-Apr-21.
//

#ifndef T2_BVLAD917_1_SERVICE_H
#define T2_BVLAD917_1_SERVICE_H


#include "../persistency/person.h"

class Service {
private:
    Person& p;

public:
    explicit Service(Person& p);

    void srv_addMeasurement(Measurement* new_m);

    std::vector<Measurement*> getAllMeasurements();

    std::string srvGetPersonName();

    bool isPersonHealthy(int month);

    void srv_save(std::string file_name, std::string date);
};


#endif //T2_BVLAD917_1_SERVICE_H

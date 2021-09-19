//
// Created by VladB on 26-Apr-21.
//

#ifndef T2_BVLAD917_1_PERSON_H
#define T2_BVLAD917_1_PERSON_H


#include <vector>
#include <string>
#include "../domain/measurement.h"

class Person {
private:
    std::string name;
    std::vector<Measurement*> measurements;

public:
    explicit Person(std::string name);

    void addMeasurement(Measurement* m);

    std::vector<Measurement*> getAllMeasurements();

    std::vector<Measurement*> getMeasurementsByMonth(int month);

    bool isHealthy(int month);

    std::vector<Measurement*> getMeasurementsNewerThanDate(std::string date);

    void writeToFile(std::string filename, std::string date);

    std::string getPersonName();
};


#endif //T2_BVLAD917_1_PERSON_H

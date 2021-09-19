//
// Created by VladB on 26-Apr-21.
//

#ifndef T2_BVLAD917_1_BMI_H
#define T2_BVLAD917_1_BMI_H


#include "measurement.h"

class BMI: public Measurement {
private:
    double value;

public:
    BMI(std::string date, double value);

    bool isNormalValue() override;

    std::string toString() override;

    std::string getDate() override;
};


#endif //T2_BVLAD917_1_BMI_H

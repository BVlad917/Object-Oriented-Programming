//
// Created by VladB on 26-Apr-21.
//

#ifndef T2_BVLAD917_1_BP_H
#define T2_BVLAD917_1_BP_H


#include "measurement.h"

class BP: public Measurement {
private:
    int systolicValue;
    int diastolicValue;

public:
    BP(std::string date, int sys_value, int dis_value);

    bool isNormalValue() override;

    std::string toString() override;

    std::string getDate() override;
};


#endif //T2_BVLAD917_1_BP_H

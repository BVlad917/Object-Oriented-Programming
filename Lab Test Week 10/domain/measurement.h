//
// Created by VladB on 26-Apr-21.
//

#ifndef T2_BVLAD917_1_MEASUREMENT_H
#define T2_BVLAD917_1_MEASUREMENT_H


#include <string>

class Measurement {
protected:
    std::string date;

public:
    virtual bool isNormalValue() = 0;

    virtual std::string toString() = 0;

    virtual std::string getDate() = 0;

    virtual ~Measurement() = default;
};


#endif //T2_BVLAD917_1_MEASUREMENT_H

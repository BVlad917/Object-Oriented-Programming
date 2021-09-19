//
// Created by VladB on 26-Apr-21.
//

#include "bmi.h"

#include <utility>

BMI::BMI(std::string date, double value) {
    this->date = std::move(date);
    this->value = value;
}

bool BMI::isNormalValue() {
    return this->value >= 18.5 && this->value <= 25;
}

std::string BMI::toString() {
    return this->date + ", BMI, " + std::to_string(this->value);
}

std::string BMI::getDate() {
    return this->date;
}

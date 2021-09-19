//
// Created by VladB on 26-Apr-21.
//

#include "bp.h"

#include <utility>

bool BP::isNormalValue() {
    return this->systolicValue >= 90 && this->systolicValue <= 119 && this->diastolicValue >= 60 && this->diastolicValue <= 79;
}

std::string BP::toString() {
    return this->date + ", BP, systolic value  " + std::to_string(this->systolicValue) + ", diastolic value " + std::to_string(this->diastolicValue);
}

BP::BP(std::string date, int sys_value, int dis_value) {
    this->date = std::move(date);
    this->systolicValue = sys_value;
    this->diastolicValue = dis_value;
}

std::string BP::getDate() {
    return this->date;
}

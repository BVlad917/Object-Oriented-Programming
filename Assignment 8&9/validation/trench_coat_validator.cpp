//
// Created by VladB on 20-Mar-21.
//

#include "trench_coat_validator.h"
#include "../errors/exceptions.h"

void TrenchCoatValidator::validate(TrenchCoat &t) {
    std::string error;
    if (t.get_trench_size() != "XXS" && t.get_trench_size() != "XS" && t.get_trench_size() != "S"
    && t.get_trench_size() != "M" && t.get_trench_size() != "L" && t.get_trench_size() != "XL"
    && t.get_trench_size() != "XXL" && t.get_trench_size() != "XXXL" && t.get_trench_size() != "XXXXL"
    && t.get_trench_size() != "XXXXXL") {
        if (error.length() == 0) error += "\n";
        error += "Invalid size given.\n";
    }
    if (t.get_trench_colour().length() == 0) {
        if (error.length() == 0) error += "\n";
        error += "Invalid colour given.\n";
    }
    if (t.get_trench_price() <= 0) {
        if (error.length() == 0) error += "\n";
        error += "Invalid price given.\n";
    }
    if (t.get_trench_quantity() <= 0) {
        if (error.length() == 0) error += "\n";
        error += "Invalid quantity given.\n";
    }
    if (t.get_trench_photograph().length() == 0) {
        if (error.length() == 0) error += "\n";
        error += "Invalid photograph link given.\n";
    }
    if (error.length() > 0) {
        if (error.length() == 0) error += "\n";
        throw ValidationException(error);
    }
}

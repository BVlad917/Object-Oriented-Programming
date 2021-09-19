//
// Created by VladB on 20-Mar-21.
//

#include <cassert>
#include "validation_tests.h"
#include "../domain/trench_coat.h"
#include "../validation/trench_coat_validator.h"
#include "../errors/exceptions.h"

void ValidationTests::test_trench_coat_validator() {
    TrenchCoat t1("xxl", "black", 200.23, 100, "link1");
    TrenchCoatValidator::validate(t1);
    assert(true);
    t1 = TrenchCoat("mnp", "black", 200.23, 100, "link1");
    try {
        TrenchCoatValidator::validate(t1);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }

    t1 = TrenchCoat("xl", "", 200.23, 100, "link1");
    try {
        TrenchCoatValidator::validate(t1);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }

    t1 = TrenchCoat("xl", "beige", -200.23, 100, "link1");
    try {
        TrenchCoatValidator::validate(t1);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }

    t1 = TrenchCoat("xl", "brown", 200.23, -100, "link1");
    try {
        TrenchCoatValidator::validate(t1);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }

    t1 = TrenchCoat("s", "green", 200.23, 100, "");
    try {
        TrenchCoatValidator::validate(t1);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }
}

void ValidationTests::run_all_validation_tests() {
    test_trench_coat_validator();
}

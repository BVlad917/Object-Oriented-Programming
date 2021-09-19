//
// Created by VladB on 19-Mar-21.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

#include "domain_tests.h"
#include "../domain/trench_coat.h"

void DomainTests::test_trench_getters() {
    TrenchCoat t1("xxl", "blUe", 17.5, 30, "link");
    assert(t1.get_trench_size() == "XXL");
    assert(t1.get_trench_colour() == "Blue");
    assert(fabs(t1.get_trench_price() - 17.5) < 0.00001);
    assert(t1.get_trench_quantity() == 30);
    assert(t1.get_trench_photograph() == "link");
}

void DomainTests::test_trench_operators() {
    TrenchCoat t1("xxl", "blUe", 17.5, 30, "link");
    TrenchCoat t2("XXL", "blue", 20.4, 88, "other_link");
    assert(t1 == t2);
    TrenchCoat t3("Xxl", "Red", 139, 90, "link2");
    assert(t1 != t3);
    assert(t2 != t3);
}

void DomainTests::test_trench_output() {
    TrenchCoat t1("xxl", "blUe", 17.5, 30, "link");
    std::ostringstream out;
    out << t1;
    assert(out.str() == "XXL,Blue,17.5,30,link");
}

void DomainTests::run_all_domain_tests() {
    test_trench_getters();
    test_trench_operators();
    test_trench_output();
}


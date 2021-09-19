//
// Created by VladB on 19-Mar-21.
//

#include <iostream>
#include <cassert>
#include "dynamic_array_tests.h"
#include "../dynamic_array/dynamic_array.h"
#include "../errors/exceptions.h"

void DynamicArrayTests::test_da_add_and_update() {
    DynamicArray da;
    assert(da.get_dynamic_array_size() == 0);
    TrenchCoat t1("xxl", "black", 175.99, 30, "link1");
    TrenchCoat t2("l", "green", 145.99, 12, "link2");
    TrenchCoat t3("m", "white", 199.99, 5, "link3");
    da.add_to_dynamic_array(t1);
    da.add_to_dynamic_array(t2);
    da.add_to_dynamic_array(t3);
    assert(da.get_dynamic_array_size() == 3);
    assert(da.find_position_of_elem(t2) == 1);
    TrenchCoat t4("s", "brown", 150, 13, "link4");
    assert(da.find_position_of_elem(t4) == -1);
    da.update_elem_in_dynamic_array(t4, 2);
    assert(da[2] == t4);
    try {
        da.update_elem_in_dynamic_array(t4, 3);
        assert(false);
    }
    catch (DynamicArrayException& e) {
        assert(true);
    }
}

void DynamicArrayTests::test_da_remove_and_find() {
    DynamicArray da;
    assert(da.get_dynamic_array_size() == 0);
    TrenchCoat t1("xxl", "black", 175.99, 30, "link1");
    TrenchCoat t2("l", "green", 145.99, 12, "link2");
    TrenchCoat t3("m", "white", 199.99, 5, "link3");
    da.add_to_dynamic_array(t1);
    da.add_to_dynamic_array(t2);
    da.add_to_dynamic_array(t3);
    assert(da.get_dynamic_array_size() == 3);
    assert(da.remove_elem_from_dynamic_array(t2) == true);
    assert(da.get_dynamic_array_size() == 2);
    assert(da.find_position_of_elem(t2) == -1);
    da.remove_elem_from_position_in_dynamic_array(0);
    assert(da.get_dynamic_array_size() == 1);
    assert(da.find_position_of_elem(t1) == -1);
    try {
        da.remove_elem_from_position_in_dynamic_array(4);
        assert(false);
    }
    catch (std::exception&) {
        assert(true);
    }
}

void DynamicArrayTests::test_da_get_elements() {
    DynamicArray da;
    assert(da.get_dynamic_array_size() == 0);
    TrenchCoat t1("xxl", "black", 175.99, 30, "link1");
    TrenchCoat t2("l", "green", 145.99, 12, "link2");
    TrenchCoat t3("m", "white", 199.99, 5, "link3");
    da.add_to_dynamic_array(t1);
    da.add_to_dynamic_array(t2);
    da.add_to_dynamic_array(t3);
    assert(da.get_dynamic_array_size() == 3);
    TrenchCoat *elems = da.get_dynamic_array_elements();
    assert(elems[0] == t1);
    assert(elems[1] == t2);
    assert(elems[2] == t3);
    try {
        da[3];
        assert(false);
    }
    catch (DynamicArrayException& e) {
        assert(true);
    }
}

void DynamicArrayTests::test_da_resize() {
    DynamicArray da;
    assert(da.get_dynamic_array_size() == 0);
    TrenchCoat t1("xxl", "black", 175.99, 30, "link1");
    TrenchCoat t2("l", "green", 145.99, 12, "link2");
    TrenchCoat t3("m", "white", 199.99, 5, "link3");
    TrenchCoat t4("sm", "beige", 100, 7, "link4");
    TrenchCoat t5("ml", "purple", 123.23, 19, "link5");
    da.add_to_dynamic_array(t1);
    da.add_to_dynamic_array(t2);
    da.add_to_dynamic_array(t3);
    da.add_to_dynamic_array(t4);
    assert(da.get_dynamic_array_size() == 4);
    assert(da.get_dynamic_array_capacity() == INITIAL_CAPACITY);
    da.add_to_dynamic_array(t5);
    assert(da.get_dynamic_array_size() == 5);
    assert(da.get_dynamic_array_capacity() == INITIAL_CAPACITY * CAPACITY_MULTIPLIER);
    assert(da.remove_elem_from_dynamic_array(t1) == true);
    assert(da.get_dynamic_array_size() == 4);
    assert(da.get_dynamic_array_capacity() == INITIAL_CAPACITY * CAPACITY_MULTIPLIER);
    assert(da.remove_elem_from_dynamic_array(t1) == false);
}

void DynamicArrayTests::test_da_assignment_operator() {
    TrenchCoat t1("xxl", "black", 209.32, 31, "link1");
    TrenchCoat t2("m", "grey", 250.64, 13, "link2");
    TrenchCoat t3("s", "white", 289.96, 5, "link3");
    DynamicArray da;
    da.add_to_dynamic_array(t1);
    da.add_to_dynamic_array(t2);
    da.add_to_dynamic_array(t3);
    DynamicArray copy;
    copy = da;
    assert(copy[0] == t1);
    assert(copy[1] == t2);
    assert(copy[2] == t3);
    assert(copy.get_dynamic_array_size() == 3);
    assert(copy.get_dynamic_array_capacity() == da.get_dynamic_array_capacity());
    // Test that the edge case with self assignment is handled
    copy = copy;
    assert(copy[0] == t1);
    assert(copy[1] == t2);
    assert(copy[2] == t3);
    assert(copy.get_dynamic_array_size() == 3);
    assert(copy.get_dynamic_array_capacity() == da.get_dynamic_array_capacity());
    // Test the copy constructor
    DynamicArray a = copy;
    assert(a[0] == t1);
    assert(a[1] == t2);
    assert(a[2] == t3);
    assert(a.get_dynamic_array_size() == 3);
    assert(a.get_dynamic_array_capacity() == da.get_dynamic_array_capacity());
}

void DynamicArrayTests::run_all_dynamic_array_tests() {
    test_da_add_and_update();
    test_da_remove_and_find();
    test_da_get_elements();
    test_da_resize();
    test_da_assignment_operator();

}









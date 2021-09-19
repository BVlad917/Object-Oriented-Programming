//
// Created by VladB on 27-Mar-21.
//

#include "templated_dynamic_vector_tests.h"
#include "../dynamic_array/dynamic_vector.h"

#include <cassert>
#include <iostream>

void TemplatedDynamicVectorTests::test_tdv_for_ints() {
    DynamicVector<int> a{2};
    a.add_to_dynamic_vector(3);
    a.add_to_dynamic_vector(4);
    a.add_to_dynamic_vector(5);
    assert(a.get_dynamic_vector_size() == 3);
    assert(a.get_dynamic_vector_capacity() == 2 * CAPACITY_MULTIPLIER);
    assert(a.remove_elem_from_dynamic_vector(3) == true);
    assert(a.find_position_of_elem(3) == -1);
    assert(a[1] == 5);
    a.remove_elem_from_position_in_dynamic_vector(1);
    assert(a.get_dynamic_vector_size() == 1);
    assert(a[0] == 4);
    a.update_elem_in_dynamic_vector(10, 0);
    assert(a[0] == 10);
}

void TemplatedDynamicVectorTests::test_copy_constructor() {
    DynamicVector<TrenchCoat> vector;
    vector.add_to_dynamic_vector(TrenchCoat("xxl", "blue", 123.23, 13, "link1"));
    vector.add_to_dynamic_vector(TrenchCoat("m", "beige", 145.99, 3, "link2"));
    assert(vector.get_dynamic_vector_size() == 2);
    DynamicVector<TrenchCoat> copy = vector;
    assert(copy.get_dynamic_vector_size() == vector.get_dynamic_vector_size());
    assert(copy.get_dynamic_vector_capacity() == vector.get_dynamic_vector_capacity());
    assert(copy.get_dynamic_vector_elements() != vector.get_dynamic_vector_elements());
    assert(copy.find_position_of_elem(TrenchCoat("xxl", "blue", 1, 1, "")) != -1);
    assert(copy.find_position_of_elem(TrenchCoat("m", "beige", 1, 1, "")) != -1);
}

void TemplatedDynamicVectorTests::test_assignment_operator() {
    DynamicVector<TrenchCoat> vector;
    vector.add_to_dynamic_vector(TrenchCoat("xxl", "blue", 123.23, 13, "link1"));
    vector.add_to_dynamic_vector(TrenchCoat("m", "beige", 145.99, 3, "link2"));
    assert(vector.get_dynamic_vector_size() == 2);
    DynamicVector<TrenchCoat> copy;
    copy = vector;
    assert(copy.get_dynamic_vector_size() == vector.get_dynamic_vector_size());
    assert(copy.get_dynamic_vector_capacity() == vector.get_dynamic_vector_capacity());
    assert(copy.get_dynamic_vector_elements() != vector.get_dynamic_vector_elements());
    assert(copy.find_position_of_elem(TrenchCoat("xxl", "blue", 1, 1, "")) != -1);
    assert(copy.find_position_of_elem(TrenchCoat("m", "beige", 1, 1, "")) != -1);
    copy = copy;
    assert(copy.get_dynamic_vector_size() == vector.get_dynamic_vector_size());
    assert(copy.get_dynamic_vector_capacity() == vector.get_dynamic_vector_capacity());
    assert(copy.get_dynamic_vector_elements() != vector.get_dynamic_vector_elements());
    assert(copy.find_position_of_elem(TrenchCoat("xxl", "blue", 1, 1, "")) != -1);
    assert(copy.find_position_of_elem(TrenchCoat("m", "beige", 1, 1, "")) != -1);
}

void TemplatedDynamicVectorTests::test_remove_trench_coat() {
    DynamicVector<TrenchCoat> vector;
    vector.add_to_dynamic_vector(TrenchCoat("xxl", "blue", 123.23, 13, "link1"));
    vector.add_to_dynamic_vector(TrenchCoat("m", "beige", 145.99, 3, "link2"));
    assert(vector.get_dynamic_vector_size() == 2);
    assert(vector.remove_elem_from_dynamic_vector(TrenchCoat("xxl", "blue", 123, 1, "")) == true);
    assert(vector.get_dynamic_vector_size() == 1);
    assert(vector.remove_elem_from_dynamic_vector(TrenchCoat("xxl", "blue", 123, 1, "")) == false);
    assert(vector.get_dynamic_vector_size() == 1);
    try {
        vector.remove_elem_from_position_in_dynamic_vector(1);
        assert(false);
    }
    catch (DynamicArrayException&) {
        assert(true);
    }
    vector.remove_elem_from_position_in_dynamic_vector(0);
    assert(vector.get_dynamic_vector_size() == 0);
}

void TemplatedDynamicVectorTests::test_update_elem_in_dynamic_vector() {
    DynamicVector<TrenchCoat> vector;
    vector.add_to_dynamic_vector(TrenchCoat("xxl", "blue", 123.23, 13, "link1"));
    vector.add_to_dynamic_vector(TrenchCoat("m", "beige", 145.99, 3, "link2"));
    assert(vector.get_dynamic_vector_size() == 2);
    vector.update_elem_in_dynamic_vector(TrenchCoat("l", "green", 101.1, 9, "link3"), 0);
    assert(vector.find_position_of_elem(TrenchCoat("xxl", "blue", 123.23, 13, "link1")) == -1);
    assert(vector.find_position_of_elem(TrenchCoat("l", "green", 101.1, 9, "link3")) != -1);
    assert(vector.get_dynamic_vector_size() == 2);
    try {
        vector.update_elem_in_dynamic_vector(TrenchCoat("xs", "black", 109.19, 10, "link4"), 9);
        assert(false);
    }
    catch (DynamicArrayException&) {
        assert(true);
    }
}

void TemplatedDynamicVectorTests::test_tdv_for_trench_coats() {
    DynamicVector<TrenchCoat> vector;
    vector.add_to_dynamic_vector(TrenchCoat("xxl", "blue", 123.23, 13, "link1"));
    vector.add_to_dynamic_vector(TrenchCoat("m", "beige", 145.99, 3, "link2"));
    assert(vector.get_dynamic_vector_size() == 2);
    TrenchCoat t = vector[0];
    assert(t.get_trench_photograph() == "link1");
    try {
        vector[3];
        assert(false);
    }
    catch (DynamicArrayException&) {
        assert(true);
    }
}

void TemplatedDynamicVectorTests::test_dv_iterator() {
    DynamicVector<TrenchCoat> vector;
    vector.add_to_dynamic_vector(TrenchCoat("xxl", "blue", 123.23, 13, "link1"));
    vector.add_to_dynamic_vector(TrenchCoat("m", "beige", 145.99, 3, "link2"));
    vector.add_to_dynamic_vector(TrenchCoat("s", "red", 209.99, 7, "link3"));
    assert(vector.get_dynamic_vector_size() == 3);
    auto it = vector.begin();
    int cnt = 0;
    while (it != vector.end()) {
        cnt += 1;
        it++;
    }
    assert(cnt == 3);
    it = vector.begin();
    assert(it->get_trench_colour() == "Blue");
    std::string col = (++it)->get_trench_colour();
    assert(col == "Beige");
    it++;
    assert(it->get_trench_colour() == "Red");
    it++;
    assert(it == vector.end());
    // Test the clear function
    vector.clear_dynamic_vector();
    assert(vector.get_dynamic_vector_size() == 0);
    assert(vector.get_dynamic_vector_capacity() == INITIAL_CAPACITY);
}

void TemplatedDynamicVectorTests::run_all_tdv_tests() {
    test_tdv_for_ints();
    test_copy_constructor();
    test_assignment_operator();
    test_remove_trench_coat();
    test_update_elem_in_dynamic_vector();
    test_tdv_for_trench_coats();
    test_dv_iterator();
}

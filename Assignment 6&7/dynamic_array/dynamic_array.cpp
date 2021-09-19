//
// Created by VladB on 19-Mar-21.
//

#include "dynamic_array.h"

#include "../errors/exceptions.h"

DynamicArray::DynamicArray() {
    this->size = 0;
    this->capacity = INITIAL_CAPACITY;
    this->elements = new TElem[INITIAL_CAPACITY];
}

DynamicArray::DynamicArray(const DynamicArray &other): size(other.size), capacity(other.capacity) {
    this->elements = new TElem[other.capacity];
    for (int i = 0; i < other.size; i++) {
        this->elements[i] = other.elements[i];
    }
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
    if (this == &other) {
        return *this;
    }
    this->size = other.size;
    this->capacity = other.capacity;
    for (int i = 0; i < other.size; i++) {
        this->elements[i] = other.elements[i];
    }
    return *this;
}

TElem &DynamicArray::operator[](int position) {
    if (position < 0 || position >= this->size) {
        throw DynamicArrayException("\nInvalid position given.\n");
    }
    return this->elements[position];
}


void DynamicArray::resize_dynamic_array() {
    this->capacity *= CAPACITY_MULTIPLIER;
    auto *new_dynamic_array = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++) {
        new_dynamic_array[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = new_dynamic_array;
}

int DynamicArray::get_dynamic_array_size() const {
    return this->size;
}

TElem *DynamicArray::get_dynamic_array_elements() {
    return this->elements;
}

void DynamicArray::add_to_dynamic_array(TElem t) {
    if (this->size == this->capacity) {
        this->resize_dynamic_array();
    }
    this->elements[this->size] = std::move(t);
    this->size += 1;
}

bool DynamicArray::remove_elem_from_dynamic_array(const TElem& t) {
    int i;
    for (i = 0; i < this->size; i++) {
        if (this->elements[i] == t) {
            break;
        }
    }
    // If we reached the end of the dynamic array without finding the element, that means that the
    // element is not in the dynamic array
    if (i == this->size) {
        return false;
    }
    // If not, we remove it
    this->elements[i] = this->elements[this->size - 1];
    this->size -= 1;
    return true;
}

void DynamicArray::remove_elem_from_position_in_dynamic_array(int position) {
    if (position < 0 || position >= this->size) {
        throw DynamicArrayException("\nInvalid position given.\n");
    }
    this->elements[position] = this->elements[this->size - 1];
    this->size -= 1;
}

int DynamicArray::find_position_of_elem(TElem t) {
    for (int i = 0; i < this->size; i++) {
        if (this->elements[i] == t) {
            return i;
        }
    }
    return -1;
}

void DynamicArray::update_elem_in_dynamic_array(TElem new_t, int position) {
    if (position < 0 || position >= this->size) {
        throw DynamicArrayException("\nInvalid position given.\n");
    }
    this->elements[position] = std::move(new_t);
}

int DynamicArray::get_dynamic_array_capacity() const {
    return this->capacity;
}

DynamicArray::~DynamicArray() {
    delete[] this->elements;
}



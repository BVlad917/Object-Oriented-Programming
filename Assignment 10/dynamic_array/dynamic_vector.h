//
// Created by VladB on 27-Mar-21.
//

#ifndef A45_BVLAD917_DYNAMIC_VECTOR_H
#define A45_BVLAD917_DYNAMIC_VECTOR_H

#include <iterator>
#include <cstddef>

#include "../errors/exceptions.h"
#include "../domain/trench_coat.h"

#define INITIAL_CAPACITY 4
#define CAPACITY_MULTIPLIER 2

template<typename T>
class DynamicVector {
private:
    int size;
    int capacity;
    T *elems;

    void resize_dynamic_vector();

public:
    /*
        Default Dynamic Array constructor.
     */
    explicit DynamicVector(int capacity = INITIAL_CAPACITY);

    /*
        Copy constructor overloading.
    */
    DynamicVector(const DynamicVector &other);

    /*
        Assignment constructor overloading.
     */
    DynamicVector &operator=(const DynamicVector &other);

    /*
        Subscript [] operator overloading.
     */
    T &operator[](int position);

    /*
        Return the array's current number of elements.
     */
    int get_dynamic_vector_size() const;

    /*
        Return the array's current maximum capacity.
     */
    int get_dynamic_vector_capacity() const;

    /*
        Return the array's elements as a pointer to TElem.
     */
    T *get_dynamic_vector_elements();

    /*
        Return the position of an element in the array. Returns -1 if the element is not in the dynamic array.
     */
    int find_position_of_elem(T t);

    /*
        Add an element to the dynamic array.
     */
    void add_to_dynamic_vector(T t);

    /*
        Remove an element from the dynamic array. Returns true if the element was removed; false
        otherwise (if the element could not be found in the dynamic array)
     */
    bool remove_elem_from_dynamic_vector(T t);

    /*
        Remove an element from a position in the dynamic array.
        Throws: DynamicArrayException if the position is invalid.
     */
    void remove_elem_from_position_in_dynamic_vector(int position);

    /*
        Removes all the elements from the dynamic array.
     */
    void clear_dynamic_vector();

    /*
        Update an element from the dynamic array at a given position.
        Throws: DynamicArrayException if the position is invalid.
     */
    void update_elem_in_dynamic_vector(T new_t, int position);

    /*
        Iterator for the dynamic vector.
     */
    class iterator {
    private:
        T *m_ptr;
    public:
        explicit iterator(T *ptr) : m_ptr(ptr) {}

        T &operator*() const { return *m_ptr; }

        T *operator->() const { return m_ptr; }

        iterator &operator++() {    // Prefix increment (++it)
            m_ptr++;
            return *this;
        }

        iterator operator++(int) {  // Postfix increment (it++)
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const iterator &a, const iterator &b) { return a.m_ptr == b.m_ptr; }

        friend bool operator!=(const iterator &a, const iterator &b) { return a.m_ptr != b.m_ptr; }
    };

    /*
        Returns an iterator pointing to the first element from the dynamic vector.
     */
    iterator begin() { return iterator(&this->elems[0]); }

    /*
        Returns an iterator pointing to the last element from the dynamic vector.
     */
    iterator end() { return iterator(&this->elems[this->size]); }

    /*
        Dynamic array destructor.
     */
    ~DynamicVector();
};

template<typename T>
DynamicVector<T>::DynamicVector(int capacity): size(0), capacity(capacity) {
    this->elems = new T[capacity];
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector &other): size(other.size), capacity(other.capacity) {
    this->elems = new T[other.capacity];
    for (int i = 0; i < other.size; i++) {
        this->elems[i] = other.elems[i];
    }
}

template<typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector &other) {
    if (this == &other) {
        return *this;
    }
    this->size = other.size;
    this->capacity = other.capacity;
    for (int i = 0; i < other.size; i++) {
        this->elems[i] = other.elems[i];
    }
    return *this;
}

template<typename T>
void DynamicVector<T>::resize_dynamic_vector() {
    this->capacity *= CAPACITY_MULTIPLIER;
    auto *new_dynamic_vector = new T[this->capacity];
    for (int i = 0; i < this->size; i++) {
        new_dynamic_vector[i] = this->elems[i];
    }
    delete[] this->elems;
    this->elems = new_dynamic_vector;
}

template<typename T>
T &DynamicVector<T>::operator[](int position) {
    if (position < 0 || position >= this->size) {
        throw DynamicArrayException("\nInvalid position given.\n");
    }
    return this->elems[position];
}

template<typename T>
int DynamicVector<T>::get_dynamic_vector_size() const {
    return this->size;
}

template<typename T>
int DynamicVector<T>::get_dynamic_vector_capacity() const {
    return this->capacity;
}

template<typename T>
T *DynamicVector<T>::get_dynamic_vector_elements() {
    return this->elems;
}

template<typename T>
int DynamicVector<T>::find_position_of_elem(T t) {
    for (int i = 0; i < this->size; i++) {
        if (this->elems[i] == t) {
            return i;
        }
    }
    return -1;
}

template<typename T>
void DynamicVector<T>::add_to_dynamic_vector(T t) {
    if (this->size == this->capacity) {
        this->resize_dynamic_vector();
    }
    this->elems[this->size] = std::move(t);
    this->size += 1;
}

template<typename T>
bool DynamicVector<T>::remove_elem_from_dynamic_vector(T t) {
    int i;
    for (i = 0; i < this->size; i++) {
        if (this->elems[i] == t) {
            break;
        }
    }
    // If we reached the end of the dynamic array without finding the element, that means that the
    // element is not in the dynamic array
    if (i == this->size) {
        return false;
    }
    // If not, we remove it
    for (int j = i; j < this->size - 1; j++) {
        this->elems[j] = this->elems[j + 1];
    }
    this->size -= 1;
    return true;
}

template<typename T>
void DynamicVector<T>::remove_elem_from_position_in_dynamic_vector(int position) {
    if (position < 0 || position >= this->size) {
        throw DynamicArrayException("\nInvalid position given.\n");
    }
    for (int i = position; i < this->size - 1; i++) {
        this->elems[i] = this->elems[i + 1];
    }
    this->size -= 1;
}

template<typename T>
void DynamicVector<T>::update_elem_in_dynamic_vector(T new_t, int position) {
    if (position < 0 || position >= this->size) {
        throw DynamicArrayException("\nInvalid position given.\n");
    }
    this->elems[position] = std::move(new_t);
}


template<typename T>
void DynamicVector<T>::clear_dynamic_vector() {
    delete[] this->elems;
    this->elems = new T[INITIAL_CAPACITY];
    this->size = 0;
    this->capacity = INITIAL_CAPACITY;
}

template<typename T>
DynamicVector<T>::~DynamicVector() {
    delete[] this->elems;
}


#endif //A45_BVLAD917_DYNAMIC_VECTOR_H

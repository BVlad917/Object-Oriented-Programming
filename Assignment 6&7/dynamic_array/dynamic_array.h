//
// Created by VladB on 19-Mar-21.
//

#ifndef A45_BVLAD917_DYNAMIC_ARRAY_H
#define A45_BVLAD917_DYNAMIC_ARRAY_H

#include "../domain/trench_coat.h"

#define INITIAL_CAPACITY 4
#define CAPACITY_MULTIPLIER 2

typedef TrenchCoat TElem;

class DynamicArray {
private:
    int capacity, size;
    TElem *elements;

    void resize_dynamic_array();

public:
    /*
        Default Dynamic Array constructor.
     */
    DynamicArray();

    /*
        Copy constructor overloading.
     */
    DynamicArray(const DynamicArray &other);

    /*
        Assignment constructor overloading.
     */
    DynamicArray &operator=(const DynamicArray &other);

    /*
        Subscript [] operator overloading.
     */
    TElem &operator[](int position);

    /*
        Return the array's current number of elements.
     */
    int get_dynamic_array_size() const;

    /*
        Return the array's current maximum capacity.
     */
    int get_dynamic_array_capacity() const;

    /*
        Return the array's elements as a pointer to TElem.
     */
    TElem *get_dynamic_array_elements();

    /*
        Return the position of an element in the array. Returns -1 if the element is not in the dynamic array.
     */
    int find_position_of_elem(TElem t);

    /*
        Add an element to the dynamic array.
     */
    void add_to_dynamic_array(TElem t);

    /*
        Remove an element from the dynamic array. Returns true if the element was removed; false
        otherwise (if the element could not be found in the dynamic array)
     */
    bool remove_elem_from_dynamic_array(const TElem& t);

    /*
        Remove an element from a position in the dynamic array.
        Throws: DynamicArrayException if the position is invalid.
     */
    void remove_elem_from_position_in_dynamic_array(int position);

    /*
        Update an element from the dynamic array at a given position.
        Throws: DynamicArrayException if the position is invalid.
     */
    void update_elem_in_dynamic_array(TElem new_t, int position);

    /*
        Dynamic array destructor.
     */
    ~DynamicArray();
};


#endif //A45_BVLAD917_DYNAMIC_ARRAY_H

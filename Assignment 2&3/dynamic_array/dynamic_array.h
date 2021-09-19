//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_DYNAMIC_ARRAY_H
#define A23_BVLAD917_DYNAMIC_ARRAY_H

typedef void *TElem;

typedef struct {
    int capacity;
    int size;
    TElem *elems;
} DynamicArray;

/// Creates a dynamic array with the given capacity and returns a pointer to it
DynamicArray *create_dynamic_array(int capacity);

/// Frees the memory used by the dynamic array. Important to note that it will deallocate the memory taken
/// by the pointer to the elements and the pointer to the dynamic array, but it will not deallocate the elements
/// themselves.
void destroy_dynamic_array(DynamicArray *da);

/// Returns the current capacity (how many elements it can fit) of the dynamic array as an integer
int get_dynamic_array_capacity(DynamicArray *da);

/// Returns the current size (number of elements) of the dynamic array as an integer
int get_dynamic_array_size(DynamicArray *da);

/// Returns a pointer (**void) to the elements of the dynamic array. If these elements are to be used, type
/// casting is needed.
TElem *get_dynamic_array_elems(DynamicArray *da);

/// Resizes the dynamic array, multiplying its capacity by the capacity multiplier (2 by default). Used
/// when the capacity of the dynamic array is filled
void resize_dynamic_array(DynamicArray *da);

/// Adds a new generic element of type TElem (void*) to the dynamic array
void add_elem_to_dynamic_array(DynamicArray *da, TElem elem);

/// Deletes the element in the array from the given position
/// \return: an integer: 0 - if the element was successfully removed; -1 otherwise (if the given index is
/// too large or too small)
int delete_elem_from_position(DynamicArray *da, int index);

/// Inserts a generic element of type TElem (void*) to the dynamic array on the given position
/// \param da: pointer to Dynamic Array; the container where the element needs to be inserted
/// \param elem: TElem*; pointer to the element to be inserted
/// \param position: int; the position where the element should be included
/// \return an integer: 0 - if the element was successfully inserted; -1 otherwise (if the given index
/// is too large or too small)
int insert_elem_to_position(DynamicArray *da, TElem elem, int position);

/// Returns the element from the given position in the dynamic array
/// \param da: pointer to Dynamic Array; where the element is stored
/// \param position: integer; the position of the element we need
/// \return TElem (i.e., void*): the element from the given position, which is a pointer to void
TElem get_elem_from_position(DynamicArray *da, int position);

/// Returns a copy of the dynamic array. It performs a so called "shallow" copy. It doesn't actually copy each
/// element from the dynamic array into another one. Rather, it creates a new dynamic array and copies in it
/// the TElems (void*, pointers to void) of the original dynamic array. It only performs a shallow copy (and not
/// a deep copy) because the dynamic array has no way of knowing what type of elements are in it, so they cannot
/// be copied.
/// \return: pointer to the copied dynamic array
DynamicArray *get_shallow_copy_of_dynamic_array(DynamicArray *da);

#endif //A23_BVLAD917_DYNAMIC_ARRAY_H

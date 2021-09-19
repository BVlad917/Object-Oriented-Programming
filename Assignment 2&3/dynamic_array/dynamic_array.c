//
// Created by VladB on 07-Mar-21.
//

#include <stdlib.h>

#include "dynamic_array.h"

#define CAPACITY_MULTIPLIER 2

DynamicArray *create_dynamic_array(int capacity) {
    DynamicArray *da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = capacity;
    da->size = 0;
    da->elems = (TElem *) malloc(sizeof(TElem) * capacity);
    return da;
}

void destroy_dynamic_array(DynamicArray *da) {
    free(da->elems);
    free(da);
}

int get_dynamic_array_capacity(DynamicArray *da) {
    return da->capacity;
}

int get_dynamic_array_size(DynamicArray *da) {
    return da->size;
}

TElem *get_dynamic_array_elems(DynamicArray *da) {
    return da->elems;
}

void resize_dynamic_array(DynamicArray *da) {
    da->capacity = da->capacity * CAPACITY_MULTIPLIER;
    da->elems = (TElem *) realloc(da->elems, sizeof(TElem) * da->capacity);
}

void add_elem_to_dynamic_array(DynamicArray *da, TElem elem) {
    if (da->size == da->capacity) {
        resize_dynamic_array(da);
    }
    da->elems[da->size] = elem;
    da->size += 1;
}

int delete_elem_from_position(DynamicArray *da, int index) {
    int i;
    if (index < 0 || index >= da->size) {
        return -1;
    }
    for (i = index; i < da->size - 1; i++) {
        da->elems[i] = da->elems[i + 1];
    }
    da->size -= 1;
    return 0;
}

int insert_elem_to_position(DynamicArray *da, TElem elem, int position) {
    int i;
    if (position < 0 || position > da->size) {
        return -1;
    }
    if (da->size == da->capacity) {
        resize_dynamic_array(da);
    }
    for (i = da->size; i > position; i--) {
        da->elems[i] = da->elems[i - 1];
    }
    da->elems[position] = elem;
    da->size += 1;
    return 0;
}

TElem get_elem_from_position(DynamicArray *da, int position) {
    return da->elems[position];
}

DynamicArray *get_shallow_copy_of_dynamic_array(DynamicArray *da) {
    DynamicArray *copy_array = create_dynamic_array(da->capacity);
    copy_array->size = da->size;
    for (int i = 0; i < copy_array->size; i++) {
        copy_array->elems[i] = da->elems[i];
    }
    return copy_array;
}
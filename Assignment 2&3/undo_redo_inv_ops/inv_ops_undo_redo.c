//
// Created by VladB on 22-Mar-21.
//

#include <stdlib.h>
#include <string.h>

#include "inv_ops_undo_redo.h"

#define INITIAL_STACK_SIZE 2

Operation *create_operation(Product *p, char *type_of_op) {
    Operation *op = (Operation *) malloc(sizeof(Operation));
    Product *copy = create_product(get_product_name(p), get_product_category(p), get_product_quantity(p),
                                   get_product_expiration_day(p), get_product_expiration_month(p),
                                   get_product_expiration_year(p));
    op->product = copy;
    strcpy(op->operation_type, type_of_op);
    return op;
}

char* get_op_type(Operation *op) {
    return op->operation_type;
}

Product *get_op_product(Operation *op) {
    return op->product;
}

void destroy_op(Operation *op) {
    destroy_product(op->product);
    free(op);
}

UndoRedo *create_undo_redo() {
    UndoRedo *undo_redo = (UndoRedo *) malloc(sizeof(UndoRedo));
    undo_redo->undo_list = create_dynamic_array(INITIAL_STACK_SIZE);
    undo_redo->redo_list = create_dynamic_array(INITIAL_STACK_SIZE);
    return undo_redo;
}

void undo_add(UndoRedo *undo_redo, Product *p) {
    add_elem_to_dynamic_array(undo_redo->undo_list, create_operation(p, "delete"));
}

void undo_remove(UndoRedo *undo_redo, Product *p) {
    add_elem_to_dynamic_array(undo_redo->undo_list, create_operation(p, "add"));
}

void undo_update(UndoRedo *undo_redo, Product *p) {
    add_elem_to_dynamic_array(undo_redo->undo_list, create_operation(p, "update"));
}

Operation *get_last_undo(UndoRedo *undo_redo) {
    if (get_dynamic_array_size(undo_redo->undo_list) == 0) {
        return NULL;
    }
    return get_elem_from_position(undo_redo->undo_list, get_dynamic_array_size(undo_redo->undo_list) - 1);
}

DynamicArray *get_undo_list(UndoRedo *undo_redo) {
    return undo_redo->undo_list;
}

int get_undo_stack_length(UndoRedo *undo_redo) {
    return get_dynamic_array_size(undo_redo->undo_list);
}

void redo_add(UndoRedo *undo_redo, Product *p) {
    add_elem_to_dynamic_array(undo_redo->redo_list, create_operation(p, "delete"));
}

void redo_remove(UndoRedo *undo_redo, Product *p) {
    add_elem_to_dynamic_array(undo_redo->redo_list, create_operation(p, "add"));
}

void redo_update(UndoRedo *undo_redo, Product *p) {
    add_elem_to_dynamic_array(undo_redo->redo_list, create_operation(p, "update"));
}

Operation *get_last_redo(UndoRedo *undo_redo) {
    if (get_dynamic_array_size(undo_redo->redo_list) == 0) {
        return NULL;
    }
    return get_elem_from_position(undo_redo->redo_list, get_dynamic_array_size(undo_redo->redo_list) - 1);
}

DynamicArray *get_redo_list(UndoRedo *undo_redo) {
    return undo_redo->redo_list;
}

int get_redo_stack_length(UndoRedo *undo_redo) {
    return get_dynamic_array_size(undo_redo->redo_list);
}

void clear_undo_list(UndoRedo *undo_redo) {
    for (int i = get_dynamic_array_size(undo_redo->undo_list) - 1; i >= 0; i--) {
        destroy_op(get_elem_from_position(undo_redo->undo_list, i));
        delete_elem_from_position(undo_redo->redo_list, i);
    }
}

void clear_redo_list(UndoRedo *undo_redo) {
    for (int i = get_dynamic_array_size(undo_redo->redo_list) - 1; i >= 0; i--) {
        destroy_op(get_elem_from_position(undo_redo->redo_list, i));
        delete_elem_from_position(undo_redo->redo_list, i);
    }
}

void destroy_undo_redo(UndoRedo *undo_redo) {
    clear_undo_list(undo_redo);
    destroy_dynamic_array(undo_redo->undo_list);
    clear_redo_list(undo_redo);
    destroy_dynamic_array(undo_redo->redo_list);
    free(undo_redo);
}
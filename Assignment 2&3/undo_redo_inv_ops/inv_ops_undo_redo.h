//
// Created by VladB on 22-Mar-21.
//

#ifndef A23_BVLAD917_INV_OPS_UNDO_REDO_H
#define A23_BVLAD917_INV_OPS_UNDO_REDO_H

#include "../dynamic_array/dynamic_array.h"
#include "../domain/product.h"

typedef struct {
    Product* product;
    char operation_type[256];
}Operation;

typedef struct {
    DynamicArray* undo_list;
    DynamicArray* redo_list;
}UndoRedo;

Operation* create_operation(Product* p, char* type_of_op);

char* get_op_type(Operation *op);

Product *get_op_product(Operation *op);

void destroy_op(Operation *op);

UndoRedo* create_undo_redo();

void undo_add(UndoRedo *undo_redo, Product *p);

void undo_remove(UndoRedo *undo_redo, Product *p);

void undo_update(UndoRedo *undo_redo, Product *p);

Operation *get_last_undo(UndoRedo *undo_redo);

DynamicArray *get_undo_list(UndoRedo *undo_redo);

int get_undo_stack_length(UndoRedo *undo_redo);

void redo_add(UndoRedo *undo_redo, Product *p);

void redo_remove(UndoRedo *undo_redo, Product *p);

void redo_update(UndoRedo *undo_redo, Product *p);

int get_redo_stack_length(UndoRedo *undo_redo);

Operation *get_last_redo(UndoRedo *undo_redo);

DynamicArray *get_redo_list(UndoRedo *undo_redo);

void clear_undo_list(UndoRedo *undo_redo);

void clear_redo_list(UndoRedo *undo_redo);

void destroy_undo_redo(UndoRedo *undo_redo);

#endif //A23_BVLAD917_INV_OPS_UNDO_REDO_H

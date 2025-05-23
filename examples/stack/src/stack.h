/*
 * Stack module for int items.
 * Example of abstract data type (ADT).
 */
#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h>

// represents the type of data to be stored
typedef int Item;

// incomplete type used to hide the
// internal stack representation
typedef struct stack_type *Stack;

// allocate and release memory
Stack stack_create(void);
void stack_destroy(Stack s);

// stack operations
void stack_make_empty(Stack s);
bool stack_is_empty(Stack s);
bool stack_is_full(Stack s);
void stack_push(Stack s, Item i);
Item stack_pop(Stack s);

#endif

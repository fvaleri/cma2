#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// linked list node
struct node {
    Item data;
    struct node *next;
};

struct stack_type {
    struct node *top;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack stack_create(void) {
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL)
        terminate("Error in create: stack could not be created.");
    s->top = NULL;
    return s;
}

// calls make empty to release the memory
// occupied by the nodes in the linked list
void stack_destroy(Stack s) {
    stack_make_empty(s);
    free(s);
}

void stack_make_empty(Stack s) {
    while (!stack_is_empty(s))
        stack_pop(s);
}

bool stack_is_empty(Stack s) {
    return s->top == NULL;
}

bool stack_is_full(Stack s) {
    (void) s; // silent unused param
    return false;
}

void stack_push(Stack s, Item i) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
        terminate("Error in push: stack is full.");
    new_node->data = i;
    new_node->next = s->top;
    s->top = new_node;
}

Item stack_pop(Stack s) {
    struct node *old_top;
    Item i;

    if (stack_is_empty(s))
        terminate("Error in pop: stack is empty.");

    old_top = s->top;
    i = old_top->data;
    s->top = old_top->next;
    free(old_top);

    return i;
}

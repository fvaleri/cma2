#include <stdio.h>
#include "stack.h"

// using the Stack abstraction without knowledge
// of its internal representation
int main(void) {
    Stack s1, s2;
    int n;

    s1 = stack_create();
    s2 = stack_create();

    stack_push(s1, 1);
    stack_push(s1, 2);

    n = stack_pop(s1);
    printf("Popped %d from s1\n", n);
    stack_push(s2, n);
    n = stack_pop(s1);
    printf("Popped %d from s1\n", n);
    stack_push(s2, n);

    stack_destroy(s1);

    while (!stack_is_empty(s2))
        printf("Popped %d from s2\n", stack_pop(s2));

    stack_push(s2, 3);
    stack_make_empty(s2);
    if (stack_is_empty(s2))
        printf("s2 is empty\n");
    else
        printf("s2 is not empty\n");

    stack_destroy(s2);

    return 0;
}

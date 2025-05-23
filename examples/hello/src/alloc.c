#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

char *concat(const char *s1, const char *s2);

int main(void) {
    // dynamically allocated strings
    // each char is 1 byte and we need to include the null char
    char *p1 = malloc(N + 1);
    strcpy(p1, "hello");
    printf("%s\n", p1);
    // reclaim memory to avoid exhausting the heap
    // the pointer remains dangling and can't be used
    free(p1);

    char *p2 = concat("abc", "def");
    printf("%s\n", p2);
    free(p2);

    // dynamically allocated arrays
    // calloc also clears the memory setting all bits to zero
    int *p3 = calloc(N, sizeof(int));
    p3[1] = 33;
    p3 = realloc(p3, 2 * N);
    printf("%d\n", p3[1]);
    free(p3);

    // using calloc with 1 as its first arg,
    // we can allocate space for a data item of any type
    struct point { int x, y; } *p4;
    p4 = calloc(1, sizeof(struct point));
    printf("(%d, %d)\n", p4->x, p4->y);
    free(p4);
}

char *concat(const char *s1, const char *s2) {
    char *result;

    result = malloc(strlen(s1) + strlen(s2) + 1 );
    if (result == NULL) {
        printf("Error: malloc failed in concat\n");
        exit(EXIT_FAILURE);
    }

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

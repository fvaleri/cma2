#include <stdio.h>

# define N 10
# define NUM_ROWS 5
# define NUM_COLS 5

void hello_pointers(void);
void pointer_params(void);
void decompose(double x, long *int_part, double *frac_part);
void pointer_arithmetic(void);
void print_array(size_t n, const int a[n]);
int find_largest(size_t n, const int a[n]);
void print_matrix(size_t r, size_t c, const int m[r][c]);
void function_pointers(void);
int add(int a, int b);
int multiply(int a, int b);

int main(void) {
    hello_pointers();
    pointer_params();
    pointer_arithmetic();
    function_pointers();
    return 0;
}

void hello_pointers(void) {
    int i = 5;
    int *p = &i; // pointer to the memory address
    printf("variable content (i): %d\n", i);
    printf("variable address (&i): %p\n", (void *) &i);
    *p = 6; // *p is equivalent to i
    printf("modified content: %d\n", i);
}

void pointer_params(void) {
    double x, z;
    long y;
    x = 3.14159;
    decompose(x, &y, &z);
    printf("int part of %f: %ld\n", x, y);
    printf("frac part of %f: %.10f\n", x, z);
}

void decompose(double x, long *int_part, double *frac_part) {
    *int_part = (long) x;
    *frac_part = x - *int_part;
}

void pointer_arithmetic(void) {
    int arr[N] = {11, 34, 82, 7, 64, 98, 47, 18, 79, 20};
    int sum, *p;

    printf("----------------\n");
    print_array(N, arr);
    printf("\n----------------\n");
    printf("size: %ld bytes\n", sizeof(arr));

    // sum elements of an array
    sum = 0;
    for (int i = 0; i < N; i++)
        sum += arr[i];
    printf("sum: %d\n", sum);

    // sum elements of an array using pointers
    // integers used in pointer arithmetic are scaled depending on the type ot the pointer
    // if p is of type int *, then p +j = p + (4 * j), assuming int is stored with 4 bytes
    sum = 0;
    for (p = &arr[0]; p < &arr[N]; p++)
        sum += *p;
    printf("sum: %d\n", sum);

    // sum elements of an array using array name as pointer to the 1st element
    sum = 0;
    for (p = arr; p < arr + N; p++)
        sum += *p;
    printf("sum: %d\n", sum);

    // when passed to a function, an array name is always treated as a pointer
    printf("largest: %d\n", find_largest(N, arr));

    // C stores two-dimensional arrays in row-major order;
    // in other words, the elements of row 0 come first,
    // followed by the elements of row 1, and so forth
    int matrix[NUM_ROWS][NUM_COLS] = {{13, 54, 19, 56, 81},
                                      {43, 99, 76, 82, 64},
                                      {47, 59, 25, 17, 73},
                                      {34, 77, 94, 66, 43},
                                      {56, 78, 34, 56, 72}};

    printf("----------------\n");
    print_matrix(NUM_ROWS, NUM_COLS, matrix);
    printf("\n----------------\n");

    printf("size: %ld bytes\n", sizeof(matrix));

    int fla[NUM_ROWS];
    for (int i = 0; i < NUM_ROWS; i++)
        fla[i] = find_largest(NUM_COLS, matrix[i]);
    printf("largest: %d\n", find_largest(NUM_COLS, fla));
}

void print_array(size_t n, const int a[n]) {
    for (size_t i = 0; i < n; i++)
        printf(" %d", a[i]);
}

int find_largest(size_t n, const int a[n]) {
    int max = a[0];
    for (size_t i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max; //test
}

void print_matrix(size_t r, size_t c, const int m[r][c]) {
    for (size_t i = 0; i < r; i++) {
        print_array(c, m[i]);
        if (i != r - 1) printf("\n");
    }
}

void function_pointers(void) {
    // declare a function pointer
    // useful for callbacks and polymorphinsm
    int (*operation)(int, int);

    // point to the add function
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));

    // point to the multiply function
    operation = multiply;
    printf("5 * 3 = %d\n", operation(5, 3));

    // you can also call directly
    printf("direct call: %d\n", (*operation)(4, 2));
}

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

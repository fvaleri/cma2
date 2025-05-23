#include <stdio.h>
#include <string.h>

// the # operator creates a string version of the value
#define LOG(s) printf(#s " = %s\n", s)

int main(void) {
    // strings are character arrays with null terminator
    // the max length is at least 509 in C89 and at least 4095 in C99
    char s1[6] = {'h', 'e', 'l', 'l', 'o', '\0'};

    printf("s1 = ");
    for (int i = 0; s1[i] != 0; i++)
        printf("%c", s1[i]);
    printf("\n");

    // libc/string.h contains utility methods like strlen
    printf("s1 has %ld chars stored in %ld bytes\n",
        strlen(s1), sizeof(s1));

    // the ascii code of the null terminator is zero
    char s2[] = {'h', 'e', 'l', 'l', 'o', 0};
    LOG(s2);

    // abbreviation for array initializer
    char s3[] = "hello";
    s3[3] = 65;
    LOG(s3);

    // string literals can't be modified
    char *s4 = "hello";
    LOG(s4);

    return 0;
}

// mkdir bin
// cc -o bin/hello_world src/hello_world.c
// bin/hello_world
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int main(void) {
    printf("Hello World\n");

    int i = 5; // 32 bits, 4 bytes
    printf("int is %lu bytes, min %d, max %d\n", sizeof(i), INT_MIN, INT_MAX);

    // wrapping overflow behavior only defined for unsigned types
    unsigned char uc = 254;
    printf("unsigned char is %lu byte, max %d\n", sizeof(uc), UCHAR_MAX);
    uc++; printf("254 + 1 = %d\n", uc);
    uc++; printf("255 + 1 = %d (wrapping)\n", uc);

    // new types with known representation
    uint64_t x = 100;
    printf("unsigned int 64 bit is %lu bytes\n", sizeof(x));

	return 0;
}

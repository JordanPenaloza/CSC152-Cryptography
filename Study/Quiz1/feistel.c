#include <stdio.h>
#include <stdint.h>

void feistel(void *buf);

int main() {
    // Example buffer: two unsigned ints
    unsigned int buffer[2] = {12345, 67890};
    
    printf("Before Feistel function:\n");
    printf("buffer[0]: %u, buffer[1]: %u\n", buffer[0], buffer[1]);

    // Call the Feistel function
    feistel(buffer);

    printf("After Feistel function:\n");
    printf("buffer[0]: %u, buffer[1]: %u\n", buffer[0], buffer[1]);

    return 0;
}

void feistel(void *buf) {
    // Treat buf as an array of two unsigned ints
    unsigned int *buffer = (unsigned int *)buf;

    unsigned int left = buffer[0];
    unsigned int right = buffer[1];
    unsigned int tmp = ((right << 1) + right);
    left = left ^ tmp;
    buffer[0] = right;
    buffer[1] = left;
}


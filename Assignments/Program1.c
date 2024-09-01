// Program1 by Jordan Penaloza, Submitted for CSC152
// Used https://www.tutorialspoint.com/c_standard_library/c_function_memcmp.htm to learn about memcmp function

#include <stdio.h>
#include <string.h>

//checks if sequence of bytes in b matches the sequence of bytes at a[i]
int is_equal(void *a, void *b, int blen) {return memcmp(a, b, blen) == 0;}

int contains(void *a, int alen, void *b, int blen) {
    if (blen == 0) {
        return 1;
    }
    if (blen > alen) {
        return 0;
    }
    for (int i = 0; i <= alen - blen; i++) {
        if (is_equal((char*)a + i, b, blen)) { //send buffer a starting from position i and buffer b to check if it matches
            return 1;
        }
    }
    return 0;
}

//for test casing 
int main(int argc, char *argv[]) {

    char *a = argv[1];
    char *b = argv[2];

    int alen = strlen(a);
    int blen = strlen(b);

    int result = contains(a, alen, b, blen);

    if (result) {
        printf("Buffer b is contained in buffer a.\n");
    } else {
        printf("Buffer b is NOT contained in buffer a.\n");
    }

    return 0;
}
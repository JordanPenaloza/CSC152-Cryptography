// Program1.c by Jordan Penaloza (jordanpenaloza@csus.edu), Submitted for CSC152 Fall 2024
// Used memcmp() function from https://www.tutorialspoint.com/c_standard_library/c_function_memcmp.htm 
// Checks if the contents of a buffer is inside of another

#include <stdio.h>
#include <string.h>
#include <stdint.h>

//checks if sequence of bytes in b matches the sequence of bytes at a[i]
int is_equal(unsigned char *a, unsigned char *b, int blen) {return memcmp(a, b, blen) == 0;}

int contains(void *a, int alen, void *b, int blen) {
    a = (unsigned char*)a;
    b = (unsigned char*)b;
    if (blen == 0) {
        return 1;
    }
    if (blen > alen) {
        return 0;
    }
    for (int i = 0; i <= alen - blen; i++) {
        if (is_equal(a + i, b, blen)) { //send buffer a starting from position i and buffer b to check if it matches
            return 1;
        }
    }
    return 0;
}
/*
//for test casing 
int main() {
    // Test case 1: char buffer
    char a1[] = "abcdef";
    char b1[] = "def";
    printf("Test case 1: %s\n", contains(a1, sizeof(a1) - 1, b1, sizeof(b1) - 1) ? "Match" : "No Match");

    // Test case 2: int buffer
    int a2[] = {1, 2, 3, 4, 5, 6};
    int b2[] = {4, 5, 6};
    printf("Test case 2: %s\n", contains(a2, sizeof(a2), b2, sizeof(b2)) ? "Match" : "No Match");

    // Test case 3: float buffer
    float a3[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float b3[] = {3.3, 4.4};
    printf("Test case 3: %s\n", contains(a3, sizeof(a3), b3, sizeof(b3)) ? "Match" : "No Match");

    // Test case 4: uint64_t buffer
    uint64_t a4[] = {1, 2, 3, 4, 5};
    uint64_t b4[] = {3, 4};
    printf("Test case 4: %s\n", contains(a4, sizeof(a4), b4, sizeof(b4)) ? "Match" : "No Match");

    // Test case 5: b larger than a
    int a5[] = {1, 2, 3};
    int b5[] = {1, 2, 3, 4, 5};
    printf("Test case 5: %s\n", contains(a5, sizeof(a5), b5, sizeof(b5)) ? "Match" : "No Match");

    // Test case 6: both a and b empty
    char a6[] = "";
    char b6[] = "";
    printf("Test case 6: %s\n", contains(a6, sizeof(a6) - 1, b6, sizeof(b6) - 1) ? "Match" : "No Match");

    // Test case 7: b is empty
    char a7[] = "abcdef";
    char b7[] = "";
    printf("Test case 7: %s\n", contains(a7, sizeof(a7) - 1, b7, sizeof(b7) - 1) ? "Match" : "No Match");

    // Test case 8: unsigned char buffer
    unsigned char a8[] = "abcdef";
    unsigned char b8[] = "def";
    printf("Test case 8: %s\n", contains(a8, sizeof(a8) - 1, b8, sizeof(b8) - 1) ? "Match" : "No Match");

    return 0;
}
*/
/*
Write a function named cmp_bits that accepts two int arguments a and b, and compares the number of "on" bits (number of 1s) between them. Returns a negative result if the bitwise representation of a has fewer 1s than b, a positive result if a has more 1s than b, and zero if both have the same number of 1s. For example, if a is 5 (binary 00000000000000000000000000000101) and b is 32 (binary 00000000000000000000000000010000), then cmp_bits returns any positive number (for example, it could return 1).
*/

#include <stdio.h>

int cmp_bits(int a, int b) {
    unsigned int *ua = (unsigned int *)&a;
    unsigned int *ub = (unsigned int *)&b;
    int count_a = 0;
    int count_b = 0;
    
    while (*ua) {
        count_a += *ua & 1;
        *ua >>= 1;
    }
    while (*ub) {
        count_b += *ub & 1;
        *ub >>= 1;
    }
    if (count_a > count_b) {
        return 1;
    }
    if (count_a < count_b) {
        return -1;
    }
    return 0;
}
    





/*
Write a function named cmp_bits that accepts two int arguments a and b, and compares the number of "on" bits (number of 1s) 
between them. Returns a negative result if the bitwise representation of a has fewer 1s than b, a positive result if a has more 1s than b, 
and zero if both have the same number of 1s. For example, if a is 5 (binary 00000000000000000000000000000101) and b is 32 (binary 00000000000000000000000000010000), then cmp_bits returns any positive number (for example, it could return 1).
*/
int cmp_bits(int a, int b) {
    int count_a = 0;
    int count_b = 0;
    int n = sizeof(int) * 8;
    for(int i = 0; i < n; i++) {
        if(a & 1) {
            count_a++;
        }
        if(b & 1) {
            count_b++;
        }
        a>>=1;
        b>>=1;
    }
    if (count_a < count_b) {
        return -1;
    }
    else if(count_a > count_b) {
        return 1;
    }
    else{
        return 0;
    }
}
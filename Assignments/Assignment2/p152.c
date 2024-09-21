// p152.c by Jordan Penaloza. Submitted for CSC 152 

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// Static means that it is not exported for linking and so
// can only be called from this file.
static uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32-n));
}

// ap - dp are references to four variables to be mixed.
// A good compiler will keep everything in registers, so even
// though it looks like we're reading memory, we probably aren't.
void mix(uint32_t *ap, uint32_t *bp, uint32_t *cp, uint32_t *dp) {
    // Receive the four words to be mixed
    uint32_t a = *ap;
    uint32_t b = *bp;
    uint32_t c = *cp;
    uint32_t d = *dp;
    // Mix the four words

    a = a + b;
    d = a ^ d;
    d = rotl32(d,16);
    c = d + c;
    b = c ^ b;
    b = rotl32(b,12);
    a = b + a;
    d = a ^ d;
    d = rotl32(d,8);
    c = d + c;
    b = c ^ b;
    b = rotl32(b,7);

    // Update the caller's values
    *ap = a;
    *bp = b;
    *cp = c;
    *dp = d;
}


void p152(void *in, void *out) {
    uint32_t temp[16]; // because 16 * 4 = 64 bytes
    memcpy(temp, in, 64);
    for (int i = 0; i < 10; i++) {
        // First, mix on columns
        mix(&temp[0], &temp[4], &temp[8], &temp[12]);  // Column 1
        mix(&temp[1], &temp[5], &temp[9], &temp[13]);  // Column 2
        mix(&temp[2], &temp[6], &temp[10], &temp[14]); // Column 3
        mix(&temp[3], &temp[7], &temp[11], &temp[15]); // Column 4

        // Then, mix on diagonals
        mix(&temp[0], &temp[5], &temp[10], &temp[15]); // First diagonal
        mix(&temp[1], &temp[6], &temp[11], &temp[12]); // Second diagonal
        mix(&temp[2], &temp[7], &temp[8], &temp[13]);  // Third diagonal
        mix(&temp[3], &temp[4], &temp[9], &temp[14]);  // Fourth diagonal
    }
    memcpy(out, temp, 64);    
	
}

#if 0  // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    unsigned char buf[64] = {1};  // Puts 1 in frist byte, rest get auto zeroed
    p152(buf, buf);
    // As a test, output the first 16 bytes of the output
    printf("Is       : ");
    for (int i=0; i<16; i++)
        printf("%02x", buf[i]);
    printf("\n");
    printf("Should be: 14627e9771052d97a8a025cc5531572f\n");
}

#endif

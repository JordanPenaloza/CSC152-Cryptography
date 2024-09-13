// p152stream.c by Jordan Penaloza. Submitted for CSC 152 
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

// Increment buf as if it's a 64 byte big-endian integer
static void increment_block(void *buf) {
    unsigned char *blk = buf;
    int i = 63;
    blk[i] += 1;
    while (blk[i] == 0) {
        i -= 1;
        blk[i] += 1;
    }
} 

// k is 32 bytes, n is 16 bytes, 0* is 16 bytes
// Use blk = k || n || 0* to produce output as blk xor p152(blk), then increment blk
// This output is xor'd with the next 64 bytes of buf to encrypt/decrypt
void p152stream(void *k, void *n, void *inbuf, void *outbuf, int nbytes) {
    unsigned char *pinbuf = inbuf;
    unsigned char *poutbuf = outbuf;
    unsigned char in[64];
    unsigned char out[64];
    // Init in as k || n || 0*
    memcpy(in, k, 32);
    memcpy(in+32, n, 16);
    memset(in+48, 0, 16);

    while(nbytes >= 64){
	p152(in, out);
	for (int i = 0; i < 64; i++){
		out[i] ^= in[i]; //out = out ^ in
		poutbuf[i] = out[i] ^ pinbuf[i]; //out = out ^ next 64 bytes of inbuf
	} 
	increment_block(in);
	pinbuf += 64;   // Move to the next 64 bytes of input
	poutbuf += 64;  // Move to the next 64 bytes of output
	nbytes -= 64;   // Reduce the number of bytes remaining to process
    }
    if (nbytes > 0){
	p152(in,out);
    	for (int i = 0; i < nbytes; i++){
		out[i] ^= in[i];
		poutbuf[i] = out[i] ^ pinbuf[i];
		
	}
	increment_block(in);
    }
	
		

}

#if 1  // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    unsigned char inbuf[200] = {1};
    unsigned char outbuf[200];
    unsigned char k[32] = {1,2,3,4};
    unsigned char n[16] = {1,2,3,4};
    p152stream(k, n, inbuf, outbuf, 200);
    printf("Is       : ");
    for (int i=0; i<200; i++)
        printf("%02x", outbuf[i]);
    printf("\n");
    printf("Should be: d6c0e5ef8745f9fc4657510ce896e96b9f27c18ba5a8cadc7e2a"
           "6872c51c704983726c6633a9e924a5e9a75b8b9980cfad91501f74315fea6da"
           "0936286e5866ac66e8c3d766b6248f88ee99b468dd9fdcf2c4e65e6df35637b"
           "b245246e0cb97ce689c0b91dbd7212257f98744fae42484ea3afbd419db90ca"
           "38a96d4c6e68cd6c003af8b842733ad4162099b2b2d10bfd48a3fb6e8c5e5ea"
           "59dde8bae3206ce3e80f0acad1540e83e2858f39bccec0a4ece5172194f6d15"
           "e7fd5a26a05cb3b8b8fea979965daf5c1\n");
}

#endif

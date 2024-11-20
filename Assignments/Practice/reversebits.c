unsigned char reverseBits(unsigned char x) {
    unsigned char reversed = 0;
    for (int i = 0; i < 8; i++){
        reversed <<= 1;
        reversed |= (x & 1);
        x >>= 1;
    }
    return reversed;
}
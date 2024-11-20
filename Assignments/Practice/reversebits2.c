uint32_t reverseBits(uint32_t x) {
    uint32_t reverse = 0;
    for(int i = 0; i < 32 ; i++){
        reversed <<= 1;
        reversed |= (x & 1);
        x >>= 1;
    }
    return reversed;
}

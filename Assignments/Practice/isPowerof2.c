int isPowerOfTwo(uint32_t x){
    int count = 0;
    for(int i = 0; i < 32; i ++) {
        if ((x & 1) == 1) {
            count++;
        }
        x >>= 1;
    }
    if (count == 1) {
        return 1;
    }
    return 0;
}

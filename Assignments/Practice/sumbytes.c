uint32_t sumbytes(uint32_t x) {
    uint32_t sum = 0;
    uint32_t x1 = (x & 0xFF000000) >> 24;
    uint32_t x2 = (x & 0x00FF0000) >> 16;
    uint32_t x3 = (x & 0x0000FF00) >> 8;
    uint32_t x4 = (x & 0x000000FF);
    sum = x1 + x2 + x3 + x4;
    return sum;
    
}
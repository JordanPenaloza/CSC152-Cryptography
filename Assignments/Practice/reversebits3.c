void reverse_bits32(uint32_t *p) {
    uint32_t x = *p;
    uint32_t reverse = 0;
    for(int i = 0; i < 32; i++) {
        reverse <<= 1;
        reverse |= (x & 1);
        x >>= 1;
    }
    *p = reverse;
}
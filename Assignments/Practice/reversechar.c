void reverse_char(unsigned char x) {
    unsigned char hi = x & 0xF0;
    unsigned char lo = x & 0x0F;
    hi >>= 4;
    lo <<= 4;
    x = hi | lo;
}
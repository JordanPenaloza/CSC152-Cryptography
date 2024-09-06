unsigned char reverse_bits(unsigned char byte) {
    unsigned char reversed = 0;
    for (int i = 0; i < 8; i++) {
        int bit = (byte >> i) & 1;
        reversed |= (bit << (7-i));
    }
    return reversed;
    
}
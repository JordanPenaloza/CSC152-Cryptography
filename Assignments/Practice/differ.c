int differ_by_one_bit(uint32_t x, uint32_t y){
    int count = 0;
    uint32_t z = x ^ y;
    for (int i = 0; i < 32; i++){
        if (z & 1){
            count++;
        }
        z >>= 1;
        if (count > 1){
            return 0;
        }
    }
    return (count == 1);
}

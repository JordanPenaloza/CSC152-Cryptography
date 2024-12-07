int count_set_bits32(uint32_t *p){
    int x = *p;
    int count = 0;
    for(int i = 0; i < 32; i++){
        if(x & 1){
            count++;
        }
        x >>= 1;
    }
    return count;
}

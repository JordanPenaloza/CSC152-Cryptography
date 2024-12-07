int find_rightmost_set_bit(uint32_t x){
    int position = 1;
    for(int i = 0; i < 32; i++){
        if (x&1) {
            return position;
        }
        x>>=1;
        position++;
    }
    return 0;
}

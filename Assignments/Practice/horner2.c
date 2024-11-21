uint32_t poly(uint32_t *a, int n, uint32_t k, uint32_t p) {
    uint64_t acc = 1;
    for(int i = 0; i < n; i ++){
        acc = acc * k;
        acc = acc + a[i];
        acc = acc % p;
    }
    return (uint32_t) acc;
}
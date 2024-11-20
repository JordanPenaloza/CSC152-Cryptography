/*
 (5 Pts) Write a C function using Horners method to compute and return kn +a1kn−1+a2kn−2+...+ ank) mod p. 
 Parameter a points to an array of n elements. 
 All elements in a and the value k are nonnegative and less than p. 
 Do not use divisionless mod in this problem. uint32_t poly(uint32_t *a, int n, uint32_t k, uint32_t p) {

*/

uint32_t poly(uint32_t *a, int n, uint32_t k, uint32_t p) {
    uint64_t acc = k; 
    for(int i = 0; i < n; i++){
        acc = acc * k;
        acc = acc + a[i];
        acc = acc % p;
    }
    return (uint32_t)acc;
}
int bits_to_flip (int a, int b) {
    int c = a ^ b;
    int count = 0;
    for (int i = 0; i <= 31; i ++) {
        count += c & 1;
        c >>= 1;
    }
    return count; 
}

//test commit 3
#include <stdio.h>
#include <string.h>

int is_equal(void *a, void *b, int blen) {
    return memcmp(a, b, blen) == 0;
}
int contains(void *a, int alen, void *b, int blen) {
    if (alen < blen) {
        return 0;
    }
    if (blen == 0) {
        return 1;
    }
    for (int i = 0; i <= alen - blen; i++) {
        if (is_equal((char*)a + i,b,blen)) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

}
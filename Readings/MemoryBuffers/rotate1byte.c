#include <stdio.h>

void rotate1byte(void *buf, int bufbytes);

int main() {
    unsigned char buf[] = {1,2,3,4,5};
    int bufbytes = sizeof(buf);
    rotate1byte(buf, bufbytes);
    int length = sizeof(buf) / sizeof(buf[0]);
    for (int i = 0; i < length; i++) {
        printf("%d ", buf[i]);
    }
    printf("\n");
}

void rotate1byte(void *buf, int bufbytes) {
    if (bufbytes > 0) {
        unsigned char *p = buf; //p is pointer to buf
        unsigned char tmp = p[0]; //tmp value at start if buffer
        for (int i=1; i<bufbytes; i++) {
            p[i-1] = p[i]; //shift i to the left
        }
        p[bufbytes-1] = tmp;
    }
}

/*
the code execution of this function would look something like this to rotate the bytes
12345
22345
23345
23445
23455
23451


*/

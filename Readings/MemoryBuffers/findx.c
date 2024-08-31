#include <stdio.h>

int find_x(void *buf, int bufbytes, int x);

int main() {
    int buf[] = {1, 2, 3, 4, 5};
    int bufbytes = sizeof(buf);
    int x = 4;
    int found = find_x (buf, bufbytes, x);
    if (found) {
        printf("found %d in buffer\n", x);
    }
    else {
        printf("%d is not in the buffer\n", x);
    }
    return 0;
}

int find_x(void *buf, int bufbytes, int x) {
    int *p = buf; //p is a pointer to the start of the buffer and treats it like an array of ints
    int numints = bufbytes/sizeof(int); // calculates number of ints in the buffer
    for (int i = 0; i < numints; i++) { //loops through each int in the buffer
        if (p[i] == x) // checks if current int matches x
        return 1;
    }
    return 0;
}


#include <stdio.h>

int get_value() {
    int *p;
    int x = 6;
    p = &x;
    printf("%d\n", *p);
}

int print_address() {
    int var = 5;
    printf("var: %d\n",var);
    printf("address: %p\n",&var);
}

int main() {
    get_value();
    return 1;
}
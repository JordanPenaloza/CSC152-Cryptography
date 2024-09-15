#include <stdio.h>
#include <stdint.h>
int any_dup_ints(void *buf, int buflen);

int main() {
    // Example buffer with integers
    int buffer[] = {1, 2, 3, 4, 5, 6, 3}; // This has a duplicate (3)
    int buflen = sizeof(buffer);

    if (any_dup_ints(buffer, buflen)) {
        printf("Duplicate integers found.\n");
    } else {
        printf("No duplicate integers found.\n");
    }

    return 0;
}

int any_dup_ints(void *buf, int buflen){
	uint32_t *buffer = (uint32_t *)buf;
	for (int i = 0; i < buflen/sizeof(uint32_t) - 1; i++) {
		for (int j = i+1; j < buflen/sizeof(uint32_t); j++) {
			if (buffer[j] == buffer[i]) {
				return 1;
			}
		}
	}
	return 0;
}

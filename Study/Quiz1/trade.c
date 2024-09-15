#include <stdio.h>

void trade(void *buf, int buflen);

int main() {
    // Create a buffer with 7 bytes as an example (hex: 01 02 03 04 05 06 07)
    unsigned char buffer[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    int buflen = sizeof(buffer);

    printf("Before trade:\n");
    for (int i = 0; i < buflen; i++) {
        printf("%02x ", buffer[i]);
    }
    printf("\n");

    // Call the trade function
    trade(buffer, buflen);

    printf("After trade:\n");
    for (int i = 0; i < buflen; i++) {
        printf("%02x ", buffer[i]);
    }
    printf("\n");

    return 0;
}

// Trades bytes between even and odd indices.
void trade(void *buf, int buflen) {
	unsigned char *buffer = (unsigned char*)buf;
	unsigned char tmp;
	for (int i = 0; i < buflen-1; i+=2){
		
		tmp = buffer[i];
		buffer[i] = buffer[i+1];
		buffer[i+1] = tmp; 
	}

}

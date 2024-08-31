//prints bytes in file equal to 0

#include <stdio.h>
#include <stdlib.h>

#define BUF_BYTES 256

int main() {
    unsigned char buf[BUF_BYTES]; //small auto allocated buffer
    FILE *f = fopen("file.txt", "r"); //read file.txt
    if (f != NULL) {
        int count = 0;
        int bytes_read = fread(buf,1,BUF_BYTES,f); //attempt a read into buf
        while (bytes_read > 0) { //if there are bytes to read
            for (int i=0; i<bytes_read; i++) { //process what we got
                if (buf[i] ==0) {
                    count = count+1;
                }
            }
            bytes_read = fread(buf,1,BUF_BYTES,f); //attempt read into buf
        }
        printf("Found %d zeros\n", count);
        fclose(f);
    } else {
        printf("Error: could not open file.txt for reading");
    }
    return EXIT_SUCCESS;
}
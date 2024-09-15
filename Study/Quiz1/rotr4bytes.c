/*
 Problem:
You have a buffer that contains numbytes bytes of data. Write a function that rotates the last four bytes of the buffer to the beginning of the buffer, shifting all other bytes four bytes to the right.

You may assume numbytes is a multiple of 4, and you should treat the buffer as an array of uint32_t for efficiency.
 */

void rotr4bytes(void *buf, int numbytes) {
    uint32_t *buffer = (uint32_t*)buf;
    int num_elements = numbytes / 4;  // Add the missing semicolon
    uint32_t tmp = buffer[num_elements - 1];  // Store the last 4 bytes

    // Shift all elements to the right by one, starting from the second-to-last element
    for (int i = num_elements - 1; i > 0; i--) {
        buffer[i] = buffer[i - 1];  // Move element at i-1 to i
    }

    buffer[0] = tmp;  // Place the saved last element at the beginning
}


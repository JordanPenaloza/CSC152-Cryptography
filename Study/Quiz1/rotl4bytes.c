/*
 3) (4 Pts) Write C code that moves the first four bytes of a buffer to the end of the buffer and moves all the
other bytes four bytes closer to the beginning. For example, if the buffer was 010101010202020203030303
(in hex) before, it should be 020202020303030301010101 after. For speed, do this by treating the buffer as
if it were an array of uint32_t (which is a 4 byte type) and then finishing the problem as if it were a simple
array algorithm. You may assume numbytes is a positive multiple of 4.
void rotl4bytes(void *buf, int numbytes) {
 */ 
void rotl4bytes(void *buf, int numbytes) {
    uint32_t *buffer = (uint32_t*)buf;
    uint32_t tmp = buffer[0];  // Store the first 4 bytes (as a single uint32_t)
    int num_elements = numbytes / 4;  // Calculate number of 4-byte elements in buffer

    // Shift all elements to the left by one
    for (int i = 1; i < num_elements; i++) {
        buffer[i - 1] = buffer[i];
    }

    // Place the saved first element (tmp) at the end
    buffer[num_elements - 1] = tmp;
}


//chat_security.c by Jordan Penaloza. Submitted for CSC152
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void chat_encrypt(void *k, void *pt, int ptlen, void *ct) {
	//set parameters to unsigned char to work with bytes
	unsigned char *key = (unsigned char *)k;
	unsigned char *plaintext = (unsigned char *)pt;
	unsigned char *ciphertext = (unsigned char *)ct;

	//create a nonse of length 12 bytes and generate a random nonce to add to a 16 byte iv followed by 4 0s
	unsigned char nonce[12];
	RAND_bytes(nonce, sizeof(nonce));
	unsigned char iv[16];
	memcpy(iv, nonce, 12);
	memset(iv + 12, 0, 4);

	//copy the nonse to start of the ciphertext buffer
	memcpy(ciphertext, nonce, 12);

	//encrypt in aes256 ctr mode
	EVP_CIPHER_CTX *ctx;
	int len;
	int ctlen;
	
	//create and initialize the context
	ctx = EVP_CIPHER_CTX_new();
	
	//initialize encryption operation as ctr mode
	EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key, iv);
	
	//encrypt the message (cipher text goes after the nonse, starting at byte cipher text + nonce)
	EVP_EncryptUpdate(ctx, ciphertext + 12, &len, plaintext, ptlen);
	ctlen = len;
	
	//finalize the encryption
	EVP_EncryptFinal_ex(ctx, ciphertext + 12 + len, &len);
	ctlen += len;
	EVP_CIPHER_CTX_free(ctx);
	


}

void chat_decrypt(void *k, void *ct, int ctlen, void *pt) {
	unsigned char *key = (unsigned char *)k;
        unsigned char *plaintext = (unsigned char *)pt;
        unsigned char *ciphertext = (unsigned char *)ct;
	
	//copy the nonce from the ciphertext
	unsigned char nonce[12];
	memcpy(nonce, ciphertext, 12);
	
	//reconstruct the iv with ctr initialized to 0
	unsigned char iv[16];
	memcpy(iv, nonce, 12);
	memset(iv + 12, 0 ,4);

	//initialize context for decryption
	EVP_CIPHER_CTX *ctx;
	int len;
	int ptlen;
	ctx = EVP_CIPHER_CTX_new();

	//initialize decryption operation ctr mode
	EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, key, iv);

	//provide the decryption message and get plaintext output
	EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext + 12, ctlen - 12);
	ptlen = len;

	//Finalize the decryption
	EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
	ptlen += len;
	EVP_CIPHER_CTX_free(ctx);



}
#if 0     // Set to 1 to enable testing mode
int main() {
    // ----- First Test: Original Test with Random Key -----
    // Define a 256-bit key (32 bytes)
    unsigned char key[32];
    RAND_bytes(key, sizeof(key));

    // Define some plaintext (example message)
    unsigned char plaintext[] = "Hello, this is a test message!";
    int ptlen = strlen((char *)plaintext);

    // Allocate space for ciphertext (plaintext length + 12 bytes for the nonce)
    unsigned char ciphertext[ptlen + 12];

    // Allocate space for decrypted plaintext (+1 for null terminator)
    unsigned char decrypted[ptlen + 1];

    // Encrypt the plaintext
    chat_encrypt(key, plaintext, ptlen, ciphertext);
    printf("Original Plaintext: %s\n", plaintext);
    printf("Ciphertext in hex: ");
    for (int i = 0; i < ptlen + 12; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    chat_decrypt(key, ciphertext, ptlen + 12, decrypted);

    // Null-terminate the decrypted buffer
    decrypted[ptlen] = '\0';

    // Print the decrypted plaintext
    printf("Decrypted Ciphertext: %s\n", decrypted);

    // ----- Second Test: Test with Provided Ciphertext and Key -----
    printf("\nTesting provided ciphertext and key:\n");

    // Define the provided key (32 bytes), first 4 bytes are 1, 2, 3, 4, rest are 0
    unsigned char provided_key[32] = {1, 2, 3, 4};  // First 4 bytes are 1, 2, 3, 4; rest are 0

    // Define the provided ciphertext (93 bytes)
    unsigned char provided_ciphertext[93] = {
        0x45, 0x29, 0x18, 0x7D, 0x4D, 0x1C, 0xF3, 0x1D, 0x51, 0xBF,
        0x1A, 0xB9, 0x25, 0x57, 0xCD, 0xE3, 0x87, 0x07, 0xED, 0x72,
        0xA2, 0x9E, 0xD2, 0xA8, 0xEA, 0x3F, 0xA9, 0x2E, 0xE5, 0x08,
        0x88, 0xB8, 0xE5, 0xC3, 0xA4, 0xEC, 0xE1, 0x2F, 0xD3, 0x6E,
        0x5E, 0x92, 0xAA, 0x21, 0x2A, 0x9C, 0x7C, 0xFC, 0x62, 0x43,
        0xA9, 0x95, 0x4B, 0x0C, 0x7F, 0xB8, 0x6C, 0x59, 0x5D, 0x5C,
        0x56, 0x8C, 0x08, 0x52, 0x31, 0xD9, 0x03, 0x32, 0x8D, 0xA4,
        0x09, 0x86, 0x0B, 0xBE, 0x5A, 0xE1, 0x28, 0x4C, 0x57, 0xCE,
        0xE3, 0xAA, 0x4F, 0x7A, 0x0E, 0x11, 0x97, 0xAF, 0x89, 0x6D,
        0x34, 0xD8, 0x1B
    };

    // Allocate space for decrypted plaintext from provided ciphertext
    int provided_ctlen = sizeof(provided_ciphertext);
    int provided_ptlen = provided_ctlen - 12;  // Subtract 12 bytes for the nonce
    unsigned char provided_decrypted[provided_ptlen + 1];  // +1 for null terminator

    // Decrypt the provided ciphertext
    chat_decrypt(provided_key, provided_ciphertext, provided_ctlen, provided_decrypted);

    // Null-terminate the decrypted buffer
    provided_decrypted[provided_ptlen] = '\0';

    // Print the decrypted plaintext
    printf("Decrypted Provided Ciphertext: %s\n", provided_decrypted);

    return 0;
}
#endif


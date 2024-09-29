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
#if 0     // Set to 1 while testing and 0 for submission
int main() {
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

    return 0;
}
#endif

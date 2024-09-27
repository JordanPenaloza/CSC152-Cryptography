#include <openssl/evp.h>
#include <stdint.h>
int main() {
	char pt[44] = "The quick brown fox jumps over the lazy dog";
	char ct[44];
	char pt2[44];
	unsigned char key[16] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6};
	unsigned char iv[16] = {1,2,3,4,5,6,7,8,0,0,0,0,0,0,1};


	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key, iv))
	
	
	return 0;

}

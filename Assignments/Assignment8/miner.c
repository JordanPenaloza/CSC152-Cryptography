//miner.c by Jordan Penaloza. Submitted for CSC152.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors() {
    fprintf(stderr, "An error occurred!\n");
    exit(1);
}
void digest_message(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len)
{
	EVP_MD_CTX *mdctx;

	if((mdctx = EVP_MD_CTX_new()) == NULL)
		handleErrors();

	if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
		handleErrors();

	if(1 != EVP_DigestUpdate(mdctx, message, message_len))
		handleErrors();

	if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
		handleErrors();

	if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len))
		handleErrors();

	EVP_MD_CTX_free(mdctx);
}
void to_hex(void *buf, int len){
	unsigned char *p = (unsigned char *)buf;
	for(int i = 0; i < len; i++){
		printf("%02x", p[i]);
	}
	printf("\n");
}
void increment_string(unsigned char *str, int length) {
	for (int i = length - 1; i >= 0; i--){
		if (str[i] < 'z' ){
			str[i] += 1;
			return;	
		} else {
			str[i] = 'a';
		}
	}
	memmove(str + 1, str, length);
	str[0] = 'a';
	str[length + 1] = '\0';
}
int has_leading_zero_bits(const unsigned char *digest, int zero_bits){
	int full_bytes = zero_bits / 8;
	int remaining_bits = zero_bits % 8;
	for (int i = 0; i < full_bytes; i++){
		if (digest[i] != 0) {
			return 0;
		}
	}
	if (remaining_bits > 0){
		unsigned char mask = 0xFF << (8 - remaining_bits);
		if ((digest[full_bytes] & mask) != 0) {
			return 0;
		}	
	}
	return 1;
}
int main(int argc, char **argv) {
	if(argc != 2){
		printf("Usage %s <number of leading zero bits>\n", argv[0]);
		return 1;
	}
	else {
		printf("Mining...\n");
	}
	int n = atoi(argv[1]);
	if (n % 4 != 0){
		printf("Input must be a multiple of 4");
	}
	unsigned char charset[60] = "a";
        unsigned char *digest;
        unsigned int digest_len = 0;
	while (1) {
        	digest_message(charset, strlen((char*)charset), &digest, &digest_len);
		if (has_leading_zero_bits(digest, n)){
			printf("Found string: %s\n", charset);
			printf("Digest: ");
			to_hex(digest, digest_len);
			break;
		}
		OPENSSL_free(digest);
		increment_string(charset, strlen((char *)charset));
	}
	return 0;

}

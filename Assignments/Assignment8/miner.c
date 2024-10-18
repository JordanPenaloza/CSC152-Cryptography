#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <time.h>

#define MAX_LENGTH 60
#define CHARACTER_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"


void handleErrors(void) {
	ERR_print_errors_fp(stderr);
	abort();
}
void digest_message(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len) {
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
void to_hex_string(unsigned char *digest, unsigned int digest_len, char *output) {
	for(unsigned int i = 0; i < digest_len; i++) {
		sprintf(output + (i * 2), "%02x", digest[i]);
	}
	output[digest_len * 2] = '\0';
}
int check_zeroes(int num_hex_chars, char buffer[], char *message, char *hex_output){
	int all_zero = 1;
        for(int i = 0; i < num_hex_chars; i++) {
                if (buffer[i] != '0') {
                        all_zero = 0;
                        break;
                }
        }
	if(all_zero) {
                printf("Message: %s\n", message);
                printf("SHA-256 DIGEST: %s\n", hex_output);
                return 1;
        }
	return 0;

}
int main(int argc, char *argv[]) {
	srand(time(NULL)); //random seeding for rand() for true randomness in generatng ASCII	
    	if (argc != 2) {
        	printf("Usage: %s <n>\n", argv[0]);
        	return 1; 
    	}

    	int n = atoi(argv[1]);

    	if (n <= 0 || n % 4 != 0) {
        	printf("Error: Please provide a positive integer multiple of 4.\n");
        	return 1;  
    	}
    	printf("Mining with %d leading zero bits...\n", n);
	
	char message[MAX_LENGTH + 1] = "";
	int random_index = 0;
	size_t charset_len = strlen(CHARACTER_SET);
	
	//infinite loop that searches for correct input until corresponding hash is foune
	while(1){
		size_t length = strlen(message);
        	if (length < MAX_LENGTH) {
            		message[length] = CHARACTER_SET[rand() % charset_len];
            		message[length + 1] = '\0';  
        	} else {
            		memset(message, 0, MAX_LENGTH + 1);
          	  	length = 0;
       		}
		unsigned char *digest = NULL;
        	unsigned int digest_len = 0;
        	digest_message((unsigned char *)message, strlen(message), &digest, &digest_len);
        	char hex_output[digest_len * 2 + 1];
        	to_hex_string(digest, digest_len, hex_output);
		OPENSSL_free(digest);

		int num_hex_chars = n / 4;
		char buffer[num_hex_chars + 1];
		for (int i = 0; i < num_hex_chars; i++) {
			buffer[i] = hex_output[i];
		}
		buffer[num_hex_chars] = '\0';
		
		if (check_zeroes(num_hex_chars, buffer, message, hex_output)) {
	        	return 0;  
        	}	

	}

    	return 0;
}


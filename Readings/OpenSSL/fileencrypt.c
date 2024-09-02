#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define BUF_BYTES 256  // Will read this many bytes at a time

int main() {
  EVP_CIPHER_CTX *ctx;
  int len;
  int ciphertext_len;
  unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned char iv[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned char buf[BUF_BYTES];      // Small auto-allocated buffer
  ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
  FILE *fin = fopen("plaintext.dat", "r");
  FILE *fout = fopen("ciphertext.dat", "w");
  if ((fin != NULL) && (fout != NULL)) {
    int bytes_read  = fread(buf,1,BUF_BYTES,fin);  // Attempt a read into buf
    while (bytes_read > 0) {                       // If we got anything
      EVP_EncryptUpdate(ctx, buf, &len, buf, bytes_read); //applied the encryption
      fwrite(buf,1,len,fout);               // Write the bytes we read and encrypted
      bytes_read = fread(buf,1,BUF_BYTES,fin);     // Attempt a read into buf
    }
    EVP_EncryptFinal_ex(ctx, buf, &len);
    fwrite(buf,1,len,fout);
    fclose(fin);
    fclose(fout);
    EVP_CIPHER_CTX_free(ctx);
  } else {
    printf("Error: could not open both files");
  }
  return EXIT_SUCCESS;
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
      unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;
  int len;
  int ciphertext_len;

  ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
  EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
  ciphertext_len = len;
  EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
  ciphertext_len += len;
  EVP_CIPHER_CTX_free(ctx);
  return ciphertext_len;
}
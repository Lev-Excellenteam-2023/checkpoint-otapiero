#pragma once

#define AES_KEY_LENGTH 32 // 256-bit key
#define AES_IV_LENGTH 16  // 128-bit IV
#define KEY "a8faf318361534cf64499af1d71d95407966754e739237dde8e0890fefc0c6ed"
#define IV "271c263fcc8ff33de48dd0437a54c1c8"


// encryption of the data using openssl

int encrypt( char *plaintext, int plaintext_len,  char *key,
             char *iv,  char *ciphertext);

void encrypt_to_file(char *data, char *key, char *iv, char *filename);

int decrypt(char *ciphertext, int ciphertext_len,  char *key,
             char *iv,  char *plaintext);

void decrypt_from_file(char *encryptedFile, char* decryptedFile, char *key, char *iv, char *plaintext);
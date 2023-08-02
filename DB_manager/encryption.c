#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include "encryption.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt( char *plaintext, int plaintext_len,  char *key,
             char *iv,  char *ciphertext)
{
   
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
    {
        printf("error encrypting\n");
    }

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        printf("error encrypting\n");
    }
    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {
        printf("error encrypting\n");
    } 
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        printf("error encrypting\n");
    }
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

void encrypt_to_file(char *data, char *key, char *iv, char *filename)
{
    // create file
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    // Get data size
    int dataSize =  strlen(data);
    printf("dataSize: %d\n", dataSize);


    char* encryptedData = (char*)malloc(sizeof(char) * dataSize * 2);
    encrypt(data,dataSize, key, iv, encryptedData);
    encryptedData[dataSize * 2] = '\0';
    // Write encrypted data to file
    fwrite(encryptedData, sizeof(char), dataSize * 2, file);

    // Close file
    fclose(file);
    free(encryptedData);

}
int decrypt(char *ciphertext, int ciphertext_len,  char *key,
             char *iv,  char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
    {
        printf("error decrypting 1\n");
    }
    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        printf("error decrypting 2\n");
    }
    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    {
        printf("error decrypting 3\n");
    }
    plaintext_len = len;
    printf("plaintext_len: %d\n", plaintext_len);
    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    {
        handleErrors();
    }
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

void decrypt_from_file(char *encryptedFile, char* decryptedFile, char *key, char *iv, char *plaintext)
{
    // open encrypted file
    FILE *file = fopen(encryptedFile, "rb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // Get encrypted data size
    char* encryptedData = (char*)malloc(sizeof(char) * 1000);
    int encryptedDataSize = strlen(encryptedData);
    encryptedData[encryptedDataSize] = '\0';
    // Close file
    fclose(file);



    // open decrypted file
    FILE *decrypted = fopen(decryptedFile, "wb");
    if (decrypted == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    // Get encrypted data size
    char* decryptedData = (char*)malloc(sizeof(char) * encryptedDataSize);
    decrypt(encryptedData, encryptedDataSize, key, iv, decryptedData);
    decryptedData[encryptedDataSize] = '\0';
    // Write decrypted data to file
    fwrite(decryptedData, sizeof(char), encryptedDataSize, decrypted);

    // Close file
    fclose(decrypted);
    free(encryptedData);
    free(decryptedData);





}
#ifndef CRYPTO_H
#define CRYPTO_H

// XOR encryption function (can be used for decryption as well)
// The same function is used for encrypting and decrypting
void xor_encrypt(char* data, const char* key);
void xor_decrypt(char* data, const char* key);  // Simply reuses xor_encrypt

#endif
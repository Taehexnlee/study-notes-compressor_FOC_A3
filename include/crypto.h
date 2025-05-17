#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h> // for size_t

// Encrypts the input text using XOR cipher with a repeating key.
// The encryption is done in-place (modifies the original `text` buffer).
// `text`  - the data to encrypt
// `key`   - the encryption key
// `length` - the number of bytes in `text` to encrypt
void xor_encrypt(char* text, const char* key, size_t length);

// Decrypts the input text using XOR cipher.
// Since XOR encryption is symmetric, this just calls xor_encrypt again.
// `text`  - the data to decrypt
// `key`   - the same key used for encryption
// `length` - the number of bytes in `text` to decrypt
void xor_decrypt(char* text, const char* key, size_t length);

#endif // CRYPTO_H
#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h> // for size_t

// Encrypts the input text using a repeating key.
// The encryption is done in-place (modifies the original `text` buffer).
// `text`   - the data to encrypt
// `key`    - the encryption key
// `length` - the number of bytes in `text` to encrypt
void encryptData(char* text, const char* key, size_t length);

// Decrypts the input text using the same key.
// The encryption method is symmetric, so this uses the same logic.
// `text`   - the data to decrypt
// `key`    - the same key used for encryption
// `length` - the number of bytes in `text` to decrypt
void decryptData(char* text, const char* key, size_t length);

#endif // CRYPTO_H
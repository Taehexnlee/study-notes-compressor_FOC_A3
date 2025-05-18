#include <string.h>
#include "../include/crypto.h"

// Encrypts the input data using a repeating key.
// This modifies the input buffer in-place.
// The same function is used for both encryption and decryption due to XOR symmetry.
void encryptData(char* data, const char* key, size_t length) {
    size_t keyLength = strlen(key);
    for (size_t i = 0; i < length; ++i) {
        // Repeats key if it's shorter than the data
        data[i] ^= key[i % keyLength];  
    }
}

// Decrypts the encrypted text using the same key.
// Since the encryption is symmetric, this simply calls encryptData again.
void decryptData(char* text, const char* key, size_t length) {
    // Reuses the same logic
    encryptData(text, key, length);  
}
#include <string.h>
#include "../include/crypto.h"

// Performs XOR encryption on the input data using the provided key.
// This modifies the input buffer in-place.
// The same function is used for both encryption and decryption due to XOR symmetry.
void xor_encrypt(char* data, const char* key, size_t length) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < length; ++i) {
        // Repeats key if it's shorter than the data
        data[i] ^= key[i % key_len];  
    }
}

// Decrypts the XOR-encrypted text using the same key.
// Since XOR is symmetric, this simply calls xor_encrypt again.
void xor_decrypt(char* text, const char* key, size_t length) {
    // Reuses the same logic
    xor_encrypt(text, key, length);  
}
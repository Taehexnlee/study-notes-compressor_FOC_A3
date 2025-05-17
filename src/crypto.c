#include <string.h>
#include "../include/crypto.h"

// Encrypt the data using XOR with the given key.
// The key is repeated cyclically to match the data length.
void xor_encrypt(char* data, const char* key) {
    size_t data_len = strlen(data);
    size_t key_len = strlen(key);

    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

// Decryption is performed by applying XOR again with the same key.
// XOR-ing twice restores the original value.
void xor_decrypt(char* data, const char* key) {
    xor_encrypt(data, key);
}
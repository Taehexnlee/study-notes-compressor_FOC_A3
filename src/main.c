#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"
#include "../include/crypto.h"
#include "../include/fileio.h"

int main(int argc, char* argv[]) 
{
    // Temporary test for encryption
    char message[] = "hello world";
    char key[] = "abc";

    printf("Original: %s\n", message);

    xor_encrypt(message, key);
    printf("Encrypted: %s\n", message);

    xor_decrypt(message, key);
    printf("Decrypted: %s\n\n", message);

    // Temporary test for compression
    char text[] = "aaabbbbcc";
    printf("Original (RLE): %s\n", text);

    char* compressed = compress(text);
    printf("Compressed: %s\n", compressed);

    char* decompressed = decompress(compressed);
    printf("Decompressed: %s\n\n", decompressed);

    free(compressed);
    free(decompressed);

    // Actual CLI logic
    if (argc < 2) 
    {
        printf("Usage: ./notes_app [add | view]\n");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) 
    {
        // TODO: Prompt user for input → Compress → Encrypt → Save to file
    } else if (strcmp(argv[1], "view") == 0) 
    {
        // TODO: Read from file → Decrypt → Decompress → Display
    } else 
    {
        printf("Invalid command. Use 'add' or 'view'\n");
    }

    return 0;
}
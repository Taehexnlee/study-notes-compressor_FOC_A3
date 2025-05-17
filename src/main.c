#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"
#include "../include/crypto.h"
#include "../include/fileio.h"

#define MAX_INPUT 1024
#define FILENAME "note.txt"
#define KEY "secret"  

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        printf("Usage: ./notes_app [add | view]\n");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) 
    {
        char input[MAX_INPUT];
        printf("Enter your note: ");
        fgets(input, MAX_INPUT, stdin);

        // Remove newline from fgets
        input[strcspn(input, "\n")] = 0;

        // Compress the note
        char* compressed = compress(input);
        if (!compressed) {
            fprintf(stderr, "Compression failed.\n");
            return 1;
        }

        size_t compressed_len = strlen(compressed);

        // Encrypt the compressed data
        xor_encrypt(compressed, KEY, compressed_len);

        // Save encrypted data to file
        if (save_to_file(FILENAME, compressed, compressed_len) != 0) {
            fprintf(stderr, "Failed to save note to file.\n");
            free(compressed);
            return 1;
        }

        printf("Note saved successfully.\n");
        free(compressed);
    } 
    else if (strcmp(argv[1], "view") == 0) 
    {
        size_t encrypted_len = 0;
        char* encrypted = load_from_file(FILENAME, &encrypted_len);
        if (!encrypted) {
            fprintf(stderr, "Failed to read file.\n");
            return 1;
        }

        // Decrypt the data
        xor_decrypt(encrypted, KEY, encrypted_len);

        // Decompress the decrypted data
        char* decompressed = decompress(encrypted);
        if (!decompressed) {
            fprintf(stderr, "Decompression failed.\n");
            free(encrypted);
            return 1;
        }

        printf("Your saved note: %s\n", decompressed);

        free(encrypted);
        free(decompressed);
    } 
    else 
    {
        printf("Invalid command. Use 'add' or 'view'\n");
    }

    return 0;
}
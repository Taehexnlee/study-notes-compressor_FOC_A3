#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"
#include "../include/crypto.h"
#include "../include/fileio.h"

#define MAX_INPUT 2048
#define FILENAME "note.txt"
#define KEY "secret"

int main(int argc, char* argv[]) 
{
    // Check if command line argument is provided
    if (argc < 2) 
    {
        printf("Usage: ./notes_app [add | view]\n");
        return 1;
    }

    // ADD MODE: Save a new encrypted and compressed note
    if (strcmp(argv[1], "add") == 0) 
    {
        char name[100], student_id[50], subject[100], note[MAX_INPUT];

        // Get user input
        printf("Enter your name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter your student ID: ");
        fgets(student_id, sizeof(student_id), stdin);
        student_id[strcspn(student_id, "\n")] = 0;

        printf("Enter subject name: ");
        fgets(subject, sizeof(subject), stdin);
        subject[strcspn(subject, "\n")] = 0;

        printf("Enter your note: ");
        fgets(note, sizeof(note), stdin);
        note[strcspn(note, "\n")] = 0;

        // Combine all input into one formatted string
        char full_text[MAX_INPUT * 2];
        snprintf(full_text, sizeof(full_text),
                 "Name: %s\nStudent ID: %s\nSubject: %s\nNote: %s",
                 name, student_id, subject, note);

        // Replace reserved characters before compression
        sanitize_input(full_text);

        // Compress the text
        size_t compressed_len;
        char* compressed = compress(full_text, &compressed_len);
        if (!compressed) 
        {
            fprintf(stderr, "Compression failed.\n");
            return 1;
        }

        // Encrypt the compressed data
        xor_encrypt(compressed, KEY, compressed_len);

        // Save encrypted data to file
        if (save_to_file(FILENAME, compressed, compressed_len) != 0) 
        {
            fprintf(stderr, "Failed to save note to file.\n");
            free(compressed);
            return 1;
        }

        printf("Note saved successfully.\n");
        free(compressed);
    } 
    // VIEW MODE: Load, decrypt, decompress and display the saved note
    else if (strcmp(argv[1], "view") == 0) 
    {
        // Load encrypted data from file
        size_t encrypted_len;
        char* encrypted = load_from_file(FILENAME, &encrypted_len);
        if (!encrypted) 
        {
            fprintf(stderr, "Failed to read file.\n");
            return 1;
        }

        // Decrypt the data
        xor_decrypt(encrypted, KEY, encrypted_len);
        
        // Decompress the decrypted data
        size_t decompressed_len;
        char* decompressed = decompress(encrypted, &decompressed_len);
        if (!decompressed) 
        {
            fprintf(stderr, "Decompression failed.\n");
            free(encrypted);
            return 1;
        }

        // Restore original characters (e.g., [COLON] → :)
        desanitize_output(decompressed);
        
        // Final output
        printf("Your saved note:\n%s\n", decompressed);

        // Clean up
        free(encrypted);
        free(decompressed);
    }
    else 
    {
        // Invalid command
        printf("Invalid command. Use 'add' or 'view'\n");
    }

    return 0;
}
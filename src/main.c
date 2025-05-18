#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"
#include "../include/crypto.h"
#include "../include/fileio.h"

#define MAX_INPUT 2048
#define FILE_NAME "note.txt"
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
        char name[100], studentId[50], subject[100], note[MAX_INPUT];

        // Get user input
        printf("Enter your name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter your student ID: ");
        fgets(studentId, sizeof(studentId), stdin);
        studentId[strcspn(studentId, "\n")] = 0;

        printf("Enter subject name: ");
        fgets(subject, sizeof(subject), stdin);
        subject[strcspn(subject, "\n")] = 0;

        printf("Enter your note: ");
        fgets(note, sizeof(note), stdin);
        note[strcspn(note, "\n")] = 0;

        // Combine all input into one formatted string
        char fullText[MAX_INPUT * 2];
        snprintf(fullText, sizeof(fullText),
                 "Name: %s\nStudent ID: %s\nSubject: %s\nNote: %s",
                 name, studentId, subject, note);

        // Replace reserved characters before compression
        escapeText(fullText);

        // Compress the text
        size_t compressedLength;
        char* compressed = compress(fullText, &compressedLength);
        if (!compressed) 
        {
            fprintf(stderr, "Compression failed.\n");
            return 1;
        }

        // Encrypt the compressed data
        encryptData(compressed, KEY, compressedLength);

        // Save encrypted data to file
        if (saveToFile(FILE_NAME, compressed, compressedLength) != 0) 
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
        size_t encryptedLength;
        char* encrypted = loadFromFile(FILE_NAME, &encryptedLength);
        if (!encrypted) 
        {
            fprintf(stderr, "Failed to read file.\n");
            return 1;
        }

        // Decrypt the data
        decryptData(encrypted, KEY, encryptedLength);
        
        // Decompress the decrypted data
        size_t decompressedLength;
        char* decompressed = decompress(encrypted, &decompressedLength);
        if (!decompressed) 
        {
            fprintf(stderr, "Decompression failed.\n");
            free(encrypted);
            return 1;
        }

        // Restore original characters (e.g., [COLON] → :)
        unescapeText(decompressed);
        
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
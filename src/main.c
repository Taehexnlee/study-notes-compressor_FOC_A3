#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/rle.h"
#include "../include/crypto.h"
#include "../include/fileio.h"
#include "../include/feedback.h"

#ifdef DEBUG
#define DEBUG_PRINT(...) printf("[DEBUG] " __VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#define MAX_INPUT 2048
#define FILE_NAME "feedback.dat"
#define KEY "secret"

// Main function to handle add, view, delete commands for feedback entries
int main(int argc, char* argv[]) 
{
    // Check if a command is provided
    if (argc < 2) 
    {
        printf("Usage: ./note_app [add | view | delete <id>]\n");
        return 1;
    }

    Feedback* head = NULL;
    int nextId = 1;

    // Load encrypted and compressed data from file
    size_t fileLen;
    char* encrypted = loadFromFile(FILE_NAME, &fileLen);
    if (encrypted) 
    {
        DEBUG_PRINT("Encrypted data loaded from file (length: %zu)\n", fileLen);
        decryptData(encrypted, KEY, fileLen); // Decrypt the data
        size_t textLen; 
        char* decompressed = decompress(encrypted, &textLen); // Decompress the data
        if (decompressed) 
        {
            DEBUG_PRINT("Data decompressed (length: %zu)\n", textLen);
            unescapeText(decompressed); // Restore original special characters
            head = deserializeFeedback(decompressed, &nextId); // Deserialize to linked list
            free(decompressed);
        }
        free(encrypted);
    }

    // ADD command: collect and add new feedback
    if (strcmp(argv[1], "add") == 0) 
    {
        char name[100], studentId[50], subject[100], feedbackText[MAX_INPUT];

        printf("Enter your name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter your student ID: ");
        fgets(studentId, sizeof(studentId), stdin);
        studentId[strcspn(studentId, "\n")] = 0;

        printf("Enter subject name: ");
        fgets(subject, sizeof(subject), stdin);
        subject[strcspn(subject, "\n")] = 0;

        printf("Enter your feedback: ");
        fgets(feedbackText, sizeof(feedbackText), stdin);
        feedbackText[strcspn(feedbackText, "\n")] = 0;

        head = addFeedback(head, name, studentId, subject, feedbackText, &nextId);
        printf("Feedback saved (ID: %d).\n", nextId - 1);
    }
    // VIEW command: display all feedback
    else if (strcmp(argv[1], "view") == 0) 
    {
        printAllFeedback(head);
    }
    // DELETE command: delete a feedback by ID
    else if (strcmp(argv[1], "delete") == 0 && argc == 3) 
    {
        int id = atoi(argv[2]);
        head = deleteFeedbackById(head, id);
    }
    else if (strcmp(argv[1], "search") == 0 && argc == 3) 
    {
        int id = atoi(argv[2]);
        Feedback* found = findFeedbackById(head, id);
        if (found) 
        {
            printf("ID: %d\n", found->id);
            printf("Name: %s\n", found->studentName);
            printf("Student ID: %s\n", found->studentId);
            printf("Subject: %s\n", found->subject);
            printf("Feedback: %s\n", found->feedback);
        } else 
        {
            printf("Feedback with ID %d not found.\n", id);
        }
    }
    // Invalid command handling
    else 
    {
        printf("Invalid command. Usage: ./note_app [add | view | delete <id>]\n");
    }

    // Save updated feedback data back to file (encrypted and compressed)
    size_t textLen;
    char* plainText = serializeFeedback(head, &textLen);
    if (plainText) 
    {
        DEBUG_PRINT("Serialized feedback text (length: %zu)\n", textLen);
        escapeText(plainText); // Escape special characters before compression
        size_t compressedLen;
        char* compressed = compress(plainText, &compressedLen);
        if (compressed) 
        {
            DEBUG_PRINT("Compressed text (length: %zu)\n", compressedLen);
            encryptData(compressed, KEY, compressedLen); // Encrypt compressed data
            saveToFile(FILE_NAME, compressed, compressedLen); // Save to file
            DEBUG_PRINT("Encrypted data saved to file\n");
            free(compressed);
        }
        free(plainText);
    }

    // Clean up memory
    freeFeedbackList(head);
    return 0;
}
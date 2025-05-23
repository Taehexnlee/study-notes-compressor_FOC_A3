#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/feedback.h"

// Adds a new feedback node to the end of the linked list
// Returns the head of the updated list.
Feedback* addFeedback(Feedback* head, const char* studentName, const char* studentId, const char* subject, const char* feedbackText, int* nextId) 
{
    Feedback* newNode = (Feedback*)malloc(sizeof(Feedback));
    if (!newNode) return head;

    newNode->id = (*nextId)++;
    strncpy(newNode->studentName, studentName, sizeof(newNode->studentName));
    strncpy(newNode->studentId, studentId, sizeof(newNode->studentId));
    strncpy(newNode->subject, subject, sizeof(newNode->subject));
    strncpy(newNode->feedback, feedbackText, sizeof(newNode->feedback));
    newNode->next = NULL;

    if (!head) return newNode;

    Feedback* current = head;
    while (current->next) 
    {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Prints all feedback entries in the linked list
// If the list is empty, prints "No feedback found."
void printAllFeedback(const Feedback* head) 
{   
    if (head == NULL) 
    {
        printf("No feedback found.\n");
        return;
    }
    const Feedback* current = head;
    while (current) 
    {
        printf("ID: %d\n", current->id);
        printf("Name: %s\n", current->studentName);
        printf("Student ID: %s\n", current->studentId);
        printf("Subject: %s\n", current->subject);
        printf("Feedback: %s\n", current->feedback);
        printf("-----------------------------\n");
        current = current->next;
    }
}

// Frees all nodes in the feedback linked list
void freeFeedbackList(Feedback* head) 
{
    while (head) 
    {
        Feedback* temp = head;
        head = head->next;
        free(temp);
    }
}

// Deletes a feedback entry by ID, if found
// Returns the new head of the list
Feedback* deleteFeedbackById(Feedback* head, int id) 
{
    if (!head) return NULL;

    if (head->id == id) 
    {
        Feedback* temp = head->next;
        printf("Deleted feedback ID %d (%s - %s)\n", head->id, head->studentName, head->subject);
        free(head);
        return temp;
    }

    Feedback* current = head;
    while (current->next && current->next->id != id) 
    {
        current = current->next;
    }

    if (current->next) 
    {
        Feedback* toDelete = current->next;
        current->next = toDelete->next;
        printf("Deleted feedback ID %d (%s - %s)\n", toDelete->id, toDelete->studentName, toDelete->subject);
        free(toDelete);
    } else 
    {
        printf("Feedback with ID %d not found.\n", id);
    }

    return head;
}

// Finds a feedback entry by its ID
// Returns pointer to the matching node, or NULL if not found.
Feedback* findFeedbackById(Feedback* head, int id) 
{
    Feedback* current = head;
    while (current) 
    {
        if (current->id == id) return current;
        current = current->next;
    }
    return NULL;
}

// Converts the entire linked list into a single formatted string.
// Returns a dynamically allocated string (caller must free).
char* serializeFeedback(const Feedback* head, size_t* outLength) 
{
    const Feedback* current = head;
    // Initial buffer size, will expand dynamically
    size_t totalLen = 1024;
    char* buffer = malloc(totalLen);
    if (!buffer) return NULL;
    buffer[0] = '\0';

    while (current) 
    {
        char entry[2500];
        snprintf(entry, sizeof(entry),
                 "ID:%d\nName:%s\nStudentID:%s\nSubject:%s\nFeedback:%s\n===\n",
                 current->id, 
                 current->studentName, 
                 current->studentId,
                 current->subject, 
                 current->feedback
                );

        size_t entryLen = strlen(entry);
        size_t currentLen = strlen(buffer);

        if (currentLen + entryLen + 1 > totalLen) 
        {
            totalLen = totalLen + entryLen + 1024;
            char* newBuffer = realloc(buffer, totalLen);
            if (!newBuffer) 
            {
                free(buffer);
                return NULL;
            }
            buffer = newBuffer;
        }

        strcat(buffer, entry);
        current = current->next;
    }

    if (outLength) *outLength = strlen(buffer);
    return buffer;
}

// Parses a serialized feedback string and reconstructs the linked list.
// Also updates the next ID to maintain uniqueness.
Feedback* deserializeFeedback(const char* data, int* nextIdOut) 
{
    Feedback* head = NULL;
    int nextId = 1;
    char* copy = strdup(data);
    char* line = strtok(copy, "\n");

    int id = 0;
    char name[100], studentId[50], subject[100], feedbackText[2048];

    while (line) 
    {
        if (strncmp(line, "ID:", 3) == 0) id = atoi(line + 3);
        else if (strncmp(line, "Name:", 5) == 0) strcpy(name, line + 5);
        else if (strncmp(line, "StudentID:", 10) == 0) strcpy(studentId, line + 10);
        else if (strncmp(line, "Subject:", 8) == 0) strcpy(subject, line + 8);
        else if (strncmp(line, "Feedback:", 9) == 0) strcpy(feedbackText, line + 9);
        else if (strcmp(line, "===") == 0) 
        {
            head = addFeedback(head, name, studentId, subject, feedbackText, &nextId);
            if (id >= nextId) nextId = id + 1;
        }
        line = strtok(NULL, "\n");
    }

    if (nextIdOut) *nextIdOut = nextId;
    free(copy);
    return head;
}

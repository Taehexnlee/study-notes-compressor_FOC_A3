#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stddef.h>

typedef struct Feedback {
    int id;
    char studentName[100];
    char studentId[50];
    char subject[100];
    char feedback[2048];
    struct Feedback* next;
} Feedback;

// Adds a new feedback to the list
Feedback* addFeedback(Feedback* head, const char* studentName, const char* studentId, const char* subject, const char* feedback, int* nextId);

// Frees the entire feedback list
void freeFeedbackList(Feedback* head);

// Prints all feedback entries
void printAllFeedback(const Feedback* head);

// Finds a feedback entry by ID
Feedback* findFeedbackById(Feedback* head, int id);

// Deletes a feedback entry by ID
Feedback* deleteFeedbackById(Feedback* head, int id);

// Converts linked list to a string buffer for saving
char* serializeFeedback(const Feedback* head, size_t* outLength);

// Parses a buffer and reconstructs the feedback list
Feedback* deserializeFeedback(const char* data, int* nextIdOut);

#endif // FEEDBACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fileio.h"

// Save data to a file in binary write mode.
// Returns 0 on success, 1 on failure.
int saveToFile(const char* fileName, const char* data, size_t len) 
{
    FILE* fp = fopen(fileName, "wb");
    // Failed to open file
    if (!fp) return 1;
    // Write len bytes from data
    fwrite(data, 1, len, fp);
    fclose(fp);
    return 0;
}

// Load data from a file in binary read mode.
// Returns a dynamically allocated buffer containing the file contents.
// The length of the data is stored in `lenOut`.
char* loadFromFile(const char* fileName, size_t* lenOut) 
{
    FILE* fp = fopen(fileName, "rb");
    // Failed to open file
    if (!fp) return NULL;

    // Move to end of file
    fseek(fp, 0, SEEK_END);        
    // Get file size
    long len = ftell(fp);          
    // Move back to start
    rewind(fp);                    

    // Allocate memory (+1 for null terminator)
    char* buffer = malloc(len + 1);  
    if (!buffer) 
    {
        fclose(fp);
        return NULL;
    }

    // Read file into buffer
    fread(buffer, 1, len, fp);     
    // Null-terminate the buffer
    buffer[len] = '\0';           
    fclose(fp);

    // Output length if pointer provided
    if (lenOut) *lenOut = len;   
    return buffer;
}
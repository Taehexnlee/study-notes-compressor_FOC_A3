#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"

// Compress a string using Run-Length Encoding (RLE).
// Example: "aaabb" → "a3b2"
char* compress(const char* input) 
{
    size_t len = strlen(input);
    // Allocate enough space (worst case: twice the input length)
    char* output = malloc(2 * len + 1);
    if (!output) return NULL;

    int count = 1, j = 0;
    for (size_t i = 1; i <= len; i++) 
    {
        if (input[i] == input[i - 1]) 
        {
            count++;
        } else 
        {
            j += sprintf(&output[j], "%c%d", input[i - 1], count);
            count = 1;
        }
    }

    output[j] = '\0';
    return output;
}

// Decompress a string encoded with RLE.
// Example: "a3b2" → "aaabb"
char* decompress(const char* input) 
{
    char* output = malloc(10000);  // Allocate large buffer for decompression
    if (!output) return NULL;

    int j = 0;
    for (size_t i = 0; input[i]; i++) 
    {
        char ch = input[i];
        int count = 0;

        // Read number following the character
        while (input[++i] >= '0' && input[i] <= '9') 
        {
            count = count * 10 + (input[i] - '0');
        }
        i--;  // Step back to correct the pointer

        // Repeat character 'count' times
        for (int k = 0; k < count; k++) 
        {
            output[j++] = ch;
        }
    }

    output[j] = '\0';
    return output;
}
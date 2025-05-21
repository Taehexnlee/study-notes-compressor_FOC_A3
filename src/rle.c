#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rle.h"

// Custom isdigit replacement
int myIsDigit(char c) 
{
    return c >= '0' && c <= '9';
}

// Replaces ':' with "[COLON]" before compression to avoid format conflicts
void escapeText(char* text) 
{
    char* temp = malloc(strlen(text) * 7 + 1); // Max possible expansion
    if (!temp) return;

    size_t j = 0;
    for (size_t i = 0; i < strlen(text); ++i) 
    {
        if (text[i] == ':') 
        {
            strcpy(&temp[j], "[COLON]");
            j += strlen("[COLON]");
        } else 
        {
            temp[j++] = text[i];
        }
    }
    temp[j] = '\0';
    strcpy(text, temp);
    free(temp);
}

// Replaces "[COLON]" back to ':' after decompression
void unescapeText(char* text) 
{
    char* result = malloc(strlen(text) + 1);
    if (!result) return;

    size_t i = 0, j = 0;
    while (text[i]) 
    {
        if (strncmp(&text[i], "[COLON]", 7) == 0) 
        {
            result[j++] = ':';
            i += 7;
        } else 
        {
            result[j++] = text[i++];
        }
    }
    result[j] = '\0';
    strcpy(text, result);
    free(result);
}

// Run-Length Encoding compression:
// For example: "aaaa" → "a#4", "abc" → "abc"
char* compress(const char* input, size_t* outLen) 
{
    size_t len = strlen(input);
    char* output = malloc(len * 4 + 1); // Generous allocation
    if (!output) return NULL;

    size_t outIdx = 0;
    for (size_t i = 0; i < len;) 
    {
        char ch = input[i];
        int count = 1;
        while (i + count < len && input[i + count] == ch) count++;

        if (count >= 3) 
        {
            outIdx += sprintf(output + outIdx, "%c#%d", ch, count);
        } else 
        {
            for (int j = 0; j < count; ++j) 
            {
                output[outIdx++] = ch;
            }
        }
        i += count;
    }

    output[outIdx] = '\0';
    if (outLen) *outLen = outIdx;
    return output;
}

// Run-Length Encoding decompression:
// For example: "a#4" → "aaaa"
char* decompress(const char* input, size_t* outLen) 
{
    size_t len = strlen(input);
    char* output = malloc(len * 10 + 1); // Allocate safely for expansion
    if (!output) return NULL;

    size_t outIdx = 0;
    for (size_t i = 0; i < len;) 
    {
        char ch = input[i++];

        if (i < len && input[i] == '#') 
        {
            i++; // Skip '#'
            int count = 0;
            while (i < len && myIsDigit(input[i])) 
            {
                count = count * 10 + (input[i++] - '0');
            }

            // Safety check: invalid count or overflow
            if (count <= 0 || outIdx + count > len * 10) 
            {
                fprintf(stderr, "Invalid RLE format or corrupted count\n");
                free(output);
                return NULL;
            }

            for (int j = 0; j < count; ++j) 
            {
                output[outIdx++] = ch;
            }
        } else 
        {
            output[outIdx++] = ch;
        }
    }

    output[outIdx] = '\0';
    if (outLen) *outLen = outIdx;
    return output;
}
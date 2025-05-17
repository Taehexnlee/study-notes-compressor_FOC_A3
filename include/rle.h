#ifndef RLE_H
#define RLE_H

#include <stddef.h>

// Compresses the input string using Run-Length Encoding (RLE).
// Returns a newly allocated compressed string.
// The out_len parameter receives the length of the compressed output.
char* compress(const char* input, size_t* out_len);

// Decompresses a string encoded with RLE.
// Returns a newly allocated decompressed string.
// The out_len parameter receives the length of the decompressed output.
char* decompress(const char* input, size_t* out_len);

// Replaces all ':' characters in the input string with "[COLON]"
// This avoids conflicts with RLE parsing logic.
void sanitize_input(char* text);

// Reverts "[COLON]" back to ':' in the input string after decompression.
void desanitize_output(char* text);

#endif // RLE_H
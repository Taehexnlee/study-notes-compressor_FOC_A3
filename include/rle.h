#ifndef RLE_H
#define RLE_H

// Compresses a string using Run-Length Encoding (RLE)
char* compress(const char* input);

// Decompresses a Run-Length Encoded string
char* decompress(const char* input);

#endif
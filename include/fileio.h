#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h> // for size_t

// Saves binary data to a file.
// Parameters:
//   - fileName: name of the file to write to
//   - data: pointer to the data to be written
//   - len: number of bytes to write
// Returns 0 on success, 1 on failure.
int saveToFile(const char* fileName, const char* data, size_t len);

// Loads binary data from a file into a newly allocated buffer.
// Parameters:
//   - fileName: name of the file to read from
//   - lenOut: pointer to store the length of the data read
// Returns a pointer to the allocated buffer containing the file contents,
// or NULL if the operation fails. Caller is responsible for freeing the buffer.
char* loadFromFile(const char* fileName, size_t* lenOut);

#endif // FILEIO_H
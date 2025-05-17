#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h> // for size_t

// Saves binary data to a file.
// Parameters:
//   - filename: name of the file to write to
//   - data: pointer to the data to be written
//   - len: number of bytes to write
// Returns 0 on success, 1 on failure.
int save_to_file(const char* filename, const char* data, size_t len);

// Loads binary data from a file into a newly allocated buffer.
// Parameters:
//   - filename: name of the file to read from
//   - len_out: pointer to store the length of the data read
// Returns a pointer to the allocated buffer containing the file contents,
// or NULL if the operation fails. Caller is responsible for freeing the buffer.
char* load_from_file(const char* filename, size_t* len_out);

#endif // FILEIO_H
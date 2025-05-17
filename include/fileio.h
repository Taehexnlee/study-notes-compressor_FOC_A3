#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>

int save_to_file(const char* filename, const char* data, size_t len);
char* load_from_file(const char* filename, size_t* len_out);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "../include/fileio.h"

int save_to_file(const char* filename, const char* data, size_t len) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) return -1;

    size_t written = fwrite(data, sizeof(char), len, fp);
    fclose(fp);

    return (written == len) ? 0 : -1;
}

char* load_from_file(const char* filename, size_t* len_out) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    char* buffer = malloc(size + 1);  
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, sizeof(char), size, fp);
    buffer[size] = '\0';
    fclose(fp);

    if (len_out) *len_out = size;
    return buffer;
}
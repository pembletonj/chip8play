
#ifndef FILE_H
#define FILE_H

#include <bits/stdint-uintn.h>
#include <stddef.h>
#include <stdint.h>

int read_to_memory(const char* filename, uint8_t* memory, size_t start, size_t max_size);

#endif

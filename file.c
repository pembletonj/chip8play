
#include "file.h"

#include <stdio.h>
#include <stdlib.h>

int read_to_memory(const char* filename, uint8_t* memory, size_t start, size_t max_size) {

	FILE* file = fopen(filename, "rb");

	if (file == NULL) {
		printf("[E] Failed to open file: %s\n", filename);
		return EXIT_FAILURE;
	}

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (size > max_size) {
		printf("[E] File size is greater than available memory.\n");
		printf("\tFile: %s\n", filename);
		printf("\tSize: %zu\n", size);
		printf("\tMax size: %zu\n", max_size);
		fclose(file);
		return EXIT_FAILURE;
	}

	size_t i = 0;
	while (fread(memory + start + i, 1, 1, file)) {
		i++;
		if (i > size) {
			printf("[E] File size larger than expected.\n");
			printf("\tFile: %s\n", filename);
			printf("\tExpected size: %zu\n", size);
			fclose(file);
			return EXIT_FAILURE;
		}
	}

	printf("[I] Read file: %s\n", filename);

	fclose(file);
	return EXIT_SUCCESS;

}

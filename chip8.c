
#include "chip8.h"
#include <stdlib.h>

struct Chip8 create_chip8(uint16_t memory_size) {

	struct Chip8 chip8;
	
	chip8.memory = (uint8_t*) malloc(sizeof(uint8_t) * memory_size);
	chip8.memory_size = memory_size;

	for (size_t i = 0; i < chip8.memory_size; i++) {
		*(chip8.memory + i) = 0;
	}
	
	chip8.delay_timer = 0;
	chip8.sound_timer = 0;

	chip8.i = 0;
	chip8.sp = 0;

	for (int i = 0; i < 16; i++) {
		chip8.v[i] = 0;
		chip8.keys[i] = false;
	}

	for (int i = 0; i < 12; i++) {
		chip8.stack[i] = 0;
	}

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 64; j++) {
			chip8.screen[i][j] = 0;
		}
	}

	return chip8;

}

void destroy_chip8(struct Chip8* chip8) {

	free(chip8->memory);

}

int next_update(struct Chip8 *chip8, bool *quit) {

	if (chip8->pc + 1 >= chip8->memory_size) {
		*quit = true;
		printf("[E] Program counter outside of available memory. Quitting.\n");
		return EXIT_FAILURE;
	}

}

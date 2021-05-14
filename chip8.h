
#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>



struct Chip8 {

	uint8_t* memory;
	uint16_t memory_size;

	uint8_t v[16];
	uint16_t i;

	uint16_t stack[12];
	uint8_t sp;
	uint16_t pc;

	uint8_t delay_timer;
	uint8_t sound_timer;

	bool keys[16];
	bool screen[32][64];

};

struct Chip8 create_chip8(uint16_t memory_size);
void destroy_chip8(struct Chip8* chip8);
int next_update(struct Chip8* chip8, bool* quit);

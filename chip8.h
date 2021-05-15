
#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>



struct Chip8 {

	uint8_t memory[4096];

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

struct Chip8 create_chip8();
void next_update(struct Chip8* chip8, bool* quit, int* exit_status);


#include "chip8.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



struct Chip8 create_chip8() {

	struct Chip8 chip8;
	
	for (size_t i = 0; i < 4096; i++) {
		chip8.memory[i] = 0;
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

void next_update(struct Chip8 *chip8, bool *quit, int* exit_status) {

	if (chip8->pc + 1 >= 4096) {
		printf("[E] Program counter outside of available memory. Quitting.\n");
		*exit_status = EXIT_FAILURE;
		*quit = true;
		return;
	}

	uint16_t opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];
	chip8->pc += 2;

	switch (opcode & 0xF000) {
		case 0x0000:
			switch (opcode & 0x00FF) {
				case 0x00E0:
					printf("00E0: Clear screen.\n");
					break;
				case 0x00EE:
					printf("00EE: Return.\n");
					/*if (chip8->sp == 0) {
						printf("[W] Returned with sp=0. Quitting.\n");
						return EXIT_SUCCESS;
					}
					pc = chip8->stack[chip8->sp - 1];
					sp--;*/
					break;
				default:
					printf("0NNN: Call machine code.\n");
			}

			break;
		case 0x1000:
			printf("1NNN: Go to address.\n");
			break;
		case 0x2000:
			printf("2NNN: Call subroutine.\n");
			break;
		case 0x3000:
			printf("3XNN: Condition.\n");
			break;
		case 0x4000:
			printf("4XNN: Condition.\n");
			break;
		case 0x5000:
			printf("5XY0: Condition.\n");
			break;
		case 0x6000:
			printf("6XNN: Set register.\n");
			break;
		case 0x7000:
			printf("7XNN: Add to regisiter.\n");
			break;
		case 0x8000:
			switch (opcode & 0x000F) {
				case 0x0000:
					printf("8XY0: Set register.\n");
					break;
				case 0x0001:
					printf("8XY1: Bitwise OR.\n");
					break;
				case 0x0002:
					printf("8XY2: Bitwise AND.\n");
					break;
				case 0x0003:
					printf("8XY3: Bitwise XOR.\n");
					break;
				case 0x0004:
					printf("8XY4: Add to regisiter.\n");
					break;
				case 0x0005:
					printf("8XY5: Subtract from register.\n");
					break;
				case 0x0006:
					printf("8XY6: Right shift.\n");
					break;
				case 0x0007:
					printf("8XY7: Vx=Vy-Vx\n");
					break;
				case 0x000E:
					printf("8XYE: Left shift.\n");
					break;
				default:
					printf("[E] Unknown instruction: %x\n", opcode);
					*quit = true;
					*exit_status = EXIT_FAILURE;
					return;
			}
			
			break;
		case 0x9000:
			switch (opcode & 0x000F) {
				case 0x0000:
					printf("9XY0: Condition.\n");
				default:
					printf("[E] Unknown instruction: %x\n", opcode);
					*quit = true;
					*exit_status = EXIT_FAILURE;
					return;
			}
			break;
		case 0xA000:
			printf("ANNN: Set I to address.\n");
			break;
		case 0xB000:
			printf("BNNN: Jump to an address + V0.\n");
			break;
		case 0xC000:
			printf("CXNN: Generate a random number.\n");
			break;
		case 0xD000:
			printf("DXYN: Draw a sprite.\n");
			break;
		case 0xE000:
			switch (opcode & 0x00FF) {
				case 0x009E:
					printf("EX9E: Condition.\n");
					break;
				case 0x00A1:
					printf("EXA1: Condition.\n");
					break;
				default:
					printf("[E] Unknown instruction: %x\n", opcode);
					*quit = true;
					*exit_status = EXIT_FAILURE;
					return;
			}
			break;
		case 0xF000:
			switch (opcode & 0x00F0) {
				case 0x0000:
					switch (opcode & 0x000F) {
						case 0x0007:
							printf("FX07: Set register to value of delay timer.\n");
							break;
						case 0x000A:
							printf("FX0A: Wait for key press.\n");
							break;
						default:
							printf("[E] Unknown instruction: %x\n", opcode);
							*quit = true;
							*exit_status = EXIT_FAILURE;
							return;
					}
					break;
				case 0x0010:
					switch (opcode & 0x000F) {
						case 0x0005:
							printf("FX15: Set the delay timer.\n");
							break;
						case 0x0008:
							printf("FX18: Set the sound timer.\n");
							break;
						case 0x000E:
							printf("FX1E: Add VX to I.\n");
							break;
						default:
							printf("[E] Unknown instruction: %x\n", opcode);
							*quit = true;
							*exit_status = EXIT_FAILURE;
							return;
					}
					break;
				case 0x0020:
					switch (opcode & 0x000F) {
						case 0x0009:
							printf("FX29: Set I to the location of a character sprite.\n");
							break;
						default:
							printf("[E] Unknown instruction: %x\n", opcode);
							*quit = true;
							*exit_status = EXIT_FAILURE;
							return;
					}
					break;
				case 0x0030:
					switch (opcode & 0x000F) {
						case 0x0003:
							printf("FX33\n");
							break;
						default:
							printf("[E] Unknown instruction: %x\n", opcode);
							*quit = true;
							*exit_status = EXIT_FAILURE;
							return;
					}
					break;
				case 0x0050:
					switch (opcode & 0x000F) {
						case 0x0005:
							printf("FX55: Store V0 to VX in address I.\n");
							break;
						default:
							printf("[E] Unknown instruction: %x\n", opcode);
							*quit = true;
							*exit_status = EXIT_FAILURE;
							return;
					}
					break;
				case 0x0060:
					switch (opcode & 0x000F) {
						case 0x0005:
							printf("FX65: Fill V0 to VX with the values from address I.\n");
							break;
						default:
							printf("[E] Unknown instruction: %x\n", opcode);
							*quit = true;
							*exit_status = EXIT_FAILURE;
							return;
					}
					break;
				default:
					printf("[E] Unknown instruction: %x\n", opcode);
					*quit = true;
					*exit_status = EXIT_FAILURE;
					return;
			}
			break;
		default:
			printf("[E] Unknown instruction: %x\n", opcode);
			*quit = true;
			*exit_status = EXIT_FAILURE;
			return;
	}

	*exit_status = EXIT_SUCCESS;

}

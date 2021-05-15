
#include "chip8.h"
#include "file.h"
#include "display.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: ch8play <filename>\n");
		return EXIT_FAILURE;
	}

	// Initialize SDL2 video.

	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("[E] Failed to initialize video:\n");
		printf("\t%s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	printf("[I] Initialized video.\n");

	// Initialize SDL2 audio.

	if (SDL_Init(SDL_INIT_AUDIO)) {
		printf("[W] Failed to initialize audio:\n");
		printf("\t%s\n", SDL_GetError());
	}
	else {
		printf("[I] Initialized audio.\n");
	}

	// Create the window.
	
	struct Display display;
	if (create_window("CHIP-8", 800, 400, &display)) {
		return EXIT_FAILURE;
	}
		
	// Create the machine.

	struct Chip8 chip8 = create_chip8();
	printf("[I] Created CHIP-8 machine.\n");

	if (read_to_memory(argv[1], chip8.memory, 0x200, 0x1000 - 0x300)) {
		return EXIT_FAILURE;
	}

	/*for (size_t i = 0; i < chip8.memory_size; i++) {
		printf("%lx: %x\n", i, *(chip8.memory + i));
	}*/

	// Run

	chip8.pc = 0x200;
	bool quit = false;
	int exit_status = EXIT_SUCCESS;
	Uint32 end_time;
	Uint32 start_time;
	Uint32 update_period = 1000;

	while (!quit) {
		start_time = SDL_GetTicks();
		next_update(&chip8, &quit, &exit_status);
		end_time = SDL_GetTicks();
		SDL_Delay(update_period - (end_time - start_time));
	}

	// Clean up

	destroy_display(&display);
	SDL_Quit();

	return exit_status;

}

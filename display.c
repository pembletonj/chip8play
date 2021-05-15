
#include "display.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>



int create_window(const char* title, Uint32 width, Uint32 height, struct Display* display) {

	if (width == 0 || height == 0) {
		printf("[E] The window cannot have a width or height of 0.\n");
		return EXIT_FAILURE;
	}

	display->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);

	if (display->window == NULL) {
		printf("[E] Failed to create window:\n");
		printf("\t%s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);

	display->width = width;
	display->height = height;

	display->top_left_block.x = 0;
	display->top_left_block.y = 0;

	if (width < 2 * height) {
		display->top_left_block.w = width / 64;
		display->top_left_block.h = width / 64;
	}
	else {
		display->top_left_block.w = height / 32;
		display->top_left_block.h = height / 32;
	}

	printf("[I] Created window.\n");
	return EXIT_SUCCESS;

}

void destroy_display(struct Display* display) {

	SDL_DestroyRenderer(display->renderer);
	SDL_DestroyWindow(display->window);

}



SDL_Rect generate_rect(int x, int y, struct Display* display) {
	SDL_Rect rect = display->top_left_block;
	rect.x += x * rect.w;
	rect.y += y * rect.h;
	return rect;
}

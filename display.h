
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>



struct Display {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 width;
	Uint32 height;
	SDL_Rect top_left_block;
};



int create_window(const char* title, Uint32 width, Uint32 height, struct Display* display);
void destroy_display(struct Display* display);

SDL_Rect generate_rect(int x, int y, struct Display* display);

#endif

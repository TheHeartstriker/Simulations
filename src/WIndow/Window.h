#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void closeSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif
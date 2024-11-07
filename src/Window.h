#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL2/SDL.h>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void closeSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif
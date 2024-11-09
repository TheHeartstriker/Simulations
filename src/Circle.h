#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

void draw(SDL_Renderer* renderer, int cx, int cy, int radius);
void initializeCircles(int numCircles);
void CircleLoop(SDL_Renderer* renderer, float TimeFrame, SDL_Window* window);

#endif
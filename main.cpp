#include <SDL2/SDL.h>

#include "Circle.h"
#include "Window/Window.h"

int main(int argc, char* argv[]) {
  // Initialize SDL with video subsystem
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  if (!initSDL(window, renderer)) {
    return -1;
  }
  // The window is open: enter program loop (see SDL_PollEvent)
  SDL_Event e;
  bool quit = false;

  initializeCircles(10);

  while (!quit) {
    // Check for events
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    // Clear the screen with black color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Circle loop
    CircleLoop(renderer);

    SDL_RenderPresent(renderer);
    // FrameRate set to 60fps
    SDL_Delay(16);
  }

  closeSDL(window, renderer);

  return 0;
}
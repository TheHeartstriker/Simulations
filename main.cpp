#include <SDL2/SDL.h>
#include <Window.h>

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

  while (!quit) {
    // Check for events
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    // Main loop
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  closeSDL(window, renderer);

  return 0;
}
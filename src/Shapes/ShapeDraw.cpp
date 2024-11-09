#include "Shapes/ShapeDraw.h"

void draw(SDL_Renderer* renderer, int cx, int cy, int radius) {
  // Set draw color to white
  SDL_SetRenderDrawColor(renderer, 250, 5, 5, 0);  // RGBA

  // Midpoint Circle Algorithm
  int x = radius;
  int y = 0;
  int MidPoint =
      1 - x;  // Decision criterion divided by 2 evaluated at x=r, y=0

  while (y <= x) {
    // Draw horizontal lines to fill the circle
    SDL_RenderDrawLine(renderer, cx - x, cy + y, cx + x, cy + y);
    SDL_RenderDrawLine(renderer, cx - y, cy + x, cx + y, cy + x);
    SDL_RenderDrawLine(renderer, cx - x, cy - y, cx + x, cy - y);
    SDL_RenderDrawLine(renderer, cx - y, cy - x, cx + y, cy - x);

    y++;
    // Inside
    if (MidPoint <= 0) {
      MidPoint += 2 * y + 1;  // Change in decision criterion for y -> y+1
    } else
    // Outside
    {
      x--;
      MidPoint += 2 * (y - x) + 1;  // Change for y -> y+1, x -> x-1
    }
  }
}
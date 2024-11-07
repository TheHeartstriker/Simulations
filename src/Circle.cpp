#include "Circle.h"

// Define the functions

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

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

// Create a random number generator
std::random_device rd;   // Seed
std::mt19937 gen(rd());  // Standard mersenne_twister_engine
std::uniform_int_distribution<> dis(0, 999);

// Define a Circle struct
struct Circle {
  float Currentx;
  float Currenty;
  float Targetx;  // Change to float for consistency
  float Targety;  // Change to float for consistency
};

std::vector<Circle> circles;

// Initialize 10 circles
void initializeCircles(int numCircles) {
  std::cout << "ran";
  for (int i = 0; i < numCircles; ++i) {
    circles.push_back(
        {static_cast<float>(dis(gen)), static_cast<float>(dis(gen)),
         static_cast<float>(dis(gen)), static_cast<float>(dis(gen))});
  }
}

int test = 69;

// Update the circle's position
void CircleLoop(SDL_Renderer* renderer) {
  for (int i = 0; i < circles.size(); i++) {
    float dx = circles[i].Targetx - circles[i].Currentx;
    float dy = circles[i].Targety - circles[i].Currenty;
    float Distance = sqrt(dx * dx + dy * dy);

    draw(renderer, circles[i].Currentx, circles[i].Currenty, 25);
    if (Distance < 10) {
      circles[i].Targetx = static_cast<float>(dis(gen));
      circles[i].Targety = static_cast<float>(dis(gen));
    } else {
      float lerp = 0.03;  // Temporarily increased lerp value for testing
      circles[i].Currentx += dx * lerp;
      circles[i].Currenty += dy * lerp;
    }
  }
}
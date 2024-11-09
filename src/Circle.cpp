#include "Circle.h"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "Shapes/ShapeDraw.h"

// Create a random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 999);

struct Circle {
  float Currentx;  // This is the current circles location
  float Currenty;  // This is the current circles location
  float VelocityY;
  float VelocityX;
};
const float Gravity = 9.8f;

static std::vector<Circle> circles;

// Initialize 10 circles
void initializeCircles(int numCircles) {
  std::cout << "ran";
  for (int i = 0; i < numCircles; ++i) {
    circles.push_back({
        static_cast<float>(dis(gen)),
        static_cast<float>(dis(gen)),
        0,
        50,
    });
  }
}

void SubStep(Circle& circle) {
  for (int i = 0; i < circles.size(); i++) {
    if (&circle == &circles[i]) continue;

    float dx = circle.Currentx - circles[i].Currentx;
    float dy = circle.Currenty - circles[i].Currenty;
    float Distance = sqrt(dx * dx + dy * dy);
    float CombinedRadius = 10 + 10;
    if (Distance <= CombinedRadius || circle.Currentx <= 0 ||
        circle.Currentx >= 1000 || circle.Currenty <= 0 ||
        circle.Currenty >= 1000) {
      // Collision detected
      // Calculate the normal vector
      float nx = dx / Distance;
      float ny = dy / Distance;

      // Calculate the relative velocity
      float relativeVelocityX = circle.VelocityX - circles[i].VelocityX;
      float relativeVelocityY = circle.VelocityY - circles[i].VelocityY;

      // Calculate the relative velocity in terms of the normal direction
      float dotProduct = relativeVelocityX * nx + relativeVelocityY * ny;

      // Do not resolve if velocities are separating
      if (dotProduct > 0) {
        continue;
      }

      // Calculate the impulse for both circles
      float impulse = (2.0f * dotProduct) / (1 + 1);

      // Apply the impulse
      circle.VelocityX -= impulse * 1 * nx;
      circle.VelocityY -= impulse * 1 * ny;
      circle.Currentx += nx;
      circle.Currenty += ny;
    }
  }
}

void WindowDetection(Circle& circle, int WindowWidth, int WindowHeight) {
  float radius = 10.0f;
  if (circle.Currentx - radius < 0) {
    circle.Currentx = radius;
    circle.VelocityX *= -1;
  } else if (circle.Currentx + radius > WindowWidth) {
    circle.Currentx = WindowWidth - radius;
    circle.VelocityX *= -1;
  }

  if (circle.Currenty - radius < 0) {
    circle.Currenty = radius;
    circle.VelocityY *= -1;
  } else if (circle.Currenty + radius > WindowHeight) {
    circle.Currenty = WindowHeight - radius;
    circle.VelocityY *= -1;
  }
}

// Update the circle's position
void CircleLoop(SDL_Renderer* renderer, float TimeFrame, SDL_Window* window) {
  int WindowWidth, WindowHeight;
  SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
  for (int i = 0; i < circles.size(); i++) {
    WindowDetection(circles[i], WindowWidth, WindowHeight);
    SubStep(circles[i]);

    // Apply gravity based on vertical velocity and time
    circles[i].VelocityY += Gravity * TimeFrame;

    // Update the circle's position based on velocity and time
    circles[i].Currentx += circles[i].VelocityX * TimeFrame;
    circles[i].Currenty += circles[i].VelocityY * TimeFrame;

    draw(renderer, circles[i].Currentx, circles[i].Currenty, 10);
  }
}
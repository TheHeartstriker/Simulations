#include "Circle.h"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "Shapes/ShapeDraw.h"

extern int MouseX;
extern int MouseY;

float radius = 50.0f;

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

// Initialize circles
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
// Is given a circle and checks it compared to all other circles apart from
// itself
void Collider(Circle& circle) {
  for (int i = 0; i < circles.size(); i++) {
    if (&circle == &circles[i]) continue;

    float dx = circle.Currentx - circles[i].Currentx;
    float dy = circle.Currenty - circles[i].Currenty;
    float Distance = sqrt(dx * dx + dy * dy);
    float CombinedRadius = radius + radius;
    if (Distance <= CombinedRadius) {
      // Calculate the overlap distance that needs to be added to both balls
      float fOverlap = 0.5f * (CombinedRadius - Distance);
      // Displacemeant current balls x and y
      circle.Currentx += fOverlap * (dx / Distance);
      circle.Currenty += fOverlap * (dy / Distance);
      // Displacement of the contacted ball's x and y
      circles[i].Currentx -= fOverlap * (dx / Distance);
      circles[i].Currenty -= fOverlap * (dy / Distance);
    }
  }
}

void WindowDetection(Circle& circle, int WindowWidth, int WindowHeight) {
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

void MouseDetection(Circle& circle, int MouseX, int MouseY, float Radius) {
  if (MouseX != -1 && MouseY != -1) {
    float dx = MouseX - circle.Currentx;
    float dy = MouseY - circle.Currenty;
    float Distance = sqrt(dx * dx + dy * dy);
    if (Distance < Radius) {
      std::cout << "MouseDetection" << std::endl;
      circle.Currentx = MouseX;
      circle.Currenty = MouseY;
    }
  }
}

// Update the circle's position
void CircleLoop(SDL_Renderer* renderer, float TimeFrame, SDL_Window* window) {
  int WindowWidth, WindowHeight;
  SDL_GetWindowSize(window, &WindowWidth, &WindowHeight);
  for (int i = 0; i < circles.size(); i++) {
    WindowDetection(circles[i], WindowWidth, WindowHeight);
    MouseDetection(circles[i], MouseX, MouseY, radius);
    Collider(circles[i]);

    // Apply gravity based on vertical velocity and time
    circles[i].VelocityY += Gravity * TimeFrame;

    // Update the circle's position based on velocity and time
    circles[i].Currentx += circles[i].VelocityX * TimeFrame;
    circles[i].Currenty += circles[i].VelocityY * TimeFrame;

    draw(renderer, circles[i].Currentx, circles[i].Currenty, radius);
  }
}
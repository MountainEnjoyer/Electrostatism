#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> //random
#include <time.h>

#define WIDTH 1200
#define HEIGHT 600
#define FPS 60
#define NUM_CHARGES 30
#define SPEED 20

typedef struct {
  float x, y, radius, vx, vy, fx, fy;  
  int charge; // pos or neg
} Charge;

Charge charge[NUM_CHARGES];

void InitCharges() {
  float r = 10;
  for (int i = 0; i<NUM_CHARGES; i++) {
    charges[i].radius = r;
    charges[i].x = GetRandomValue(r, WIDTH-r);
    charges[i].y = GetRandomValue(r, HEIGHT-r);
    charges[i].fx = GetRandomValue(-SPEED, SPEED);
    charges[i].fy = GetRandomValue(-SPEED, SPEED);

  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, "Coulomb Force Simulation");

  SetTargetFPS(FPS); // CPU Usage
  InitCharges();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

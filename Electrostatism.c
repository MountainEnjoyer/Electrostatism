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

Charge charges[NUM_CHARGES];

void InitCharges() {
  float r = 10;
  for (int i = 0; i<NUM_CHARGES; i++) {
    charges[i].radius = r;
    charges[i].x = GetRandomValue(r, WIDTH-r);
    charges[i].y = GetRandomValue(r, HEIGHT-r);
    charges[i].vx = GetRandomValue(-SPEED, SPEED);
    charges[i].vy = GetRandomValue(-SPEED, SPEED);
    charges[i].fx = 0;
    charges[i].fy = 0;
    charges[i].charge = 1;
  }
}

void DrawCharges(){
  Color color;
  for (int i = 0; i<NUM_CHARGES; i++) {
    switch (charges[i].charge) {
      case 1:
        color = RED;
        break;
      case -1:
        color = BLUE;
        break;
    }
    DrawCircle(charges[i].x, charges[i].y, charges[i].radius, color);
  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, "Coulomb Force Simulation");

  SetTargetFPS(FPS); // CPU Usage
  InitCharges();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCharges();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

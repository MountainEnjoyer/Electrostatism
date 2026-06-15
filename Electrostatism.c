#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> //random
#include <time.h>

#define WIDTH 1200
#define HEIGHT 600

int main() {
  InitWindow(WIDTH, HEIGHT, "Eletrostatism Simulation");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

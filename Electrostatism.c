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
#define FACTOR 5000

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

void ComputeForce() {
  Charge *c1;
  Charge *c2;

  for (int i=0; i<NUM_CHARGES; i++) {
    c1 = &charges[i];
    
    for (int j=i+1; j<NUM_CHARGES; j++ ) {
      c2 = &charges[j];
      
      // la distance ?
      float dx = c2->x - c1->x;
      float dy = c2->y - c1->y;
      float d2 = dx*dx + dy*dy;

      float d = sqrtf(d2);
      if (d < 1) 
        d =1;

      float nx = dx / d;
      float ny = dy / d;

      float fcoulomb =  FACTOR * c1->charge * c2->charge / d2 ;
      float fx = fcoulomb * nx;
      float fy = fcoulomb * ny;

      c1->fx -= fx;
      c1->fy -= fy;
      c2->fx = fx;
      c2->fy = fy;
    }
  }
}

void ResetForces() {
  Charge *c;
  for (int i = 0; i < NUM_CHARGES; i++) {
    c = &charges[i];

    c->fx = 0;
    c->fy = 0;
  }
}

void UpdateCharges(float dt) {
  Charge *c;
  for (int i = 0; i<NUM_CHARGES; i++) {
    c = &charges[i];
    c->vx += c->fx * dt;
    c->vy += c->fy * dt;
    c->x += c->vx * dt;
    c->y += c->vy * dt;
  }
}

void CollideWalls() {
  Charge *c;
  for (int i = 0; i<NUM_CHARGES; i++) {
    c = &charges[i];

    if (c->x < c->radius) {
      c->x = c->radius;
      c->vx = -c->vx;
    }
    if (c->y < c->radius) {
      c->y = c->radius;
      c->vy = -c->vy;
    }
    if (c->x > WIDTH-c->radius) {
      c->x = WIDTH-c->radius;
      c->vx = -c->vx;
    }
    if (c->y > HEIGHT-c->radius) {
      c->y = HEIGHT-c->radius;
      c->vy = -c->vy;
    }

  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, "Coulomb Force Simulation");

  SetTargetFPS(FPS); // CPU Usage
  InitCharges();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    ResetForces();
    ComputeForce();
    UpdateCharges(GetFrameTime());
    CollideWalls();
    DrawCharges();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

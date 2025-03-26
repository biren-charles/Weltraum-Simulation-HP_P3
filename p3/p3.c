#include <stdio.h>
#include <math.h>

#define G 6.67430e-11 // Gravitational constant
#define DT 0.01       // Time step (seconds)
#define STEPS 1000    // Number of simulation steps

typedef struct {
    double x, y;      // Position (meters)
    double vx, vy;    // Velocity (meters/second)
    double mass;      // Mass (kg)
} Body;

// Function to calculate forces and update velocities and positions
void simulate(Body *b1, Body *b2) {
    for (int step = 0; step < STEPS; step++) {
        // Calculate distance and force
        double dx = b2->x - b1->x;
        double dy = b2->y - b1->y;
        double distance = sqrt(dx * dx + dy * dy);
        double force = G * b1->mass * b2->mass / (distance * distance);
        double fx = force * dx / distance;
        double fy = force * dy / distance;

        // Update velocities
        b1->vx += fx / b1->mass * DT;
        b1->vy += fy / b1->mass * DT;
        b2->vx -= fx / b2->mass * DT;
        b2->vy -= fy / b2->mass * DT;

        // Update positions
        b1->x += b1->vx * DT;
        b1->y += b1->vy * DT;
        b2->x += b2->vx * DT;
        b2->y += b2->vy * DT;

        // Print positions to console
        printf("Step %d:\n", step + 1);
        printf("  Body 1: (%.2f, %.2f)\n", b1->x, b1->y);
        printf("  Body 2: (%.2f, %.2f)\n", b2->x, b2->y);
    }
}

int main() {
    // Define two bodies
    Body body1 = {0, 0, 0, 0, 5e24};    // Large body, stationary initially
    Body body2 = {1e7, 0, 0, 1e3, 1e22}; // Smaller body, with initial velocity

    // Simulate their motion
    simulate(&body1, &body2);

    return 0;
}


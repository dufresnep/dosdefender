// particle.c
#include <stdlib.h>  // For malloc
#include "../include/particle.h" // Include the header file!

Particle* particle_new() {
  Particle* p = (Particle*)malloc(sizeof(Particle)); // Allocate memory dynamically
  if (p == NULL) {
      // Handle memory allocation failure (very important!)
      return NULL; // Or exit, or take appropriate action
  }

  p->x = 15;
  p->y = 33;
  p->vx = 3;
  p->vy = -1;
  return p; // Return the pointer to the allocated memory
}

// particle.h
#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct {
    float x, y;
    float vx, vy;
    int color;
} Particle;

Particle* particle_new();

#endif

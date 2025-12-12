#include "Smoke.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

#define M_PI 3.14159265358979323846f

Smoke::Smoke() : x(0), y(0), spawnTimer(0), spawnInterval(0.05f), active(false) {}

Smoke::Smoke(float startX, float startY) : x(startX), y(startY), spawnTimer(0), spawnInterval(0.05f), active(true) {}

// Activates smoke at new position
void Smoke::spawn(float newX, float newY) {
    x = newX;
    y = newY;
    if (!active) {
        active = true;
        spawnTimer = 0;
    }
}

// Stops spawning new particles
void Smoke::stop() {
    active = false;
}

// Updates particle positions and spawns new ones
void Smoke::update(float dt) {
    if (active) {
        spawnTimer += dt;
        if (spawnTimer >= spawnInterval) {
            spawnTimer = 0;
            
            for (int i = 0; i < 3; i++) {
                SmokeParticle p;
                p.x = x + (rand() % 40 - 20);
                p.y = y + (rand() % 20 - 10);
                p.vx = (float)(rand() % 60 - 30);
                p.vy = (float)(rand() % 40 + 20);
                p.size = (float)(rand() % 15 + 10);
                p.alpha = 0.8f;
                p.lifetime = 0;
                p.maxLifetime = 0.8f + (rand() % 100) / 200.0f;
                p.isGray = (rand() % 2 == 0);
                particles.push_back(p);
            }
        }
    }
    
    for (size_t i = 0; i < particles.size(); i++) {
        SmokeParticle& p = particles[i];
        p.x += p.vx * dt;
        p.y += p.vy * dt;
        p.lifetime += dt;
        p.alpha = 0.8f * (1.0f - p.lifetime / p.maxLifetime);
        p.size += 15.0f * dt;
    }
    
    for (int i = (int)particles.size() - 1; i >= 0; i--) {
        if (particles[i].lifetime >= particles[i].maxLifetime) {
            particles.erase(particles.begin() + i);
        }
    }
}

// Draws all smoke particles with fading effect
void Smoke::draw() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (size_t i = 0; i < particles.size(); i++) {
        const SmokeParticle& p = particles[i];
        
        if (p.isGray) {
            glColor4f(0.4f, 0.4f, 0.4f, p.alpha);
        } else {
            glColor4f(0.9f, 0.9f, 0.9f, p.alpha);
        }
        
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(p.x, p.y);
        for (int j = 0; j <= 16; j++) {
            float angle = 2.0f * M_PI * j / 16.0f;
            glVertex2f(p.x + p.size * cosf(angle), p.y + p.size * sinf(angle));
        }
        glEnd();
    }
    
    glDisable(GL_BLEND);
}

bool Smoke::isActive() const {
    return active;
}

bool Smoke::hasParticles() const {
    return !particles.empty();
}

#include "Bullet.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

Bullet::Bullet() : x(0), y(0), vx(0), vy(0), playerBullet(true), active(false) {}

Bullet::Bullet(float startX, float startY, float velX, float velY, bool isPlayerBullet)
    : x(startX), y(startY), vx(velX), vy(velY), playerBullet(isPlayerBullet), active(true) {}

// Updates bullet position based on velocity
void Bullet::update(float dt) {
    if (!active) return;
    x += vx * dt;
    y += vy * dt;
}

// Draws the bullet as a colored circle
void Bullet::draw() {
    if (!active) return;
    
    if (playerBullet) {
        glColor3f(1.0f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 16; i++) {
        float angle = 2.0f * 3.14159f * i / 16;
        glVertex2f(x + 5 * cosf(angle), y + 5 * sinf(angle));
    }
    glEnd();
}

float Bullet::getX() const { return x; }
float Bullet::getY() const { return y; }
bool Bullet::isPlayerBullet() const { return playerBullet; }
bool Bullet::isActive() const { return active; }
void Bullet::deactivate() { active = false; }

bool Bullet::isOffScreen(int screenWidth, int screenHeight) {
    return x < -10 || x > screenWidth + 10 || y < -10 || y > screenHeight + 10;
}

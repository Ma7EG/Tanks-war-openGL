#include "Player.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

Player::Player() : x(150), y(100), cannonAngle(45), cannonLength(60) {}

Player::Player(float startX, float startY) : x(startX), y(startY), cannonAngle(45), cannonLength(60) {}

// Updates cannon angle based on mouse position
void Player::setCannonAngle(float mouseX, float mouseY) {
    float dx = mouseX - x;
    float dy = mouseY - y;
    cannonAngle = atan2f(dy, dx) * 180.0f / M_PI;
    
    if (cannonAngle < 0) cannonAngle = 0;
    if (cannonAngle > 180) cannonAngle = 180;
}

// Draws the player tank with rotating cannon
void Player::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    float scale = 100.0f;
    
    // Body
    glColor3f(0.2f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.45f * scale, -0.1f * scale);
    glVertex2f(0.45f * scale, -0.1f * scale);
    glVertex2f(0.45f * scale, 0.2f * scale);
    glVertex2f(-0.45f * scale, 0.2f * scale);
    glEnd();
    
    // Turret
    float turretY = 0.25f * scale;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(0.2f * scale * cosf(angle), turretY + 0.2f * scale * sinf(angle));
    }
    glEnd();
    
    // Rotating cannon
    glColor3f(0.18f, 0.45f, 0.18f);
    float radAngle = cannonAngle * M_PI / 180.0f;
    float gunLength = 0.5f * scale;
    float gunWidth = 0.04f * scale;
    
    glPushMatrix();
    glTranslatef(0, turretY, 0);
    glRotatef(cannonAngle, 0, 0, 1);
    
    glBegin(GL_QUADS);
    glVertex2f(0, -gunWidth);
    glVertex2f(gunLength, -gunWidth);
    glVertex2f(gunLength, gunWidth);
    glVertex2f(0, gunWidth);
    glEnd();
    
    glPopMatrix();
    
    // Wheels
    glColor3f(0.18f, 0.45f, 0.18f);
    float wheelPos[2] = {-0.3f, 0.3f};
    for (int w = 0; w < 2; w++) {
        float wx = wheelPos[w];
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; i++) {
            float angle = (float)(i * M_PI / 180.0);
            glVertex2f(wx * scale + 0.1f * scale * cosf(angle), 
                      -0.1f * scale + 0.1f * scale * sinf(angle));
        }
        glEnd();
    }
    
    glPopMatrix();
}

// Creates and returns a bullet from the cannon tip
Bullet* Player::shoot() {
    float radAngle = cannonAngle * M_PI / 180.0f;
    float tipX = x + cannonLength * cosf(radAngle);
    float tipY = y + 25 + cannonLength * sinf(radAngle);
    
    float speed = 500.0f;
    float vx = speed * cosf(radAngle);
    float vy = speed * sinf(radAngle);
    
    return new Bullet(tipX, tipY, vx, vy, true);
}

float Player::getX() const { return x; }
float Player::getY() const { return y; }

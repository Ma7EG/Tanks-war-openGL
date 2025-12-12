#include "Enemy.h"
#include "Helicopter.h"
#include "Audio.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

Enemy::Enemy() : x(0), y(0), vx(0), vy(0), targetX(500), reachedTarget(false), health(3), maxHealth(3), type(ENEMY_TANK), 
    shootTimer(0), shootInterval(2.0f), active(false), damage(10), scoreValue(50), dying(false), groundHeight(88) {}

// Creates an enemy of specified type at given position
Enemy::Enemy(EnemyType enemyType, float startX, float startY, float stopX) {
    type = enemyType;
    x = startX;
    y = startY;
    targetX = stopX;
    reachedTarget = false;
    active = true;
    shootTimer = 0;
    dying = false;
    vy = 0;
    groundHeight = 88;
    
    if (type == ENEMY_TANK) {
        health = 3;
        maxHealth = 3;
        damage = 10;
        scoreValue = 50;
        shootInterval = 2.0f;
        vx = -80.0f;
    } else {
        health = 5;
        maxHealth = 5;
        damage = 20;
        scoreValue = 100;
        shootInterval = 1.5f;
        vx = -120.0f;
        reachedTarget = true;
    }
}

// Updates enemy position, handles dying state and smoke for helicopters
void Enemy::update(float dt, int ground) {
    if (!active) return;
    groundHeight = ground;
    
    if (dying) {
        vy -= 150.0f * dt;
        y += vy * dt;
        vx *= 0.98f;
        x += vx * dt;
        
        smoke.spawn(x, y);
        smoke.update(dt);
        
        if (y <= groundHeight + 20) {
            y = (float)(groundHeight + 20);
            smoke.stop();
            smoke.update(dt);
            if (!smoke.hasParticles()) {
                active = false;
            }
        }
        return;
    }
    
    if (type == ENEMY_TANK) {
        if (!reachedTarget) {
            x += vx * dt;
            if (x <= targetX) {
                x = targetX;
                reachedTarget = true;
                vx = 0;
            }
        }
    } else {
        x += vx * dt;
    }
    
    if (reachedTarget) {
        shootTimer += dt;
    }
}

// Draws the enemy (tank or helicopter) with health bar
void Enemy::draw() {
    if (!active) return;
    
    if (dying && type == ENEMY_HELICOPTER) {
        smoke.draw();
    }
    
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    if (type == ENEMY_TANK) {
        float scale = 100.0f;
        glScalef(scale, scale, 1.0f);
        
        glColor3f(0.3f, 0.15f, 0.15f);
        glBegin(GL_QUADS);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(0.45f, -0.1f);
        glVertex2f(0.45f, 0.2f);
        glVertex2f(-0.45f, 0.2f);
        glEnd();
        
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(0.2f * cosf(angle), 0.25f + 0.2f * sinf(angle));
        }
        glEnd();
        
        glColor3f(0.25f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.23f);
        glVertex2f(-0.2f, 0.23f);
        glVertex2f(-0.2f, 0.27f);
        glVertex2f(-0.5f, 0.27f);
        glEnd();
        
        glColor3f(0.2f, 0.1f, 0.1f);
        float wheelPositions[2] = {-0.3f, 0.3f};
        for (int w = 0; w < 2; w++) {
            float wx = wheelPositions[w];
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i <= 360; i++) {
                float angle = i * 3.14159f / 180.0f;
                glVertex2f(wx + 0.1f * cosf(angle), -0.1f + 0.1f * sinf(angle));
            }
            glEnd();
        }
    } else {
        if (dying) {
            float tiltAngle = 15.0f;
            glRotatef(tiltAngle, 0, 0, 1);
        }
        glScalef(1.5f, 1.5f, 1.0f);
        drawHelicopter();
    }
    
    glPopMatrix();
    
    // Health bar
    if (!dying) {
        float barWidth = 50.0f;
        float barHeight = 6.0f;
        float healthPercent = (float)health / maxHealth;
        float barY = (type == ENEMY_TANK) ? y + 45 : y + 50;
        
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_QUADS);
        glVertex2f(x - barWidth/2, barY);
        glVertex2f(x + barWidth/2, barY);
        glVertex2f(x + barWidth/2, barY + barHeight);
        glVertex2f(x - barWidth/2, barY + barHeight);
        glEnd();
        
        glColor3f(1.0f - healthPercent, healthPercent, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(x - barWidth/2, barY);
        glVertex2f(x - barWidth/2 + barWidth * healthPercent, barY);
        glVertex2f(x - barWidth/2 + barWidth * healthPercent, barY + barHeight);
        glVertex2f(x - barWidth/2, barY + barHeight);
        glEnd();
    }
}

// Shoots at player if ready and returns the bullet
Bullet* Enemy::shoot(float playerX, float playerY) {
    if (!active || dying || !reachedTarget || shootTimer < shootInterval) return NULL;
    
    shootTimer = 0;
    
    float dx = playerX - x;
    float dy = playerY - y;
    float dist = sqrtf(dx*dx + dy*dy);
    if (dist < 1) dist = 1;
    
    float speed = 350.0f;
    float bvx = (dx / dist) * speed;
    float bvy = (dy / dist) * speed;
    
    return new Bullet(x, y + 25, bvx, bvy, false);
}

// Reduces health and triggers dying state for helicopters
void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        if (type == ENEMY_HELICOPTER && !dying) {
            dying = true;
            vy = 50.0f;
            vx = -30.0f;
            Audio::playDamageHelicopter();
        } else {
            active = false;
        }
    }
}

bool Enemy::isAlive() const { return health > 0; }
bool Enemy::isActive() const { return active; }
bool Enemy::isDying() const { return dying; }
void Enemy::deactivate() { active = false; }
float Enemy::getX() const { return x; }
float Enemy::getY() const { return y; }
int Enemy::getScoreValue() const { return scoreValue; }
EnemyType Enemy::getType() const { return type; }

bool Enemy::isOffScreen(int screenWidth) {
    return x < -100 || x > screenWidth + 100;
}

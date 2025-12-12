#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "Bullet.h"
#include "Smoke.h"

enum EnemyType {
    ENEMY_TANK = 0,
    ENEMY_HELICOPTER = 1
};

class Enemy {
private:
    float x, y;
    float vx, vy;
    float targetX;
    bool reachedTarget;
    int health;
    int maxHealth;
    EnemyType type;
    float shootTimer;
    float shootInterval;
    bool active;
    int damage;
    int scoreValue;
    bool dying;
    Smoke smoke;
    int groundHeight;

public:
    Enemy();
    Enemy(EnemyType enemyType, float startX, float startY, float stopX);
    
    void update(float dt, int ground);
    void draw();
    Bullet* shoot(float targetX, float targetY);
    
    void takeDamage(int amount);
    bool isAlive() const;
    bool isActive() const;
    bool isDying() const;
    void deactivate();
    
    float getX() const;
    float getY() const;
    int getScoreValue() const;
    EnemyType getType() const;
    
    bool isOffScreen(int screenWidth);
};

#endif

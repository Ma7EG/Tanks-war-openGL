#ifndef BULLET_H
#define BULLET_H

class Bullet {
private:
    float x, y;
    float vx, vy;
    bool playerBullet;
    bool active;

public:
    Bullet();
    Bullet(float startX, float startY, float velX, float velY, bool isPlayerBullet);
    
    void update(float dt);
    void draw();
    
    float getX() const;
    float getY() const;
    bool isPlayerBullet() const;
    bool isActive() const;
    void deactivate();
    bool isOffScreen(int screenWidth, int screenHeight);
};

#endif

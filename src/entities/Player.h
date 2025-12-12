#ifndef PLAYER_H
#define PLAYER_H

#include "Bullet.h"

class Player {
private:
    float x, y;
    float cannonAngle;
    float cannonLength;
    
public:
    Player();
    Player(float startX, float startY);
    
    void setCannonAngle(float mouseX, float mouseY);
    void draw();
    Bullet* shoot();
    
    float getX() const;
    float getY() const;
};

#endif

#ifndef SMOKE_H
#define SMOKE_H

#include <vector>

struct SmokeParticle {
    float x, y;
    float vx, vy;
    float size;
    float alpha;
    float lifetime;
    float maxLifetime;
    bool isGray;
};

class Smoke {
private:
    std::vector<SmokeParticle> particles;
    float x, y;
    float spawnTimer;
    float spawnInterval;
    bool active;

public:
    Smoke();
    Smoke(float startX, float startY);
    
    void update(float dt);
    void draw();
    void spawn(float newX, float newY);
    void stop();
    
    bool isActive() const;
    bool hasParticles() const;
};

#endif

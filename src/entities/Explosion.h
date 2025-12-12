#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion {
private:
    float x, y;
    float timer;
    float duration;
    bool active;
    static unsigned int textureId;
    static bool textureLoaded;
    static int texWidth, texHeight;

public:
    Explosion();
    Explosion(float posX, float posY);
    
    static void initTexture();
    void update(float dt);
    void draw();
    
    bool isActive() const;
};

#endif

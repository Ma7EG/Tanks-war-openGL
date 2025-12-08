#ifndef TANK_H
#define TANK_H

class Tank {
private:
    void drawCircle(float cx, float cy, float r, float r_color, float g_color, float b_color);

public:
    Tank();
    void draw();
};

#endif

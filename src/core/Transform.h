#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Transform {
private:
    float scaleX, scaleY;
    float translateX, translateY;

public:
    Transform() : scaleX(1.0f), scaleY(1.0f), translateX(0.0f), translateY(0.0f) {}
    
    Transform(float sx, float sy, float tx, float ty) 
        : scaleX(sx), scaleY(sy), translateX(tx), translateY(ty) {}

    void setScale(float sx, float sy) {
        scaleX = sx;
        scaleY = sy;
    }

    void setTranslate(float tx, float ty) {
        translateX = tx;
        translateY = ty;
    }

    void apply() {
        glPushMatrix();
        glTranslatef(translateX, translateY, 0.0f);
        glScalef(scaleX, scaleY, 1.0f);
    }

    void reset() {
        glPopMatrix();
    }
};

#endif

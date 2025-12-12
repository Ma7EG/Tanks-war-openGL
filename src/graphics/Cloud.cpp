#include "Cloud.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// Helper function to draw a filled circle for cloud puffs
static void drawCloudCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); 
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(angle) * r, cy + sin(angle) * r);
    }
    glEnd();
}

// Draws a fluffy cloud from overlapping circles
void drawCloud() {
    glColor3f(1.0f, 1.0f, 1.0f); 

    drawCloudCircle(-0.2f, 0.4f, 0.22f);
    drawCloudCircle(0.05f, 0.45f, 0.25f);
    drawCloudCircle(0.25f, 0.40f, 0.20f);
    drawCloudCircle(0.15f, 0.30f, 0.18f);
    drawCloudCircle(-0.05f, 0.30f, 0.18f);
}

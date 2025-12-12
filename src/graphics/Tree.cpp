#include "Tree.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

// Helper function to draw a filled circle for tree leaves
static void drawTreeCircle(float cx, float cy, float r, int seg = 60) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; i++) {
        float t = 2 * 3.14159265f * i / seg;
        glVertex2f(cx + r * cosf(t), cy + r * sinf(t));
    }
    glEnd();
}

// Draws a tree with trunk and circular leaf clusters
void drawTree() {
    // Trunk
    glColor3f(0.55f, 0.18f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-20, 0);
        glVertex2f(20, 0);
        glVertex2f(20, 200);
        glVertex2f(-20, 200);
    glEnd();

    // Leaves
    glColor3f(0.1f, 0.8f, 0.18f);
    float cx[] = { -70, 0, 70 };
    float cy[] = { 190, 210, 200 };
    float r[]  = { 70, 85, 65 };

    for (int i = 0; i < 3; i++)
        drawTreeCircle(cx[i], cy[i], r[i]);
}

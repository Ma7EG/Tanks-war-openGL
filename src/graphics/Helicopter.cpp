#include "Helicopter.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#define M_PI 3.14159265358979323846

// Helper function to draw a filled circle
static void drawCircleH(float cx, float cy, float r, int seg = 60) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * (float)M_PI * i / seg;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

// Helper function to draw a filled ellipse
static void drawEllipseH(float cx, float cy, float rx, float ry, int seg = 80) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * (float)M_PI * i / seg;
        glVertex2f(cx + rx * cosf(a), cy + ry * sinf(a));
    }
    glEnd();
}

// Draws an enemy helicopter with body, rotor, door and window
void drawHelicopter() {
    GLfloat BODY_COLOR[] = { 0.10f, 0.30f, 0.25f };
    GLfloat WINDOW_COLOR[] = { 0.12f, 0.15f, 0.16f };
    GLfloat DOOR_COLOR[] = { 0.16f, 0.55f, 0.45f };
    GLfloat WHITE_COLOR[] = { 0.90f, 0.90f, 0.90f };

    float offsetX = -45.125f;
    float offsetY = 21.935f;

    auto fx = [&](float left, float width) {
        return offsetX + left + width * 0.5f + 281.0f;
    };
    auto fy = [&](float top, float height) {
        return offsetY - (top + height * 0.5f + 1724.0f);
    };

    // Main body
    {
        float w = 90.25f;
        float h = 44.79f;
        float top = -1724.46f;
        float left = -281.0f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(BODY_COLOR);
        drawEllipseH(cx, cy, w * 0.5f, h * 0.5f);
    }

    // Tail connector
    {
        float w = 67.86f;
        float h = 4.07f;
        float top = -1704.11f;
        float left = -201.61f;
        float x1 = fx(left, 0);
        float x2 = x1 + w;
        float y1 = fy(top + h, 0);
        float y2 = y1 + h;
        glColor3fv(BODY_COLOR);
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }

    // Tail vertical
    {
        float w = 4.07f;
        float h = 8.82f;
        float top = -1710.89f;
        float left = -137.82f;
        float x1 = fx(left, 0);
        float x2 = x1 + w;
        float y1 = fy(top + h, 0);
        float y2 = y1 + h;
        glColor3fv(BODY_COLOR);
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }

    // Tail rotor
    {
        float w = 14.25f;
        float h = 14.25f;
        float top = -1721.07f;
        float left = -143.25f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WHITE_COLOR);
        drawCircleH(cx, cy, w * 0.5f);
    }

    // Door
    {
        float w = 12.89f;
        float h = 22.39f;
        float top = -1711.57f;
        float left = -245.71f;
        float x1 = fx(left, 0);
        float x2 = x1 + w;
        float y1 = fy(top + h, 0);
        float y2 = y1 + h;
        glColor3fv(DOOR_COLOR);
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }

    // Door handle
    {
        float w = 2.71f;
        float h = 2.71f;
        float top = -1700.71f;
        float left = -236.21f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WHITE_COLOR);
        drawCircleH(cx, cy, w * 0.5f, 20);
    }

    // Rotor shaft
    {
        float w = 2.71f;
        float h = 5.43f;
        float top = -1729.21f;
        float left = -236.89f;
        float x1 = fx(left, 0);
        float x2 = x1 + w;
        float y1 = fy(top + h, 0);
        float y2 = y1 + h;
        glColor3fv(WHITE_COLOR);
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }

    // Rotor hub
    {
        float w = 6.11f;
        float h = 6.79f;
        float top = -1736.0f;
        float left = -238.93f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WHITE_COLOR);
        drawEllipseH(cx, cy, w * 0.5f, h * 0.5f);
    }

    // Main rotor blade
    {
        float w = 89.57f;
        float h = 2.04f;
        float top = -1729.21f;
        float left = -280.32f;
        float x1 = fx(left, 0);
        float x2 = x1 + w;
        float y1 = fy(top + h, 0);
        float y2 = y1 + h;
        glColor3fv(WHITE_COLOR);
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }

    // Cockpit window
    {
        float w = 26.6f;
        float h = 20.7f;
        float top = -1721.07f;
        float left = -278.29f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WINDOW_COLOR);
        drawEllipseH(cx, cy, w * 0.5f, h * 0.5f);
    }
}

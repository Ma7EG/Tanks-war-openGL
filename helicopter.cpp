#include <freeglut.h>
#include <cmath>
#define M_PI 3.14159265358979323846

void drawCircle(float cx, float cy, float r, int seg = 60) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * M_PI * i / seg;
        glVertex2f(cx + r * cos(a), cy + r * sin(a));
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int seg = 80) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * M_PI * i / seg;
        glVertex2f(cx + rx * cos(a), cy + ry * sin(a));
    }
    glEnd();
}

void display() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat BODY_COLOR[] = { 0.10f, 0.30f, 0.25f };
    GLfloat WINDOW_COLOR[] = { 0.12f, 0.15f, 0.16f };
    GLfloat DOOR_COLOR[] = { 0.16f, 0.55f, 0.45f };
    GLfloat WHITE_COLOR[] = { 0.90f, 0.90f, 0.90f };

    float offsetX = 160.0f;
    float offsetY = 120.0f;

    auto fx = [&](float left, float width) {
        return offsetX + left + width * 0.5f + 281.0f;
        };
    auto fy = [&](float top, float height) {
        return offsetY - (top + height * 0.5f + 1724.0f);
        };

    {
        float w = 90.25f;
        float h = 44.79f;
        float top = -1724.46f;
        float left = -281.0f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(BODY_COLOR);
        drawEllipse(cx, cy, w * 0.5f, h * 0.5f);
    }

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

    {
        float w = 14.25f;
        float h = 14.25f;
        float top = -1721.07f;
        float left = -143.25f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WHITE_COLOR);
        drawCircle(cx, cy, w * 0.5f);
    }

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

    {
        float w = 2.71f;
        float h = 2.71f;
        float top = -1700.71f;
        float left = -236.21f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WHITE_COLOR);
        drawCircle(cx, cy, w * 0.5f, 20);
    }

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

    {
        float w = 6.11f;
        float h = 6.79f;
        float top = -1736.0f;
        float left = -238.93f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WHITE_COLOR);
        drawEllipse(cx, cy, w * 0.5f, h * 0.5f);
    }

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

    {
        float w = 26.6f;
        float h = 20.7f;
        float top = -1721.07f;
        float left = -278.29f;
        float cx = fx(left, w);
        float cy = fy(top, h);
        glColor3fv(WINDOW_COLOR);
        drawEllipse(cx, cy, w * 0.5f, h * 0.5f);
    }

    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 320.0, 0.0, 240.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

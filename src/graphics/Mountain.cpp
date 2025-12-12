#include "Mountain.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Draws the left mountain with shading and snow cap
void drawMountainLeft() {
    // Mountain body (light side)
    glBegin(GL_TRIANGLES);
    glColor3f(0.404f, 0.435f, 0.576f);
    glVertex3f(-90.0f, 10.0f, 0.0f);
    glVertex3f(-10.0f, 10.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();

    // Mountain body (dark shadow side)
    glBegin(GL_TRIANGLES);
    glColor3f(0.35f, 0.35f, 0.43f);
    glVertex3f(-90.0f, 10.0f, 0.0f);
    glVertex3f(-50.0f, 10.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();

    // Snow cap (right part)
    glBegin(GL_QUADS);
    glColor3f(0.851f, 0.996f, 0.992f);
    glVertex3f(-50.0f, 40.0f, 0.0f);
    glVertex3f(-40.0f, 50.0f, 0.0f);
    glVertex3f(-30.0f, 45.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();

    // Snow cap (left part)
    glBegin(GL_QUADS);
    glColor3f(0.851f, 0.996f, 0.992f);
    glVertex3f(-50.0f, 40.0f, 0.0f);
    glVertex3f(-60.0f, 50.0f, 0.0f);
    glVertex3f(-70.0f, 45.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();
}

// Draws the right mountain with shading and snow cap
void drawMountainRight() {
    // Mountain body (dark side)
    glBegin(GL_TRIANGLES);
    glColor3f(0.35f, 0.35f, 0.43f);
    glVertex3f(90.0f, 10.0f, 0.0f);
    glVertex3f(10.0f, 10.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();

    // Mountain body (light side)
    glBegin(GL_TRIANGLES);
    glColor3f(0.404f, 0.435f, 0.576f);
    glVertex3f(90.0f, 10.0f, 0.0f);
    glVertex3f(50.0f, 10.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();

    // Snow cap (left part)
    glBegin(GL_QUADS);
    glColor3f(0.851f, 0.996f, 0.992f);
    glVertex3f(50.0f, 40.0f, 0.0f);
    glVertex3f(40.0f, 50.0f, 0.0f);
    glVertex3f(30.0f, 45.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();

    // Snow cap (right part)
    glBegin(GL_QUADS);
    glColor3f(0.851f, 0.996f, 0.992f);
    glVertex3f(50.0f, 40.0f, 0.0f);
    glVertex3f(60.0f, 50.0f, 0.0f);
    glVertex3f(70.0f, 45.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();
}

// Draws both mountains
void drawMountain() {
    drawMountainLeft();
    drawMountainRight();
}
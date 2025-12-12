#include "Building.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Draws a row of 4 buildings with lit windows
void drawBuilding() {
    // Building 1 (short)
    glColor3f(0.235f, 0.235f, 0.235f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0); glVertex2f(200, 0);
    glVertex2f(200, 300); glVertex2f(0, 300);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS); glVertex2f(20, 220); glVertex2f(80, 220); glVertex2f(80, 280); glVertex2f(20, 280); glEnd();
    glBegin(GL_QUADS); glVertex2f(20, 130); glVertex2f(80, 130); glVertex2f(80, 190); glVertex2f(20, 190); glEnd();
    glBegin(GL_QUADS); glVertex2f(20, 40);  glVertex2f(80, 40);  glVertex2f(80, 100); glVertex2f(20, 100); glEnd();
    glBegin(GL_QUADS); glVertex2f(120, 220); glVertex2f(180, 220); glVertex2f(180, 280); glVertex2f(120, 280); glEnd();
    glBegin(GL_QUADS); glVertex2f(120, 130); glVertex2f(180, 130); glVertex2f(180, 190); glVertex2f(120, 190); glEnd();
    glBegin(GL_QUADS); glVertex2f(120, 40);  glVertex2f(180, 40);  glVertex2f(180, 100); glVertex2f(120, 100); glEnd();

    // Building 2 (tall)
    glColor3f(0.235f, 0.235f, 0.235f);
    glBegin(GL_QUADS);
    glVertex2f(200, 0); glVertex2f(400, 0);
    glVertex2f(400, 500); glVertex2f(200, 500);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS); glVertex2f(220, 420); glVertex2f(280, 420); glVertex2f(280, 480); glVertex2f(220, 480); glEnd();
    glBegin(GL_QUADS); glVertex2f(220, 320); glVertex2f(280, 320); glVertex2f(280, 380); glVertex2f(220, 380); glEnd();
    glBegin(GL_QUADS); glVertex2f(220, 220); glVertex2f(280, 220); glVertex2f(280, 280); glVertex2f(220, 280); glEnd();
    glBegin(GL_QUADS); glVertex2f(320, 420); glVertex2f(382, 420); glVertex2f(382, 480); glVertex2f(320, 480); glEnd();
    glBegin(GL_QUADS); glVertex2f(320, 320); glVertex2f(382, 320); glVertex2f(382, 380); glVertex2f(320, 380); glEnd();
    glBegin(GL_QUADS); glVertex2f(320, 220); glVertex2f(382, 220); glVertex2f(382, 280); glVertex2f(320, 280); glEnd();

    // Building 3 (short)
    glColor3f(0.235f, 0.235f, 0.235f);
    glBegin(GL_QUADS);
    glVertex2f(400, 0); glVertex2f(600, 0);
    glVertex2f(600, 300); glVertex2f(400, 300);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS); glVertex2f(420, 220); glVertex2f(480, 220); glVertex2f(480, 280); glVertex2f(420, 280); glEnd();
    glBegin(GL_QUADS); glVertex2f(420, 130); glVertex2f(480, 130); glVertex2f(480, 190); glVertex2f(420, 190); glEnd();
    glBegin(GL_QUADS); glVertex2f(420, 40);  glVertex2f(480, 40);  glVertex2f(480, 100); glVertex2f(420, 100); glEnd();
    glBegin(GL_QUADS); glVertex2f(520, 220); glVertex2f(580, 220); glVertex2f(580, 280); glVertex2f(520, 280); glEnd();
    glBegin(GL_QUADS); glVertex2f(520, 130); glVertex2f(580, 130); glVertex2f(580, 190); glVertex2f(520, 190); glEnd();
    glBegin(GL_QUADS); glVertex2f(520, 40);  glVertex2f(580, 40);  glVertex2f(580, 100); glVertex2f(520, 100); glEnd();

    // Building 4 (tall)
    glColor3f(0.235f, 0.235f, 0.235f);
    glBegin(GL_QUADS);
    glVertex2f(600, 0); glVertex2f(800, 0);
    glVertex2f(800, 500); glVertex2f(600, 500);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS); glVertex2f(620, 420); glVertex2f(680, 420); glVertex2f(680, 480); glVertex2f(620, 480); glEnd();
    glBegin(GL_QUADS); glVertex2f(620, 320); glVertex2f(680, 320); glVertex2f(680, 380); glVertex2f(620, 380); glEnd();
    glBegin(GL_QUADS); glVertex2f(620, 220); glVertex2f(680, 220); glVertex2f(680, 280); glVertex2f(620, 280); glEnd();
    glBegin(GL_QUADS); glVertex2f(720, 420); glVertex2f(780, 420); glVertex2f(780, 480); glVertex2f(720, 480); glEnd();
    glBegin(GL_QUADS); glVertex2f(720, 320); glVertex2f(780, 320); glVertex2f(780, 380); glVertex2f(720, 380); glEnd();
    glBegin(GL_QUADS); glVertex2f(720, 220); glVertex2f(780, 220); glVertex2f(780, 280); glVertex2f(720, 280); glEnd();

    // Dividing lines between buildings
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(200, 0); glVertex2f(200, 500);
    glVertex2f(400, 0); glVertex2f(400, 500);
    glVertex2f(600, 0); glVertex2f(600, 500);
    glEnd();
}

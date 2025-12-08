#include <freeglut.h>

void SetTransformations() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

void display() {
    glClearColor(0.733f, 0.843f, 0.925f, 0);
    glClear(GL_COLOR_BUFFER_BIT);





    SetTransformations();

    glBegin(GL_TRIANGLES);
    glColor3f(0.404f, 0.435f, 0.576f);
    glVertex3f(-90.0f, 10.0f, 0.0f);
    glVertex3f(-10.0f, 10.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.35f, 0.35f, 0.43f);
    glVertex3f(-90.0f, 10.0f, 0.0f);
    glVertex3f(-50.0f, 10.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.35f, 0.35f, 0.43f);
    glVertex3f(90.0f, 10.0f, 0.0f);
    glVertex3f(10.0f, 10.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.404f, 0.435f, 0.576f);

    glVertex3f(90.0f, 10.0f, 0.0f);
    glVertex3f(50.0f, 10.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();






    glBegin(GL_QUADS);
    glColor3f(0.851, 0.996, 0.992);
    glVertex3f(-50.0f, 40.0f, 0.0f);
    glVertex3f(-40.0f, 50.0f, 0.0f);
    glVertex3f(-30.0f, 45.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.851, 0.996, 0.992);
    glVertex3f(-50.0f, 40.0f, 0.0f);
    glVertex3f(-40.0f, 50.0f, 0.0f);
    glVertex3f(-30.0f, 45.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.851, 0.996, 0.992);
    glVertex3f(-50.0f, 40.0f, 0.0f);
    glVertex3f(-60.0f, 50.0f, 0.0f);
    glVertex3f(-70.0f, 45.0f, 0.0f);
    glVertex3f(-50.0f, 80.0f, 0.0f);
    glEnd();







    glBegin(GL_QUADS);
    glColor3f(0.851, 0.996, 0.992);
    glVertex3f(50.0f, 40.0f, 0.0f);
    glVertex3f(40.0f, 50.0f, 0.0f);
    glVertex3f(30.0f, 45.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.851, 0.996, 0.992);
    glVertex3f(50.0f, 40.0f, 0.0f);
    glVertex3f(60.0f, 50.0f, 0.0f);
    glVertex3f(70.0f, 45.0f, 0.0f);
    glVertex3f(50.0f, 80.0f, 0.0f);
    glEnd();


















    glFlush();
}
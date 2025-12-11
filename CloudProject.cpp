#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); 
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(angle) * r, cy + sin(angle) * r);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f); 

    drawCircle(-0.2f, 0.4f, 0.22f);
    drawCircle(0.05f, 0.45f, 0.25f);
    drawCircle(0.25f, 0.40f, 0.20f);
    drawCircle(0.15f, 0.30f, 0.18f);
    drawCircle(-0.05f, 0.30f, 0.18f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

 
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cloud Drawing");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
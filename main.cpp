#include <GL/glut.h>
#include <cmath>

const int W = 800, H = 600;

void circle(float cx, float cy, float r, int seg = 60) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; i++) {
        float t = 2 * 3.14159265f * i / seg;
        glVertex2f(cx + r * cosf(t), cy + r * sinf(t));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    glColor3f(0.55f, 0.18f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(W/2 - 20, 50);
        glVertex2f(W/2 + 20, 50);
        glVertex2f(W/2 + 20, 250);
        glVertex2f(W/2 - 20, 250);
    glEnd();


    glColor3f(0.1f, 0.8f, 0.18f);
    float cx[] = { W/2 - 70, W/2, W/2 + 70 };
    float cy[] = { 240, 260, 250 };
    float r[]  = { 70, 85, 65 };

    for (int i = 0; i < 3; i++)
        circle(cx[i], cy[i], r[i]);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(W, H);
    glutCreateWindow("Tree");

    glClearColor(1, 1, 1, 1);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
}

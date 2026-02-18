#include <GL/glut.h>
#include <math.h>

#define BODY_GREEN_R 0.2f
#define BODY_GREEN_G 0.5f
#define BODY_GREEN_B 0.2f

#define WHEEL_GREEN_R 0.18f
#define WHEEL_GREEN_G 0.45f
#define WHEEL_GREEN_B 0.18f

void drawCircle(float cx, float cy, float r, float r_color, float g_color, float b_color) {
    glColor3f(r_color, g_color, b_color);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(cx + cosf(angle) * r, cy + sinf(angle) * r);
    }
    glEnd();
}

void drawTank() {
    glColor3f(BODY_GREEN_R, BODY_GREEN_G, BODY_GREEN_B);
    glBegin(GL_QUADS);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f( 0.45f, -0.1f);
        glVertex2f( 0.45f,  0.2f);
        glVertex2f(-0.45f,  0.2f);
    glEnd();

    float turret_center_y = 0.25f;
    float turret_radius = 0.2f;
    drawCircle(0.0f, turret_center_y, turret_radius, BODY_GREEN_R, BODY_GREEN_G, BODY_GREEN_B);

    glColor3f(WHEEL_GREEN_R, WHEEL_GREEN_G, WHEEL_GREEN_B);
    glBegin(GL_QUADS);
        float gun_start_x = 0.2f;
        float gun_end_x = 0.5f;

        float gun_y_bottom = turret_center_y - 0.02f;
        float gun_y_top    = turret_center_y + 0.02f;

        glVertex2f(gun_start_x, gun_y_bottom);
        glVertex2f(gun_end_x,   gun_y_bottom);
        glVertex2f(gun_end_x,   gun_y_top);
        glVertex2f(gun_start_x, gun_y_top);
    glEnd();

    float wheel_radius = 0.1f;
    float wheel_y = -0.1f;

    drawCircle(-0.3f, wheel_y, wheel_radius, WHEEL_GREEN_R, WHEEL_GREEN_G, WHEEL_GREEN_B);
    drawCircle( 0.3f, wheel_y, wheel_radius, WHEEL_GREEN_R, WHEEL_GREEN_G, WHEEL_GREEN_B);
}

void display() {
    glClearColor(0.88f, 0.92f, 0.96f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    drawTank();

    glFlush();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    if (aspect >= 1.0f) {
        glOrtho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
        glOrtho(-1.0f, 1.0f, -1.0f/aspect, 1.0f/aspect, -1.0f, 1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tank");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;

GLdouble radius = 2;
GLint slices = 50;
GLint stacks = 50;

void displaySphere(void) {
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0, 0.0, -4.5);

    glColor3f(1.0, 1.0, 1.0);

    glRotatef(xRotated, 1.0, 0.0, 0.0);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);

    glScalef(1.0, 1.0, 1.0);

    glutSolidSphere(radius, slices, stacks);

    glFlush();

    glutSwapBuffers();
}

void reshapeSphere(int x, int y) {
    if (y == 0 || x == 0)
        return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(70.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glViewport(0, 0, x, y);
}

void idleSphere(void) {
    // xRotated += 0.01;
    yRotated += 0.01;
    // zRotated += 0.01;
    displaySphere();
}

int main(int argc, char **argv) {
    int w = 640, h = 640;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - w) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2);

    glutInitWindowSize(w, h);

    glutCreateWindow("Esfera 3D");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    xRotated = yRotated = zRotated = 30.0;
    xRotated = 30;
    yRotated = 40;
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(displaySphere);
    glutReshapeFunc(reshapeSphere);
    glutIdleFunc(idleSphere);

    glutMainLoop();
    return 0;
}

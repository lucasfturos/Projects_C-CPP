// comando para compilar g++ main.cpp -o main -lglut -lGL

#include <GL/glut.h>

void inicio(void);
void desenha(void);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("GLUT Hello World");

    inicio();

    glutDisplayFunc(desenha);

    glutMainLoop();
}

void inicio(void) {
    glClearColor(0, 0, 0, 0);
}

void desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(-7, -7);
    glColor3f(0, 1, 0);
    glVertex2f(0, 7);
    glColor3f(0, 0, 1);
    glVertex2f(7, -7);
    glEnd();

    glutSwapBuffers();

}
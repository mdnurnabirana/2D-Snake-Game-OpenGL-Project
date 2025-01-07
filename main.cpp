#include <GL/gl.h>
#include <GL/glut.h>

void display_callback();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display_callback);
    glutMainLoop();
    return 0;
}

void display_callback()
{
    glutSwapBuffers();
}

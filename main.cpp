#include <GL/gl.h>       // OpenGL library for rendering
#include <GL/glut.h>     // GLUT library for window and input handling

void display_callback(); // Callback to render display content
void reshape_callback(int, int); // Callback for handling window resizing

void init()
{
    glClearColor(0.0, 0.0, 1.0, 1.0); // Set the background color to blue
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Set display mode to RGB and double buffering
    glutInitWindowSize(500, 500); // Specify the initial window size (500x500)
    glutCreateWindow("SNAKE"); // Create the window with title "SNAKE"
    glutReshapeFunc(reshape_callback); // Register reshape callback for window resizing
    glutDisplayFunc(display_callback); // Register display callback for rendering
    init(); // Call function to set the background color
    glutMainLoop(); // Enter the GLUT event loop (infinite loop for handling events)
    return 0;
}

void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer with the background color
    glutSwapBuffers(); // Swap the front and back buffers for double buffering
}

void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Set the viewport to match the new window size
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix mode
    glLoadIdentity(); // Reset the projection matrix to the identity matrix

    glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0); // Define an orthogonal projection with 2D range
    glMatrixMode(GL_MODELVIEW); // Switch back to the modelview matrix mode
}

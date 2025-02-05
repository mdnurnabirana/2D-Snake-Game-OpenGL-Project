#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "game.h"

#define COLUMNS 40
#define ROWS 40
#define FPS 10

extern short sDirection;
bool gameOver = false;
bool paused = false;
int score = 0;
int highestScore = 0;

// Function declarations
void timer_callback(int);
void display_callback();
void reshape_callback(int, int);
void keyboard_callback(int, int, int);
void readHighestScore();
void writeHighestScore();

// Initialize OpenGL settings and game grid
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    initGrid(COLUMNS, ROWS);          // Initialize game grid
    readHighestScore();               // Load highest score from file
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("SNAKE");

    // Register callback functions
    glutReshapeFunc(reshape_callback);
    glutDisplayFunc(display_callback);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);

    init(); // Initialize game settings

    glutMainLoop(); // Start the game loop
    return 0;
}

// Display callback function
void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw game objects
    drawSnake();
    drawFood();

    glutSwapBuffers(); // Swap buffers for smooth rendering

    // Handle game over scenario
    if (gameOver)
    {
        char text[100];
        sprintf(text, "Your Score: %d\nHighest Score: %d", score, highestScore);
        int result = MessageBox(NULL, text, "Game Over", MB_RETRYCANCEL);

        // If user chooses to retry, reset game state
        if (result == IDRETRY)
        {
            gameOver = false;
            score = 0;
            snake_length = 3;
            sDirection = RIGHT;

            // Reset snake position
            for (int i = 0; i < snake_length; i++)
            {
                posX[i] = 20;
                posY[i] = 20 - i;
            }
        }
        else
        {
            exit(0); // Exit the game
        }
    }
}

// Reshape callback to adjust viewport
void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// Timer callback for game loop
void timer_callback(int)
{
    if (!paused && !gameOver)
    {
        glutPostRedisplay(); // Request display update
    }
    glutTimerFunc(1000 / FPS, timer_callback, 0); // Set next timer callback
}

// Keyboard input handler
void keyboard_callback(int key, int, int)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    case GLUT_KEY_F1: // Pause/Resume with F1 key
        paused = !paused;
        break;
    }
}

// Read highest score from file
void readHighestScore()
{
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highestScore;
        file.close();
    }
}

// Write highest score to file if it's beaten
void writeHighestScore()
{
    if (score > highestScore)
    {
        highestScore = score;
        std::ofstream file("highscore.txt");
        if (file.is_open())
        {
            file << highestScore;
            file.close();
        }
    }
}

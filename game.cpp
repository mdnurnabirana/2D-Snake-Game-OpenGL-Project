#include <GL/gl.h>
#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include "game.h"

extern int score;
extern int highestScore;

int gridX, gridY;       // Grid size variables
int snake_length = 3;    // Initial snake length
bool food = true;        // Flag to determine if food should be placed
int foodX, foodY;        // Food position
short sDirection = RIGHT;// Snake's current movement direction
extern bool gameOver;

int posX[60] = {20, 20, 20}, posY[60] = {20, 19, 18}; // Snake's initial position

void unit(int x, int y); // Helper function to draw grid units

// Initializes grid size
void initGrid(int x, int y)
{
    gridX = x;
    gridY = y;
}

// Draws the entire grid (not currently used in main.cpp)
void drawGrid()
{
    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            unit(x, y);
        }
    }
}

// Draws a single unit of the grid (either a wall or an empty cell)
void unit(int x, int y)
{
    if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
    {
        glLineWidth(3.0);   // Thicker lines for borders
        glColor3f(1.0, 0.0, 0.0); // Red for walls
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(1.0, 1.0, 1.0); // White for normal grid lines
    }

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

// Generates food at a random position
void drawFood()
{
    if (food)  // If food needs to be placed
    {
        random(foodX, foodY);
    }
    food = false;

    glColor3f(0.0, 1.0, 1.0);  // Cyan color for food
    glRectf(foodX, foodY, foodX + 1, foodY + 1); // Draw food as a rectangle
}

// Draws the snake and handles movement, collision, and food consumption
void drawSnake()
{
    // Move the body segments
    for (int i = snake_length - 1; i > 0; i--)
    {
        posX[i] = posX[i - 1];
        posY[i] = posY[i - 1];
    }

    // Move the head in the current direction
    if (sDirection == UP)
        posY[0]++;
    else if (sDirection == DOWN)
        posY[0]--;
    else if (sDirection == RIGHT)
        posX[0]++;
    else if (sDirection == LEFT)
        posX[0]--;

    // Draw the snake
    for (int i = 0; i < snake_length; i++)
    {
        if (i == 0) // Head of the snake
            glColor3f(0.0, 1.0, 0.0); // Green
        else // Body
            glColor3f(0.0, 0.0, 1.0); // Blue

        glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
    }

    // Check collision with walls
    if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
    {
        gameOver = true;
        writeHighestScore();
    }

    // Check collision with itself
    for (int j = 1; j < snake_length; j++)
    {
        if (posX[j] == posX[0] && posY[j] == posY[0])
        {
            gameOver = true;
            writeHighestScore();
        }
    }

    // Check if snake eats the food
    if (posX[0] == foodX && posY[0] == foodY)
    {
        score++;       // Increase score
        snake_length++; // Increase snake size
        food = true;    // Generate new food
    }
}

// Generates random food coordinates within grid boundaries
void random(int &x, int &y)
{
    int _maxX = gridX - 2;
    int _maxY = gridY - 2;
    int _min = 1;
    srand(time(NULL)); // Seed random number generator
    x = _min + rand() % (_maxX - _min);
    y = _min + rand() % (_maxY - _min);
}

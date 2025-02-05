#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

// Direction constants for snake movement
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 60 // Maximum size of the snake

// Function prototypes
void initGrid(int, int);  // Initialize grid
void drawGrid();          // Draw game grid
void drawSnake();         // Draw snake and handle movement
void drawFood();          // Draw food
void random(int&, int&);  // Generate random food position
void writeHighestScore(); // Save highest score

// Global variables used in multiple files
extern int posX[MAX], posY[MAX]; // Snake position arrays
extern int snake_length;         // Length of the snake

#endif // GAME_H_INCLUDED

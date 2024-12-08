//i222676_i222594_i222579_Project
#ifndef GRID_H
#define GRID_H

#include <pthread.h>
#include <semaphore.h> 

#define RED_INNER_PATH_CHAR '$'
#define YELLOW_INNER_PATH_CHAR '+'
#define GREEN_INNER_PATH_CHAR '%'
#define BLUE_INNER_PATH_CHAR '@'

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define BLUE    "\033[44m"
#define YELLOW  "\033[43m"
#define RED     "\033[41m"
#define GREEN   "\033[42m"
#define WHITE   "\033[47m"
#define GRAY    "\033[100m"
#define BLACK   "\033[40m"
#define LIGHT_RED "\033[48;2;255;102;102m"
#define LIGHT_YELLOW "\033[103m"
#define DARK_BLUE "\033[48;2;0;0;139m"
#define DARK_GREEN "\033[48;2;0;100;0m"

// Grid dimensions
#define GRID_ROWS 15
#define GRID_COLS 15




// Global grid variables
extern char grid[GRID_ROWS][GRID_COLS];  // Static grid
extern char tokenMap[GRID_ROWS][GRID_COLS];  // Dynamic token map

// Mutex for grid access control
extern pthread_mutex_t gridLock;

// Semaphore for dice access (if needed)
extern sem_t diceSemaphore;


// Function prototypes
void initializeGrid();
void displayGrid();

#endif


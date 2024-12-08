//i222676_i222594_i222579_Project
//g++ -o program Project.c whitePath.c Thread1.c
#include <stdio.h>
#include <stdlib.h>
#include "Grid.h"
#include "Route.h"
#include "GlobalStruct.h"
#include "Threads.h"
#include <pthread.h>

//grid access control
pthread_mutex_t gridLock;

// Grid array
char grid[15][15];

// Reserved positions (Stops)
int reservedStops[4][2] = {
    {2, 6},   // Yellow home stop
    {6, 12},  // Green home stop
    {12, 8},  // Blue home stop
    {8, 2}    // Red home stop
};

// Function to check if the position is a reserved stop (e.g., home yards)
int isReserved(int row, int col) {
    for (int i = 0; i < 4; i++) {
        if (reservedStops[i][0] == row && reservedStops[i][1] == col) {
            return 1;  // This position is reserved
        }
    }
    return 0;  // Not a reserved position
}

void initializeGrid() {
    // Initialize mutex
    pthread_mutex_init(&gridLock, NULL); 

    // Lock grid during initialization
    pthread_mutex_lock(&gridLock); 
    
    // Initialize all cells as white
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            grid[i][j] = '.';
        }
    }

    // Mark home yards
    for (int i = 0; i < 6; i++) {
        // Red = A
        for (int j = 0; j < 6; j++) grid[i][j] = 'A'; 
        // Yellow = B
        for (int j = 9; j < 15; j++) grid[i][j] = 'B'; 
    }

    for (int i = 9; i < 15; i++) {
        // Blue = C 
        for (int j = 0; j < 6; j++) grid[i][j] = 'C'; 
        // Green = D
        for (int j = 9; j < 15; j++) grid[i][j] = 'D'; // Green
    }
    
    // =================================================================
    //PATHWAYS
    for (int i = 1; i < 6; i++) grid[i][7] = '+'; 
    grid[1][8] = 'B';
    
    for (int j = 13; j > 8; j--) grid[7][j] = '%'; 
    grid[8][13] = 'D';
    
    for (int i = 13; i > 8; i--) grid[i][7] = '@'; 
    grid[13][6] = 'C';
    
    for (int j = 1; j < 6; j++) grid[7][j] = '$'; 
    grid[6][1] = 'A';
    // ==================================================================

    //stop of yellow home
    grid[2][6] = 'S'; 
    //stop of green home
    grid[6][12] = 'S'; 
    //stop of blue home
    grid[12][8] = 'S'; 
    //stop of red home
    grid[8][2] = 'S';

    for (int i = 6; i <= 8; i++) {
        for (int j = 6; j <= 8; j++) {
            grid[i][j] = 'X'; // Center block
        }
    }

    // Place index 0 Player A's token at the starting position
    grid[1][1] = 'a';
    
    // Place index 0 Player B's token at the starting position
    grid[1][11] = 'b';
    
    // Place index 0 Player C's token at the starting position (similar to others)
    grid[11][1] = 'c';

    // Place index 0 Player D's token at the starting position (similar to others)
    grid[11][11] = 'd';


    // Place index 1 Player A's token at the starting position
    grid[1][3] = 's';
    
    // Place index 1 Player B's token at the starting position
    grid[1][13] = 'n';
    
    // Place index 1 Player C's token at the starting position (similar to others)
    grid[11][3] = 'v';

    // Place index 1 Player D's token at the starting position (similar to others)
    grid[11][13] = 'e';


    // Place index 2 Player A's token at the starting position
    grid[3][1] = 'q';
    
    // Place index 2 Player B's token at the starting position
    grid[3][11] = 'j';
    
    // Place index 2 Player C's token at the starting position (similar to others)
    grid[13][1] = 'f';

    // Place index 2 Player D's token at the starting position (similar to others)
    grid[13][11] = 'r';


    // Place index 3 Player A's token at the starting position
    grid[3][3] = 'w';
    
    // Place index 3 Player B's token at the starting position
    grid[3][13] = 'h';
    
    // Place index 3 Player C's token at the starting position (similar to others)
    grid[13][3] = 'g';

    // Place index 3 Player D's token at the starting position (similar to others)
    grid[13][13] = 't';

     pthread_mutex_unlock(&gridLock); // Unlock grid

}

void displayGrid() {
    //system("clear"); // Clear the console for a fresh grid display

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
           // ================================================
            if (grid[i][j] == RED_INNER_PATH_CHAR) {
                printf(RED " %c " RESET, grid[i][j]); // Red inner path
            } else if (grid[i][j] == YELLOW_INNER_PATH_CHAR) {
                printf(YELLOW " %c " RESET, grid[i][j]); // Yellow inner path
            } else if (grid[i][j] == GREEN_INNER_PATH_CHAR) {
                printf(GREEN " %c " RESET, grid[i][j]); // Green inner path
            } else if (grid[i][j] == BLUE_INNER_PATH_CHAR) {
                printf(BLUE " %c " RESET, grid[i][j]); // Blue inner path
            }
           // ==============================================
           
             else if (grid[i][j] == 'A') {
                printf(RED "   " RESET); // Player A's area
            } else if (grid[i][j] == 'B') {
                printf(YELLOW "   " RESET); // Player B's area
            } else if (grid[i][j] == 'C') {
                printf(BLUE "   " RESET); // Player C's area
            } else if (grid[i][j] == 'D') {
                printf(GREEN "   " RESET); // Player D's area
            } else if (grid[i][j] == 'S') {
                printf(GRAY "   " RESET); // Safe zones
            } else if (grid[i][j] == 'X') {
                printf(BLACK "   " RESET); // Center block
            } else if (grid[i][j] == 'a'||grid[i][j] == 's'||grid[i][j] == 'q'||grid[i][j] == 'w') {
                printf(LIGHT_RED " %c " RESET,grid[i][j]); // Token a
            } else if (grid[i][j] == 'b'||grid[i][j] == 'n'||grid[i][j] == 'j'||grid[i][j] == 'h') {
                printf(LIGHT_YELLOW " %c " RESET,grid[i][j]); // Token b
            } else if (grid[i][j] == 'c'||grid[i][j] == 'v'||grid[i][j] == 'f'||grid[i][j] == 'g') {
                printf(DARK_BLUE " %c " RESET,grid[i][j]); // Token c
            } else if (grid[i][j] == 'd'||grid[i][j] == 'e'||grid[i][j] == 'r'||grid[i][j] == 't') {
                printf(DARK_GREEN " %c " RESET,grid[i][j]); // Token d
            } else {
                printf(WHITE " * " RESET); // Pathway cells
            }
        }
        printf("\n");
    }
    printf("\n");
}




#include <stdio.h>
#include "Route.h"
#include <pthread.h>
#include "Grid.h"
#include "GlobalStruct.h"
#include "Threads.h"

void tokenOnTop(int currentRow, int currentCol, char tokenChar, char* tempTile, int* tokenTowerPosition);
int tokenkill(int newRow, int newCol, char tokenChar);
void movePlayerWithPathway(char tokenChar);
void moveToken(int *currPosition, char *tempTile, char tokenChar, int *tokenTowerPosition, int steps);

//PATH ALLLOWED
int isAllowedToEnterPath(int newRow, int newCol, char tokenChar)
{
  // Red Inner Path is at row 7, columns 1-5
    if (newRow == 7 && newCol >= 1 && newCol <= 5) {
        if (tokenChar == 'a') {  
           if (RED_INNER_PATH_CHAR == '$'){
        // Only Red token ('a') is allowed
            return 1;
            }
        } else {
            printf("Player %c cannot enter the Red Inner Path.\n", tokenChar);
            return 0;
        }
    }
    
     // Yellow Inner Path is at row 1-5, column 7
    if (newCol == 7 && newRow >= 1 && newRow <= 5) {
        if (tokenChar == 'b') {  
            if (YELLOW_INNER_PATH_CHAR == '+'){
        // Only Yellow token ('b') is allowed
            return 1;
            }
        } else {
            printf("Player %c cannot enter the Yellow Inner Path.\n", tokenChar);
            return 0;
        }
    }
    
    
    // Green Inner Path is at row 7, columns 9-13
    //ITS ARRAY SHOULD BE IN FORM [7, 13], [7, 12], [7, 11]
    // Blue Inner Path is at row 9-13, column 7
    // Green Inner Path is at row 7, columns 13 to 9 (in reverse order)
    if (newRow == 7 && newCol <= 13 && newCol >= 9) {
        if (tokenChar == 'd') {  // Only Green token ('d') is allowed
            if (GREEN_INNER_PATH_CHAR == '%') {
                return 1; // Valid move
            }
        } else {
               printf("Player %c cannot enter the Green Inner Path.\n", tokenChar);
        return 0; // Invalid move for non-green tokens
    }
}



    // Blue Inner Path is at row 9-13, column 7
    if (newCol == 7 && newRow >= 9 && newRow <= 13) {
        if (tokenChar == 'c') {  
            if (BLUE_INNER_PATH_CHAR == '@'){
            // Only Blue token ('c') is allowed
            return 1;
            }
        } else {
            printf("Player %c cannot enter the Blue Inner Path..\n", tokenChar);
            return 0;
        }
    }
    return 1;
    
}

void movePlayerWithPathway(char tokenChar)
{
    int kill = 0; 
    if (tokenChar == 'a')
    {
       
        // for red tokens
        RedPathUH();
        YellowPathUp();
        YellowMiddle();
        YellowPathDown();
        GreenPathForward();
        GreenMiddle();
        GreenPathDown();
        BluePathDown();
        BlueMiddle();
        BluePathUp();
        RedPathDH();
        
        if (kill){
            RedInnerPath();
        }else {
           RedMiddle();
        }
        // red should ends at (7, 5) in inner home
    }
    else if (tokenChar == 'b')
    {
        // for yellow tokens
        YellowPathDown();
        GreenPathForward();
        GreenMiddle();
        GreenPathDown();
        BluePathDown();
        BlueMiddle();
        BluePathUp();
        RedPathDH();
        RedMiddle();
        RedPathUH();
        YellowPathUp();
        // have to end in yellow home
        // need home inner path
        if (kill){
            YellowInnerPath();
        } else {
            YellowMiddle();
        }
    }
    else if (tokenChar == 'c')
    {
        // for blue tokens
        BluePathUp();
        RedPathDH();
        RedMiddle();
        RedPathUH();
        YellowPathUp();
        YellowMiddle();
        YellowPathDown();
        GreenPathForward();
        GreenMiddle();
        GreenPathDown();
        BluePathDown();
        // have to add blue inner path
        if (kill){
          BlueInnerPath();
        } else {
          BlueMiddle();
        }
    }
    else if (tokenChar == 'd')
    {
        // for green tokens
        GreenPathDown();
        BluePathDown();
        BlueMiddle();
        BluePathUp();
        RedPathDH();
        RedMiddle();
        RedPathUH();
        YellowPathUp();
        YellowMiddle();
        YellowPathDown();
        GreenPathForward();
        // have to add green inner path
        if (kill){
           GreenInnerPath();
        } else {
           GreenMiddle();
        }
    }
}

//Function moveToken


// Move token for Player A along the pathway
void moveToken(int *currPosition, char *tempTile, char tokenChar, int* tokenTowerPosition, int steps)
{
    pthread_mutex_lock(&lock);

    // Check if the token is at the starting position
    if (*currPosition == -1 && steps == 6)
    {
        // Set to starting position (assumed to be 0, modify if needed)
        if (tokenChar == 'a')
        {
            grid[1][1] = 'A';
            *currPosition = 0;
            *tempTile = 'A';
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            // Place token at starting position
            grid[startingRow][startingCol] = tokenChar;
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        else if (tokenChar == 'b')
        {
            grid[1][11] = 'B';
            *currPosition = 12;
            *tempTile = 'B';
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        else if (tokenChar == 'c')
        {
            grid[12][1] = 'C';
            *currPosition = 36;
            *tempTile = 'C';
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
        else if (tokenChar == 'd')
        {
            grid[11][11] = 'D';
            *currPosition = 24;
            *tempTile = 'D';
            int startingRow = pathway[*currPosition][0];
            int startingCol = pathway[*currPosition][1];
            grid[startingRow][startingCol] = tokenChar; // Place token at starting position
            printf("Player %c has entered the game and moved to starting position (%d, %d)\n", tokenChar, startingRow, startingCol);
        }
    }
    else
    {
        if (*currPosition >= pathwayLength || *currPosition < 0)
        {
            printf("Error: Invalid position for Player %c.\n", tokenChar);
            pthread_mutex_unlock(&lock); // Ensure unlock before returning
            return;
        }

        // Clear the current position only if it's not in the home area
        int currentRow = pathway[*currPosition][0];
        int currentCol = pathway[*currPosition][1];

        tokenOnTop(currentRow, currentCol, tokenChar, tempTile, tokenTowerPosition);

        // Clear the current position
        grid[currentRow][currentCol] = *tempTile;

        // Calculate new position (circular movement along pathway)
        *currPosition = (*currPosition + steps) % pathwayLength;

        // Place token at the new position
        int newRow = pathway[*currPosition][0];
        int newCol = pathway[*currPosition][1];
        
        
        int kill = tokenkill(newRow, newCol, tokenChar);  // Only call once
        *tokenTowerPosition = kill;  // Use it to update tokenTowerPosition
        
        // Debugging: Check the value of kill
        printf("kill value after tokenkill: %d\n", kill);

        if (kill == 1) {
             // Token kill occurred, handle the post-kill logic
              printf("Token kill detected. Player %c needs to handle the aftermath.\n", tokenChar);
}

        // =================================================================
        // If a token was killed, handle it accordingly
        if (*tokenTowerPosition == 1) {
            // If token kill occurs, handle the post-kill logic here
            printf("Token kill detected. Player %c needs to handle the aftermath.\n", tokenChar);
        }
        // ===================================================================
        
        
         // Check if the player is entering an inner path that doesn't belong to them
        if (kill == 1){
              
          if (isAllowedToEnterPath(newRow, newCol, tokenChar)){
    
          printf("Player %c stays at position (%d, %d)\n", tokenChar, currentRow, currentCol);
    
    
          printf("Player %c stays at position (%d, %d)\n", tokenChar, currentRow, currentCol);
            
             // Correctly revert the position
           //*currPosition = (*currPosition - steps + pathwayLength) % pathwayLength;
            
  printf("AFTER: Player %c stays at position (%d, %d)\n", tokenChar, currentRow, currentCol);
            pthread_mutex_unlock(&lock);  // Unlock the mutex before returning
            return;  // Stop the function to prevent further movement
            }
        }
        

        // stores value of the tile before going to it's postion
        *tempTile = grid[newRow][newCol];
        // Place token at the new position
        grid[newRow][newCol] = tokenChar;

        printf("Player %c moved to position (%d, %d)\n(for testing: tempTile:%c)\n", tokenChar, newRow, newCol, *tempTile);
        
    }
    
    //FOR DEBUGGING
    

    pthread_mutex_unlock(&lock);
}

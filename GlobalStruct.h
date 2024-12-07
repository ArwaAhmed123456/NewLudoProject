#ifndef GLOBALSTRUCT_H
#define GLOBALSTRUCT_H

#include <pthread.h>

//extern tells lock is define else where
extern pthread_mutex_t lock;  // Declaration only


struct PlayerArgs
{
    int *currPosition;
    char tokenChar;
    //tile value on which player currently exist
    //for removing color issue
    char *tempTile;
    
    //when token are more than one
    int *tokenTowerPosition;
    
    // Tracks the number of kills for this token
    int killCount; 
};

#endif // GLOBALS_H


// Global Variables
extern int currPositionA[4];
extern int currPositionB[4];
extern int currPositionC[4];
extern int currPositionD[4];

extern int tokenTowerPositionA[4];
extern int tokenTowerPositionB[4];
extern int tokenTowerPositionC[4];
extern int tokenTowerPositionD[4];

// TempTile values
extern char tempA[4];
extern char tempB[4];
extern char tempC[4];
extern char tempD[4];

// Declare the arrays globally
extern struct PlayerArgs tokenA[4];
extern struct PlayerArgs tokenB[4];
extern struct PlayerArgs tokenC[4];
extern struct PlayerArgs tokenD[4];


 /*the tempTile carries the character value of the tile the player is currently on
    so that when a player moves to from current Tile-A to destination Tile-B,
     the player can reintilize Tile-A back to it's original color value*/
     
      /*tokenTowerPosition tell us where or at which y position the token is
    if multiple tokens are on top of eachother
    if tokenTowerPosition>0 it is on top of another token
    else it is not on top of another token*/



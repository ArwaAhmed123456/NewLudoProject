//Moved the thread portion here
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "Grid.h"
#include "Route.h"
#include "GlobalStruct.h"


// Global Variables
int currPositionA[4] = {-1, -1, -1, -1};
int currPositionB[4] = {-1, -1, -1, -1};
int currPositionC[4] = {-1, -1, -1, -1};
int currPositionD[4] = {-1, -1, -1, -1};

int tokenTowerPositionA[4] = {0, 0, 0, 0};
int tokenTowerPositionB[4] = {0, 0, 0, 0};
int tokenTowerPositionC[4] = {0, 0, 0, 0};
int tokenTowerPositionD[4] = {0, 0, 0, 0};

/*the following are the intial values for the starting tempTile variable for each player reason why there is one for each player is beacause if it was one
it would end up being shared by every thread via referencing causing major issues.*/

// tempTile values
char tempA[4] = {'.', '.', '.', '.'}; 
char tempB[4] = {'.', '.', '.', '.'}; 
char tempC[4] = {'.', '.', '.', '.'}; 
char tempD[4] = {'.', '.', '.', '.'}; 

// TokenChar Values
// A = Red
char tokenCharA[4] = {'a', 's', 'q', 'w'}; 
// B = Yellow
char tokenCharB[4] = {'b', 'n', 'j', 'h'}; 
// C = Blue
char tokenCharC[4] = {'c', 'v', 'f', 'g'}; 
// D = Green
char tokenCharD[4] = {'d', 'e', 'r', 't'}; 

// Declare the function prototypes before using them
void movePlayerWithPathway(char tokenChar);
void moveToken(int *currPosition, char *tempTile, char tokenChar, int* tokenTowerPosition, int steps);


void initializePlayerArgs()
{
    for (int i = 0; i < 4; i++)
    {
        tokenA[i] = (struct PlayerArgs){&currPositionA[i], tokenCharA[i], &tempA[i], &tokenTowerPositionA[i], 0};
        tokenB[i] = (struct PlayerArgs){&currPositionB[i], tokenCharB[i], &tempB[i], &tokenTowerPositionB[i], 0};
        tokenC[i] = (struct PlayerArgs){&currPositionC[i], tokenCharC[i], &tempC[i], &tokenTowerPositionC[i], 0};
        tokenD[i] = (struct PlayerArgs){&currPositionD[i], tokenCharD[i], &tempD[i], &tokenTowerPositionD[i], 0};
    }
}

// colorcheck method checks if the token belongs to a given color group or not
int colorcheck(char tokenChar, char tokenCharX[])
{
    for (int i = 0; i < 4; i++)
    {
        if (tokenChar == tokenCharX[i])
        {
            return 1;
        }
    }
    return 0;
}

// samecolorcheck method checks if two tokens belong to the same color group or not
int samecolorcheck(char tokenChar1, char tokenChar2, int newRow, int newCol)
{
    if (colorcheck(tokenChar1, tokenCharA) && colorcheck(tokenChar2, tokenCharA))
    {
        switch (tokenChar1)
        {
        case 'a':
            return *(tokenA[0].tokenTowerPosition);
            break;
        case 's':
            return *(tokenA[1].tokenTowerPosition);
            break;
        case 'q':
            return *(tokenA[2].tokenTowerPosition);
            break;
        case 'w':
            return *(tokenA[3].tokenTowerPosition);
            break;
        default:
            break;
        }
    }
    else if (colorcheck(tokenChar1, tokenCharB) && colorcheck(tokenChar2, tokenCharB))
    {
        switch (tokenChar1)
        {
        case 'b':
            return *(tokenB[0].tokenTowerPosition);
            break;
        case 'n':
            return *(tokenB[1].tokenTowerPosition);
            break;
        case 'j':
            return *(tokenB[2].tokenTowerPosition);
            break;
        case 'h':
            return *(tokenB[3].tokenTowerPosition);
            break;
        default:
            break;
        }
    }
    else if (colorcheck(tokenChar1, tokenCharC) && colorcheck(tokenChar2, tokenCharC))
    {
        switch (tokenChar1)
        {
        case 'c':
            return *(tokenC[0].tokenTowerPosition);
            break;
        case 'v':
            return *(tokenC[1].tokenTowerPosition);
            break;
        case 'f':
            return *(tokenC[2].tokenTowerPosition);
            break;
        case 'g':
            return *(tokenC[3].tokenTowerPosition);
            break;
        default:
            break;
        }
    }
    else if (colorcheck(tokenChar1, tokenCharD) && colorcheck(tokenChar2, tokenCharD))
    {
        switch (tokenChar1)
        {
        case 'd':
            return *(tokenD[0].tokenTowerPosition);
            break;
        case 'e':
            return *(tokenD[1].tokenTowerPosition);
            break;
        case 'r':
            return *(tokenD[2].tokenTowerPosition);
            break;
        case 't':
            return *(tokenD[3].tokenTowerPosition);
            break;
        default:
            break;
        }
    }
    return 0;
}

// this function is used for killing the token if it is not on stops and homes and the token to be killed is in the location of token that is going to kill
//  Corrected tokenkill function:
int tokenkill(int newRow, int newCol, int tokenChar)
{
    int scc = 0;
    if (scc = samecolorcheck(grid[newRow][newCol], tokenChar, newRow, newCol))
    {
        return scc;
    }

        switch (grid[newRow][newCol])
        {
        // tokens at index 0
        case 'a':
        if(*(tokenA[0].tempTile)=='S'||*(tokenA[0].tempTile)=='A'||*(tokenA[0].tempTile)=='B'||*(tokenA[0].tempTile)=='C'||*(tokenA[0].tempTile)=='D'||*(tokenA[0].tokenTowerPosition)>0)
        {return *(tokenA[0].tokenTowerPosition);}
        
            grid[newRow][newCol] = *(tokenA[0].tempTile);
            tokenA[0].tempTile = &tempA[0];
            currPositionA[0] = -1; // Reset position for Player A first token
            grid[1][1] = 'a';
            printf("\nPlayer %c has killed the token of Player A\n", tokenChar);
            return 1;
            break;

        case 'b':
        if(*(tokenB[0].tempTile)=='S'||*(tokenB[0].tempTile)=='A'||*(tokenB[0].tempTile)=='B'||*(tokenB[0].tempTile)=='C'||*(tokenB[0].tempTile)=='D'||*(tokenB[0].tokenTowerPosition)>0)
        {return *(tokenB[0].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenB[0].tempTile);
            tokenB[0].tempTile = &tempB[0]; // Reset position for Player B first token
            currPositionB[0] = -1;
            grid[1][11] = 'b';
            printf("\nPlayer %c has killed the token of Player B\n", tokenChar);
           return 1;
           break;

        case 'c':
        if(*(tokenC[0].tempTile)=='S'||*(tokenC[0].tempTile)=='A'||*(tokenC[0].tempTile)=='B'||*(tokenC[0].tempTile)=='C'||*(tokenC[0].tempTile)=='D'||*(tokenC[0].tokenTowerPosition)>0)
        {return *(tokenC[0].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenC[0].tempTile);
            tokenC[0].tempTile = &tempC[0];
            currPositionC[0] = -1; // Reset Player C's first token position
            grid[11][1] = 'c';
            printf("\nPlayer %c has killed the token of Player C\n", tokenChar);
            return 1;
            break;

        case 'd':
        if(*(tokenD[0].tempTile)=='S'||*(tokenD[0].tempTile)=='A'||*(tokenD[0].tempTile)=='B'||*(tokenD[0].tempTile)=='C'||*(tokenD[0].tempTile)=='D'||*(tokenD[0].tokenTowerPosition)>0)
        {return *(tokenD[0].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenD[0].tempTile);
            tokenD[0].tempTile = &tempD[0];
            currPositionD[0] = -1; // Reset Player D's first token position
            grid[11][11] = 'd';
            printf("\nPlayer %c has killed the token of Player D\n", tokenChar);
            return 1;
            break;

        // tokens at index 1
        case 's':
        if(*(tokenA[1].tempTile)=='S'||*(tokenA[1].tempTile)=='A'||*(tokenA[1].tempTile)=='B'||*(tokenA[1].tempTile)=='C'||*(tokenA[1].tempTile)=='D'||*(tokenA[1].tokenTowerPosition)>0)
        {return *(tokenA[1].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenA[1].tempTile);
            tokenA[1].tempTile = &tempA[1];
            currPositionA[1] = -1; // Reset position for Player A first token
            grid[1][3] = 's';
            printf("\nPlayer %c has killed the token of Player A\n", tokenChar);
            return 1;
            break;

        case 'n':
        if(*(tokenB[1].tempTile)=='S'||*(tokenB[1].tempTile)=='A'||*(tokenB[1].tempTile)=='B'||*(tokenB[1].tempTile)=='C'||*(tokenB[1].tempTile)=='D'||*(tokenB[1].tokenTowerPosition)>0)
        {return *(tokenB[1].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenB[1].tempTile);
            tokenB[1].tempTile = &tempB[1]; // Reset position for Player B first token
            currPositionB[1] = -1;
            grid[1][13] = 'n';
            printf("\nPlayer %c has killed the token of Player B\n", tokenChar);
            return 1;
            break;

        case 'v':
        if(*(tokenC[1].tempTile)=='S'||*(tokenC[1].tempTile)=='A'||*(tokenC[1].tempTile)=='B'||*(tokenC[1].tempTile)=='C'||*(tokenC[1].tempTile)=='D'||*(tokenC[1].tokenTowerPosition)>0)
        {return *(tokenC[1].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenC[1].tempTile);
            tokenC[1].tempTile = &tempC[1];
            currPositionC[1] = -1; // Reset Player C's first token position
            grid[11][3] = 'v';
            printf("\nPlayer %c has killed the token of Player C\n", tokenChar);
            return 1;
            break;

        case 'e':
        if(*(tokenD[1].tempTile)=='S'||*(tokenD[1].tempTile)=='A'||*(tokenD[1].tempTile)=='B'||*(tokenD[1].tempTile)=='C'||*(tokenD[1].tempTile)=='D'||*(tokenD[1].tokenTowerPosition)>0)
        {return *(tokenD[1].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenD[1].tempTile);
            tokenD[1].tempTile = &tempD[1];
            currPositionD[1] = -1; // Reset Player D's first token position
            grid[11][13] = 'e';
            printf("\nPlayer %c has killed the token of Player D\n", tokenChar);
            return 1;
            break;

        // tokens at index 2
        case 'q':
        if(*(tokenA[2].tempTile)=='S'||*(tokenA[2].tempTile)=='A'||*(tokenA[2].tempTile)=='B'||*(tokenA[2].tempTile)=='C'||*(tokenA[2].tempTile)=='D'||*(tokenA[2].tokenTowerPosition)>0)
        {return *(tokenA[2].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenA[2].tempTile);
            tokenA[2].tempTile = &tempA[2];
            currPositionA[2] = -1; // Reset position for Player A first token
            grid[3][1] = 'q';
            printf("\nPlayer %c has killed the token of Player A\n", tokenChar);
            return 1;
            break;

        case 'j':
        if(*(tokenB[2].tempTile)=='S'||*(tokenB[2].tempTile)=='A'||*(tokenB[2].tempTile)=='B'||*(tokenB[2].tempTile)=='C'||*(tokenB[2].tempTile)=='D'||*(tokenB[2].tokenTowerPosition)>0)
        {return *(tokenB[2].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenB[2].tempTile);
            tokenB[2].tempTile = &tempB[2]; // Reset position for Player B first token
            currPositionB[2] = -1;
            grid[3][11] = 'j';
            printf("\nPlayer %c has killed the token of Player B\n", tokenChar);
            return 1;
            break;

        case 'f':
        if(*(tokenC[2].tempTile)=='S'||*(tokenC[2].tempTile)=='A'||*(tokenC[2].tempTile)=='B'||*(tokenC[2].tempTile)=='C'||*(tokenC[2].tempTile)=='D'||*(tokenC[2].tokenTowerPosition)>0)
        {return *(tokenC[2].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenC[2].tempTile);
            tokenC[2].tempTile = &tempC[2];
            currPositionC[2] = -1; // Reset Player C's first token position
            grid[13][1] = 'f';
            printf("\nPlayer %c has killed the token of Player C\n", tokenChar);
            return 1;
            break;

        case 'r':
        if(*(tokenD[2].tempTile)=='S'||*(tokenD[2].tempTile)=='A'||*(tokenD[2].tempTile)=='B'||*(tokenD[2].tempTile)=='C'||*(tokenD[2].tempTile)=='D'||*(tokenD[2].tokenTowerPosition)>0)
        {return *(tokenD[2].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenD[2].tempTile);
            tokenD[2].tempTile = &tempD[2];
            currPositionD[2] = -1; // Reset Player D's first token position
            grid[13][11] = 'r';
            printf("\nPlayer %c has killed the token of Player D\n", tokenChar);
            return 1;
            break;

        // tokens at index 3
        case 'w':
        if(*(tokenA[3].tempTile)=='S'||*(tokenA[3].tempTile)=='A'||*(tokenA[3].tempTile)=='B'||*(tokenA[3].tempTile)=='C'||*(tokenA[3].tempTile)=='D'||*(tokenD[3].tokenTowerPosition)>0)
        {return *(tokenA[3].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenA[3].tempTile);
            tokenA[3].tempTile = &tempA[3];
            currPositionA[3] = -1; // Reset position for Player A first token
            grid[3][3] = 'w';
            printf("\nPlayer %c has killed the token of Player A\n", tokenChar);
            return 1;
            break;

        case 'h':
        if(*(tokenB[3].tempTile)=='S'||*(tokenB[3].tempTile)=='A'||*(tokenB[3].tempTile)=='B'||*(tokenB[3].tempTile)=='C'||*(tokenB[3].tempTile)=='D'||*(tokenB[3].tokenTowerPosition)>0)
        {return *(tokenB[3].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenB[3].tempTile);
            tokenB[3].tempTile = &tempB[3]; // Reset position for Player B first token
            currPositionB[3] = -1;
            grid[3][13] = 'h';
            printf("\nPlayer %c has killed the token of Player B\n", tokenChar);
            return 1;
            break;

        case 'g':
        if(*(tokenC[3].tempTile)=='S'||*(tokenC[3].tempTile)=='A'||*(tokenC[3].tempTile)=='B'||*(tokenC[3].tempTile)=='C'||*(tokenC[3].tempTile)=='D'||*(tokenC[3].tokenTowerPosition)>0)
        {return *(tokenC[3].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenC[3].tempTile);
            tokenC[3].tempTile = &tempC[3];
            currPositionC[3] = -1; // Reset Player C's first token position
            grid[13][3] = 'g';
            printf("\nPlayer %c has killed the token of Player C\n", tokenChar);
            return 1;
            break;

        case 't':
        if(*(tokenD[3].tempTile)=='S'||*(tokenD[3].tempTile)=='A'||*(tokenD[3].tempTile)=='B'||*(tokenD[3].tempTile)=='C'||*(tokenD[3].tempTile)=='D'||*(tokenD[3].tokenTowerPosition)>0)
        {return *(tokenD[3].tokenTowerPosition);}
            grid[newRow][newCol] = *(tokenD[3].tempTile);
            tokenD[3].tempTile = &tempD[3];
            currPositionD[3] = -1; // Reset Player D's first token position
            grid[13][13] = 't';
            printf("\nPlayer %c has killed the token of Player D\n", tokenChar);
            return 1;
            break;

        default:
            return 0;
            break;
    }
    
}

void TopTokensDecrmenter(int currentRow,int currentCol,int limit_low)
{
    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenA[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenA[i].tokenTowerPosition)>limit_low)
        {*(tokenA[i].tokenTowerPosition)--;}
    }

    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenB[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenB[i].tokenTowerPosition)>limit_low)
        {*(tokenB[i].tokenTowerPosition)--;}
    }

    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenC[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenC[i].tokenTowerPosition)>limit_low)
        {*(tokenC[i].tokenTowerPosition)--;}
    }

    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenD[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenD[i].tokenTowerPosition)>limit_low)
        {*(tokenD[i].tokenTowerPosition)--;}
    }

    
}


/*this function is used in during stops when two tokens are on the same stop
Case one token ,lets say token x, is underneath another token, lets say token y.
when token y moves before token x, it should give token x the current tile
i.e tempTile in player structs, value and get token x tokenchar, so that
any sort of visual token duplication, or painting error is does not occurs
*/
void tokenOnTop(int currentRow, int currentCol, int tokenChar, char *tempTile, int* tokenTowerPosition)
{
    if(tokenChar==grid[currentRow][currentCol])
    {return;}
    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenA[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenA[i].tokenTowerPosition)==*(tokenTowerPosition)+1)
        { TopTokensDecrmenter(currentRow,currentCol,*(tokenTowerPosition));
            *(tokenA[i].tempTile)=*(tempTile);
            *(tokenTowerPosition)=0;
            return;
        }
    }

    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenB[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenB[i].tokenTowerPosition)==*(tokenTowerPosition)+1)
        { TopTokensDecrmenter(currentRow,currentCol,*(tokenTowerPosition));
            *(tokenB[i].tempTile)=*(tempTile);
            *(tokenTowerPosition)=0;
            return;
        }
    }


    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenC[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenC[i].tokenTowerPosition)==*(tokenTowerPosition)+1)
        { TopTokensDecrmenter(currentRow,currentCol,*(tokenTowerPosition));
            *(tokenC[i].tempTile)=*(tempTile);
            *(tokenTowerPosition)=0;
            return;
        }
    }


    for(int i=0;i<4;i++)
    {   int tempcurrPosition=*(tokenD[i].currPosition);
        int tempRow = pathway[tempcurrPosition][0];
        int tempCol = pathway[tempcurrPosition][1];
        if(tempRow==currentRow&&tempCol==currentCol&&*(tokenD[i].tokenTowerPosition)==*(tokenTowerPosition)+1)
        { TopTokensDecrmenter(currentRow,currentCol,*(tokenTowerPosition));
            *(tokenD[i].tempTile)=*(tempTile);
            *(tokenTowerPosition)=0;
            return;
        }
    }
}

// Dice roll function
int rollDice()
{
    return (rand() % 6) + 1;
}


// Thread function for Player A's game loop
void *gameThread(void *arg)
{
    // cast pointer to struct
    //for getting access  to specific data structure
    struct PlayerArgs *playerArgs = (struct PlayerArgs *)arg;
    
    char tokenChar = playerArgs->tokenChar;
    int *currPosition = playerArgs->currPosition;
    char *tempTile = playerArgs->tempTile;
    int* tokenTowerPosition=playerArgs->tokenTowerPosition;
    int killCount = playerArgs->killCount;
    
    //function call
    //moving Player to specific position
    movePlayerWithPathway(tokenChar);

    while (1)
    {
        printf("Press Enter to roll the dice for Player %c...", tokenChar);
        getchar(); // Wait for input

        int diceRoll = rollDice();
        printf("\nPlayer %c rolled a %d!\n", tokenChar, diceRoll);

        if (*currPosition == -1 && diceRoll != 6)
        {
            // If in home area, do not overwrite with '.'
            // Instead, keep the token representation
            printf("Player %c is in their home area and cannot move.\n", tokenChar);
        }
        else
        {
            // Move Player's token
            moveToken(currPosition, tempTile, tokenChar,tokenTowerPosition, diceRoll);
        }

        // Display updated grid
        displayGrid();
    }
    return NULL;
}

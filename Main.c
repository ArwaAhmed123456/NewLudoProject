//g++ -o ludo1 Main.c Grid.c Route.c Threads.c PlayerMovement.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "Grid.h"
#include "Route.h"
#include "GlobalStruct.h"
#include "Threads.h"
#include "GlobalStruct.h"


// Define the lock here
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


//calling functions from PlayerMovement
// Declare the function prototype for moveToken
void moveToken(int *currPosition, char *tempTile, char tokenChar, int* tokenTowerPosition, int steps);

//declaration
void movePlayerWithPathway(char tokenChar);
void *gameThread(void* arg);
void initializePlayerArgs(void);  // Add this declaration



// PlayerArgs for each token
struct PlayerArgs tokenA[4], tokenB[4], tokenC[4], tokenD[4];




int main()
{pthread_t threads[16];
    int threadIndex = 0;

    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);

    initializePathway();
    initializeGrid();
    initializePlayerArgs();

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[threadIndex++], NULL, gameThread, &tokenA[i]);
        pthread_create(&threads[threadIndex++], NULL, gameThread, &tokenB[i]);
        pthread_create(&threads[threadIndex++], NULL, gameThread, &tokenC[i]);
        pthread_create(&threads[threadIndex++], NULL, gameThread, &tokenD[i]);
    }

    for (int i = 0; i < 16; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;}
/// this  has been re commited

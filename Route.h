//Pathways.h
#ifndef ROUTE_H
#define ROUTE_H

// Maximum size for the pathway (all '.' cells in the grid)
#define MaxPathwayLength 255

// Array to hold coordinates of the pathway
extern int pathway[MaxPathwayLength][2];

// Length of the pathway (number of '.' cells)
extern int pathwayLength;

void initializePathway();

void RedPathUH();
void RedPathDH();
void RedMiddle();
void YellowPathUp();
void YellowMiddle();
void YellowPathDown();
void GreenPathForward();
void GreenMiddle();
void GreenPathDown();
void BluePathDown(); 
void BlueMiddle();
void BluePathUp();
void RedInnerPath();
void YellowInnerPath();
void BlueInnerPath();
void GreenInnerPath();



#endif


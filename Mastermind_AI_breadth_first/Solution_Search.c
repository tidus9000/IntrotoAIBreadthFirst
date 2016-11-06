/*
*  Project - Breadth First search AI solver
*  File    - Solution_Search.c
*  Date    - 4/11/16
*  Purpose - A set of functions that will be used by the system to perform breadth first search on the system.
*  Author  - Nathan Butt (n86-64)
*/

// Dependancies
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#include "Solution_Search.h"

// The pegs that the
char PegChoice[4] = { 'r', 'g', 'b','y' };
int previousScore = 0;

void GenerateInitialGuess(char pegs[], int Size)
{
	char InitialGuess;

	srand((unsigned int)time(NULL)); 
	workingCandidate.numberOfDefinedValues = Size;

	InitialGuess = PegChoice[rand() % 4];


	int i;
	for (i = 0; i < Size; i++) 
	{
		pegs[i] = workingCandidate.variableValues[i] = InitialGuess;
	}

}

void UpdateScore(int NewScore)
{
	previousScore = workingCandidate.score;
	workingCandidate.score = NewScore;
}


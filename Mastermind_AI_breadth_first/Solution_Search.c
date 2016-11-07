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

// The pegs that the AI can choose from
char PegChoice[4] = { 'r', 'g', 'b','y' };

char previousCounters[4][4];

// the previous score
int previousScore = 0;

int listCounter = 0;
int retrieveListCounter = 0;

void GenerateInitialGuess(char pegs[], int size)
{
	char InitialGuess;

	srand((unsigned int)time(NULL)); 
	workingCandidate.numberOfDefinedValues = size;

	InitialGuess = PegChoice[rand() % 4];


	int i;
	for (i = 0; i < size; i++) 
	{
		pegs[i] = workingCandidate.variableValues[i] = InitialGuess;
	}

}

void GenerateListofSolutions(int size)
{
	candidateSolution generatedSolution;

	int i;
	int j;

	generatedSolution.numberOfDefinedValues = size;

	for (i = 0; i < size; i++) 
	{
		generatedSolution = workingCandidate;

		for (j = 0; j < size; j++) 
		{
			if (PegChoice[j] != generatedSolution.variableValues[j]) 
			{
				generatedSolution.variableValues[i] = PegChoice[j];
				currentListOfCandidates.listEntries[listCounter] = generatedSolution;
				listCounter++;
			}
		}
	}

	CleanCandidate(&generatedSolution);
}

void RetrieveGeneratedSolution(char solutionBuffer[], int size)
{
	AddWorkingCandidateToExaminedList();
	CopySolutionFromCurrentListIntoWorkingCandidate(retrieveListCounter);

	int i;
	for (i = 0; i < size; i++) 
	{
		solutionBuffer[i] = workingCandidate.variableValues[i];
	}
}

void UpdateScore(int newScore)
{

	workingCandidate.score = newScore;
}


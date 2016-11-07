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
int  searchLevel = 0;

// the previous score
int previousScore = 0;

int listCounter = 0;
int retrieveListCounter = 0;

int Character = 0;

struct PegScore currentScore;
struct PegScore PreviousScore;

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
			if (PegChoice[j] != generatedSolution.variableValues[j] && previousCounters[i][j] != PegChoice[j]) 
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

	retrieveListCounter += 1;
}

void UpdateScore(int newScore)
{
	workingCandidate.score = newScore;
}

bool isWorkingCandidateViable()
{
	SetScoreForGuess(&currentScore, workingCandidate.score, 4);
	SetScoreForGuess(&PreviousScore, listOfExaminedCandidates.listEntries[listOfExaminedCandidates.indexOfLastEntryAdded].score, 4);

	if (currentScore.Blackpegs <= PreviousScore.Blackpegs) 
	{
		if (currentScore.Blackpegs == PreviousScore.Blackpegs) 
		{
			if (currentScore.Whitepegs <= PreviousScore.Whitepegs) 
			{
				return false;
			}
			return true;
		}
		else 
		{
			return false;
		}
	}
	else 
	{ 
		return true;
	}
}

void UpdateSearch()
{
	switch (isWorkingCandidateViable()) 
	{
	case true:

		UpdateDuplicateInfo();
		GenerateListofSolutions(4);
		break;
	case false:
		CopySolutionParam1_IntoSolutionParam2(&listOfExaminedCandidates.listEntries[listOfExaminedCandidates.indexOfLastEntryAdded], &workingCandidate);
		break;
	}
}

void UpdateDuplicateInfo()
{
	int i;
	for (i = 0; i > 4; i++) 
	{
		previousCounters[i][Character] = workingCandidate.variableValues[i];
	}
	Character++;
}

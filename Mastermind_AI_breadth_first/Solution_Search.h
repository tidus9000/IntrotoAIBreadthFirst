/*
*  Project - Breadth First search AI solver
*  File    - Solution_Search.h
*  Date    - 4/11/16
*  Purpose - A set of functions that will be used by the system to perform breadth first search on the system. 
*  Author  - Nathan Butt (n86-64)  
*/

#pragma once

#ifndef _cplusplus
  typedef int bool;
  #define true 1
  #define false 0
#endif


#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "Helpers.h"



// Search Globals
candidateSolution workingCandidate;     //this one will hold the soltion we arecurrently considering
candidateList  currentListOfCandidates; // this list will store all the soltion we have created but not examined yet
candidateList listOfExaminedCandidates; // this is where we will store all the ones we're done with

/* 
* System Discription - The system will perform the search in two phases.
* 
* Phase 1:
* Randomly generate a single peg which will be used to make an initial guess and get an initial score. 
*
* Phase 2: 
* Work through the breadth first search generating each possible result and working through the list. 
*/


// Generates the first guess that the system will make.
void GenerateInitialGuess(char pegs[], int size);

// Generates a list of possible solutions based on the working candidate.
void GenerateListofSolutions(int size);

// Retrieve the generated solution for testing. 
void RetrieveGeneratedSolution(char solutionBuffer[], int size);

// Retrieves the score for the working candidiate and performs a viablility check providing the list of unexamined candidates is full.
void UpdateScore(int newScore);

// Checks the viability of a solution. 
int isWorkingCandidateViable();

// perform the next stage of the search based on the viability of the last search. 
void UpdateSearch();

// records any known duplicates characters. 
void UpdateDuplicateInfo();
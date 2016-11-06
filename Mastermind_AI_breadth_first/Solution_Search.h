/*
*  Project - Breadth First search AI solver
*  File    - Solution_Search.h
*  Date    - 4/11/16
*  Purpose - A set of functions that will be used by the system to perform breadth first search on the system. 
*  Author  - Nathan Butt (n86-64)  
*/

#pragma once

#include "StructureDefinitions.h"
#include "SolutionListOperations.h"


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
void GenerateInitialGuess(char pegs[], int Size);

// Generates a list of possible solutions. 
// void GenerateListofSolutions();


// Retrieves the score for the working candidiate.
void UpdateScore(int NewScore);
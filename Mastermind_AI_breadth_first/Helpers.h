/*
*  Project - Breadth First search AI solver
*  File    - Helpers.h
*  Date    - 7/11/16
*  Purpose - A set of Routienes that will assist with the system.
*  Author  - Nathan Butt (n86-64)
*/

#pragma once


// Stores the score of the pegs for evalutaion of the solution.
struct PegScore
{
	int Blackpegs;
	int Whitepegs;
};

// sets the score for the attempt. 
void SetScoreForGuess(struct PegScore* scoreValue, int score, int numberOfPegs);

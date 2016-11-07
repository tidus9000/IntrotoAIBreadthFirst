/*
*  Project - Breadth First search AI solver
*  File    - Helpers.c
*  Date    - 7/11/16
*  Purpose - A set of Routienes that will assist with the system.
*  Author  - Nathan Butt (n86-64)
*/

#include "Helpers.h"

void SetScoreForGuess(struct PegScore * scoreValue, int score, int numberOfPegs)
{
	scoreValue->Blackpegs = score / numberOfPegs;
	scoreValue->Whitepegs = score % numberOfPegs;
}

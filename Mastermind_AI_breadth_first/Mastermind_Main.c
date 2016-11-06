

//
//  main.c
//  MastermindTest
//
//  Created by Jim Smith on 26/09/2014.
//  Copyright (c) 2014 James Smith. All rights reserved.
// simple command line version of the mastermind game
//

#pragma warning (disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Additional #include statements (for breadth-first search solution)
#include "Solution_Search.h"

//some #defined values
#define NUMPEGS 4
#define LEFTOUTER 0
#define LEFTMID 1
#define RIGHTMID 2
#define  RIGHTOUTER 3

//a way of getting the number of whitre/balck pegs from the int score
#define WHITEPEGS(x) ( (x) % NUMPEGS)
#define BLACKPEGS(x) ((x)/NUMPEGS)



// finally here are some functions I've written to save time
void SetNewChallenge(char *challenge);
int ScoreCandidateSolution(char *attempt, char *target);

char GetValidGuessForPeg(void);



int main(int argc, const char * argv[])
{
	char target[NUMPEGS], candidate[NUMPEGS];

	char userResponse;
	int attempts = 0, scoreForAttempt = 0, peg = 0;

	// begin by setting a new goal
	SetNewChallenge(target);


	//prompt the user to start
	printf("Are you ready to start?\n Please type y or Y to begin\n");
	// read two chars: first is the value they input (stored in UserResponse),
	// second is the <return which we discard using %*c
	scanf("%c%*c", &userResponse);

	//only proceed if they have given the right response
	while ((userResponse != 'y') && (userResponse != 'Y'))
	{ ///if not valid keep promptong and reading until it is valid
		printf("%c is not a valid response\n Please type y or Y followed by <return> to begin: ", userResponse);
		scanf("%c%*c", &userResponse);
	}


	//start off there are no right pieces
	scoreForAttempt = 0;

	// now lets do the main goal loop
	while (BLACKPEGS(scoreForAttempt) < NUMPEGS)
	{

		printf("enter q to quit or any other key followed by <return>to continue:");
		scanf("%c%*c", &userResponse);
		if (userResponse == 'q')
			break;
		else
		{
			if (attempts < 1) 
			{
				// Nathan Butt (n86-64) - Generates starting state to begin the search. 
				GenerateInitialGuess(candidate, NUMPEGS);
			}
			else 
			{
				//loop over each peg position
				for (peg = 0; peg < NUMPEGS; peg++)
				{
					//prompt the user to fill in the slot correctly and set the value in thisTryleftOutside

					// (Nathan Butt) TODO - Write search routienes. 
					printf(" What is your guess for  peg %d? ", peg);
					candidate[peg] = GetValidGuessForPeg();
				}
			}
		}

		attempts++;

		/* now the attempt is complete we can call the function to score it
		* that will set the values of the variables  numberOfRightPieces  and numberOfRightColoursInWrongPlace
		* It would be friendly to print out a message saying what the score was...
		*/
		scoreForAttempt = ScoreCandidateSolution(candidate, target);
		UpdateScore(scoreForAttempt);
		printf("The score for the guess:");
		for (peg = 0; peg<NUMPEGS; peg++)
		{
			printf(" %c", candidate[peg]);
		}
		printf(" was %d black and %d white pegs\n", BLACKPEGS(scoreForAttempt), WHITEPEGS(scoreForAttempt));



	} //end of while loop


	if (BLACKPEGS(scoreForAttempt) == NUMPEGS)
		printf("Well done you have solved the puzzle in %d attempts!\n", attempts);
	return 0;
}




char GetValidGuessForPeg(void)
{
	char guess = '-', userResponse;
	int  readOK = 0;
	while (readOK == 0)
	{
		printf("\n\tPlease enter one of r, g, b or y followed by <return>:");
		// read two chars: first is the value they input (stored in UserResponse),
		// second is the <return which we discard using %*c
		scanf("%c%*c", &userResponse);
		switch (userResponse)
		{
		case 'r': //fall through to 4th ok case
		case 'y':
		case 'g':
		case 'b': readOK = 1;
			guess = userResponse;
			break;
		default: readOK = 0;
		}
	}

	return guess;

}


/////DONT CHANGE ANYTHING BELOW THIS LINE


/* void SetNewGoal(void)
* simple function that creates 4 randon colours for the target
* doesn;t need any inputs or outputs
*/
void SetNewChallenge(char *challenge)
{

	int colourAsInt, peg;
	char colour;
	//initialise the rando, number generator from the time in seconds
	srand((unsigned int)time(NULL));

	//loop over each position in the target
	for (peg = 0; peg<NUMPEGS; peg++)
	{
		//generate a number between 0 and 3
		colourAsInt = rand() % 4;
		//convert this to a char for thre colour
		if (colourAsInt == 0)
			colour = 'r';
		else if (colourAsInt == 1)
			colour = 'y';
		else if (colourAsInt == 2)
			colour = 'b';
		else
			colour = 'g';
		//set the value
		challenge[peg] = colour;
	}


	printf("Target sequence is:");
	for (peg = 0; peg<NUMPEGS; peg++)
	{
		printf(" %c", challenge[peg]);
	}
	printf("\n");
}


/* void ScoreThisTry(void);
* function that change the values of the counter of correct/mispalced counters to score this attempt
* no inout or output
*/
int ScoreCandidateSolution(char *attempt, char *target)
{

	//start off by zero-ing the counters
	int numberOfRightPieces = 0, numberOfRightColoursInWrongPlace = 0;

	//keep track of how many times we have counted each of the goal colours
	int peg, peg2, pegUsedInScore[NUMPEGS];
	for (peg = 0; peg<NUMPEGS; peg++)
	{
		pegUsedInScore[peg] = 0;
	}


	//look for utterly correct pieces first
	for (peg = 0; peg<NUMPEGS; peg++)
	{
		if (target[peg] == attempt[peg])
		{
			pegUsedInScore[peg] = 1;
			numberOfRightPieces++;
		}
	}

	//if not solved, we need to count partial matches
	if (numberOfRightPieces <NUMPEGS)
	{

		//consider each peg in turn
		for (peg = 0; peg < NUMPEGS; peg++)
		{
			//if peg was not a match in the right place
			if (attempt[peg] != target[peg])
			{
				//look elsewhere along the target  for a possible match
				for (peg2 = 0; peg2 < NUMPEGS; peg2++)
				{
					//only consider target pegs that have not already been matched already
					if ((pegUsedInScore[peg2] == 0) && (attempt[peg] == target[peg2]))
					{
						//increase count of white pegs
						numberOfRightColoursInWrongPlace++;
						//mark target peg as no longer available for matching
						pegUsedInScore[peg2] = 1;
						//stop looking at this peg in the attempt
						break;
					}
				}

			}
		}

	}
	return (NUMPEGS* numberOfRightPieces + numberOfRightColoursInWrongPlace);

}


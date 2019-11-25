
/**************************************************************************
//randomtestcard2.c test function minionEffect
**/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "minionEffect"

// assert helper function
void assertCheck(int A, int B);

int main() {

	int choice1;
	int choice2;
	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int thisPlayer = 0;
	int handPos = 0;
	struct gameState beforeState, afterState;
	int k[10] = { baron, minion, ambassador, embargo, tribute, mine, cutpurse, remodel, smithy, village };

	initializeGame(numPlayers, k, seed, &beforeState);

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	for (int i = 0; i < 1000; i++) {
		seed = rand() % 1000 + 1;
		choice1 = rand() % 2;
		choice2 = 1 - choice1;
		initializeGame(numPlayers, k, seed, &beforeState);
		
		for (int i = 0; i < numPlayers; i++) {
			beforeState.handCount[i] = rand() % 6;
		}
		
		memcpy(&afterState, &beforeState, sizeof(struct gameState));
		minionEffect(&afterState, thisPlayer, handPos, choice1, choice2);
		
		if (choice1) {
			printf("Coin should increase by 2. ");
			assertCheck(beforeState.coins + 2, afterState.coins);
		}
		else if (choice2) {
			printf("Current player should have 4 cards in hand. ");
			assertCheck(afterState.handCount[thisPlayer], 4);
			for (int i = 0; i < numPlayers; i++) {
				if (i != thisPlayer) {
					if (beforeState.handCount[i] > 4) {
						printf("Other players 5 or more cards now have 4. ");
						assertCheck(afterState.handCount[i], 4);
					}
				}
			}
		}
	
	
	}

	return 0;
}

void assertCheck(int A, int B)
{
	if (A == B)
		printf("Test passed\n");
	else
		printf("Test failed\n");
}



/*
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "minionEffect"

//assert function
void assert_function(int A, int B);

int main() {

	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int player = 0;
	int choice1;
	int choice2;
	struct gameState preState, postState;
	int handPos = 0;
	int k[10] = {adventurer, minion, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	
	initializeGame(numPlayers, k, seed, &preState);

	printf("** Function Test for Minion Card **\n");

	for (int i = 0; i < 2000; i++) {
		seed = rand() % 1000 + 1;
		choice1 = rand() % 2;
		choice2 = 1 - choice1;
		initializeGame(numPlayers, k, seed, &preState);
		
		for (int i = 0; i < numPlayers; i++) {
			preState.handCount[i] = rand() % 6;
		}
		
		memcpy(&postState, &preState, sizeof(struct gameState));
		minionEffect(&postState, player, choice1, choice2, handPos);
		
		if (choice1) {
			printf("plus 2 to coin count");
			assert_function(preState.coins + 2, postState.coins);
		}
		else if (choice2) {
			printf("player has 4 cards");
			assert_function(postState.handCount[player], 4);
			for (int i = 0; i < numPlayers; i++) {
				if (i != player) {
					if (preState.handCount[i] > 4) {
						printf("Anyone who had 5 plus cards, now has 4 cards");
						assert_function(postState.handCount[i], 4);
					}
				}
			}
		}
	
	
	}

	return 0;
}

void assert_function(int A, int B)
{
	if (A == B)
		printf("  Passes\n");
	else
		printf("  Fails\n");
}
*/

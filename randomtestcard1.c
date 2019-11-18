/**************************************************************************
//randomtestcard1.c test function baronEffect
*************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "baronEffect"

//assert function

void assert_function(int A, int B);

int main() {

	
	int seed = rand() % 1000 + 1;
	int numPlayers = 2;
	int player = 0;
	int choice1 = 0;
	struct gameState preState, postState;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	initializeGame(numPlayers, k, seed, &preState);

	printf("** Function Test for Baron Card **\n");

	for (int i = 0; i < 2000; i++) {
		seed = rand() % 1000 + 1;
		initializeGame(numPlayers, k, seed, &preState);
		choice1 = rand() % 2;

		preState.supplyCount[estate] = rand() % 3;
		
		for (int i = 0; i < 5; i++) {
			preState.hand[player][i] = rand() % 27 + 1;
			}
		
		memcpy(&postState, &preState, sizeof(struct gameState));

		baronEffect(&postState, player, choice1);

		if (choice1 > 0) {
			int thisCard = 0;
			int noEstateFound = 1;
			while(noEstateFound) {
				if(postState.hand[player][thisCard] == estate) {
					printf("plus 4 to coin count");
					assert_function(preState.coins + 4, postState.coins);
					printf("plus 1 to discard count");
					assert_function(preState.discardCount[player] + 1, postState.discardCount[player]);
					noEstateFound = 0;
				}
				else if(thisCard > postState.handCount[player]) {
					printf("choice1= 1, supply count decreases by 1");
					assert_function(preState.supplyCount[estate] - 1, postState.supplyCount[estate]);
					noEstateFound = 0;
				}
				else {
					thisCard++;
				}
			}
		}
		else {
			printf("choice1= 0, supply count decreases by 1");
			assert_function(preState.supplyCount[estate] - 1, postState.supplyCount[estate]);
			
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


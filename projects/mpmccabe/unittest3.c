//unittest3.c ambassadorEffect
//ambassadorEffect test

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> 

//assert function
void assert_Function(int A, int B, int test);

int main()
{
	int choice1 = 0;
	int choice2 = 0;
	int handPos = 0;
	
	int result = 0;
	int seed = rand() % 2000 + 1;
    
	int numPlayers = 2;
    int player = 0;
	
	struct gameState preState, postState;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    
	printf("** Function Test for Ambassador Card **\n");

	 //test checks player discards more than they should
   
	initializeGame(numPlayers, k, seed, &preState);
	
	//Test
	printf("Did each other player gain a supply card\n");
	memcpy(&postState, &preState, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 2;
	ambassadorEffect(&postState, player, choice1, choice2, handPos);
	for (int i = 0; i < postState.numPlayers; i++)
	{
		if (i != player)
		{
			printf("Player %d: ", i);
			printf("Count before getting a card: %d\n", preState.handCount[i]);
			printf("Count after getting a card: %d\n", postState.handCount[i]);
			printf("Player %d should have gained a card\n", i);
			assert_Function(postState.handCount[i], preState.handCount[i] + 1, 4);
		}
	}
		
	//Test
	printf("choice1 = handPos, should return -1\n");
	memcpy(&postState, &preState, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 1;
	handPos = 1;
	result = ambassadorEffect(&postState, player, choice1, choice2, handPos);
	printf("choice1 != handPos \n");
	assert_Function(result, -1, 3);

			
	//Test 
	printf("Player chose more supply cards than allowed. Should return -1\n");
	memcpy(&postState, &preState, sizeof(struct gameState));
	choice2 = 2;
	result = ambassadorEffect(&postState, player, choice1, choice2, handPos);
	printf("choice2 > 2\n");
	assert_Function(result, -1, 1);

	//Test
	printf("player chose less supply cards than allowed. Should return -1\n");
	memcpy(&postState, &preState, sizeof(struct gameState));
	choice2 = -1;
	result = ambassadorEffect(&postState, player, choice1, choice2, handPos);
	printf("choice2 < 0 \n");
	assert_Function(result, -1, 2);

	
	//Test 
	printf("Are trashed cards returned to supply pile\n");
	memcpy(&postState, &preState, sizeof(struct gameState));
	ambassadorEffect(&postState, player, choice1, choice2, handPos);
	for (int cardCount = 0; cardCount < choice2; cardCount++)
	{
		for (int i = 0; i < postState.handCount[player]; i++)
		{
			if (postState.hand[player][i] == postState.hand[player][choice1])
			{
				printf("card returned for player %d\n", i);
				assert_Function(postState.hand[player][i], postState.hand[player][choice1], 5);
			}
		}
	}

	return 0;
}

void assert_Function(int A, int B, int test)
{
	if (A == B)
		printf("Test %d passes\n\n", test);
	else
		printf("Test %d fails\n\n", test);
}



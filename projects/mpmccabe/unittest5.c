//unittest5.c mineEffect
//mineEffect test

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//state = &G 

//assert function
int assert_function(int evaluate)
{
    //return 0 for false 
    if (!evaluate)
    {
        return 0;
    }
    //return 1 for true
    return 1;
};

int main()
{
    int seed = 1000;
	int numPlayers = 2;
    int player = 0;
	int unittest = 1;
    int result;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    

    printf("** Function Test 5 for Mine Card **\n");
	
	memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    //player hand
    G.hand[player][0] = curse;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    //curse card choice1 
    result = mineEffect(curse, silver, &G, 4, player);

    if (assert_function(result == -1))
    {
        printf("\tUnittest %d Passes - Expect -1 choice1: result = %d\n", unittest, result);
    }
    else
    {
        printf("\tUnittest %d Fails - exception handling for choice1: result = %d\n", unittest, result);
    }
    unittest++;
	
	
    //test checks exchanges copper for copper
    // if ((getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2))
    // { return -3; }
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    
    //player hand with mine
    G.hand[player][0] = curse;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = copper;
    G.hand[player][4] = mine;

    //choice1 copper, choice 2 copper
    result = mineEffect(1, copper, &G, 4, player);

    //expect 0 result 
    if (assert_function(result == 0))
    {
        printf("\tUnittest %d Passed - copper for copper exchange: amount = %d\n", unittest, result);
    }
    else
    {
        printf("\tUnittest %d Fails - copper for copper not allowed: amount = %d\n", unittest, result);
    }
    unittest++;
	
	//test checks for one silver card
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    
    //player cards
    G.hand[player][0] = copper;
    G.hand[player][1] = copper;
    G.hand[player][2] = copper;
    G.hand[player][3] = mine;
    G.hand[player][4] = copper;

    //choice1 copper, choice2 silver
    result = mineEffect(4, silver, &G, 3, player);

    //silver card count
    int silverCards = 0;
    for (int i = 0; i < G.handCount[player]; i++)
    {
        if (G.hand[player][i] == silver)
        {
            silverCards++;
        }
    }

    if (assert_function(silverCards == 1))
    {
        printf("\tUnittest %d Passes - correct silver card count: amount = %d\n", unittest, silverCards);
    }
    else
    {
        printf("\tUnittest %d Fails - wrond silver card count: amount = %d\n", unittest, silverCards);
    }
    unittest++;

	printf("** End Function Test 5: mineEffect **");
}


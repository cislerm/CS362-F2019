//unittest1.c baronEffect
//baronEffect test

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <stdlib.h>

//state = &G

// assert function
int assert_function(int evaluate)
{
    // return 0 for false
    
    if (!evaluate)
    {
        return 0;
    }
    // return 1 for true
    return 1;
};

int main()
{
    int seed = 1000;
	int numPlayers = 2;
    int player = 0;
	int unittest = 1;
	int estateSupply;
    int result;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    printf("** Function Test for Baron Card **\n");
	
	 //test checks estate supplyCount from "else" is decremented once
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    //Does player have an estate card, no
    G.hand[player][0] = mine;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;
    //estate supply count
    estateSupply = G.supplyCount[estate];
    //play baron 
    baronEffect(1, 0, &G, 4, player);

    //result < original estate supply count by 1. 
    if ((result = assert_function(G.supplyCount[estate] + 1 == estateSupply)))
    {
        printf("\tUnittest %d Success - supplyCount decremented once: supplyCount: %d < Original: %d\n", unittest, G.supplyCount[estate], estateSupply);
    }
    else
    {
        printf("\tUnittest %d Fails - supplyCount decremented > once: supplyCount: %d < Original: %d\n", unittest, G.supplyCount[estate], estateSupply);
    }

	 //Test checks coins for state are incremented by 4
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    //Does player have estate 
    G.hand[player][0] = estate;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;

    //play baron card
    G.coins = 0;
    baronEffect(1, 1, &G, 4, player);

    if ((result = assert_function(G.coins == 4)))
    {
        printf("\tUnittest %d Passes - Coins incremented: Coins = %d\n", unittest, G.coins);
    }
    else
    {
        printf("\tUnittest %d Fails - Coins not incremented: Coins = %d\n", unittest, G.coins);
    }
    unittest++;
	
	
    //Test checks numBuys increased when card is played
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    //initialize player holding a baron card
    G.hand[player][4] = baron;
    //play baron
    baronEffect(1, 0, &G, 4, player);
	
    // numBuys 2
    if ((result = assert_function(G.numBuys == 2))) 
    {
        printf("\tUnittest %d Passes - numBuys incremented: numBuys = %d\n", unittest, G.numBuys);
    }
    else
    {
        printf("\tUnittest %d Fails - numBuys not incremented: numBuys = %d\n", unittest, G.numBuys);
    }
    unittest++;

	
   

    //Test checks handCount is decremented if they have estate
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // Does player have estate
    G.hand[player][0] = estate;
    G.hand[player][1] = mine;
    G.hand[player][2] = mine;
    G.hand[player][3] = mine;
    G.hand[player][4] = baron;

    //play baron 
    baronEffect(1, 1, &G, 4, player);
    //should be 4, player has 5 cards
    if ((result = assert_function(G.handCount[player] == 4))) 
    {
        printf("\tUnittest %d Passes - handCount decremented: handCount = %d\n", unittest, G.handCount[player]);
    }
    else
    {
        printf("\tUnittest %d Fails - handCount not decremented: handCount = %d\n", unittest, G.handCount[player]);
    }
    unittest++;

   
    printf("** End Function Test 1: baronEffect **");
}


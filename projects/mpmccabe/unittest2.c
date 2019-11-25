//unittest2.c minionEffect
//minionEffect test

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
    //return1 for true
    return 1;
};

int main()
{
    int seed = 1000;
	int numPlayers = 2;
    int player = 0;
	int coins;
	int unittest = 1;
    int result;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	
    printf("** Function Test for Minion Card **\n");
	
	//test checks choice1 coins incremented by 2
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;
    coins = G.coins;
    //play minion for choice1
    minionEffect(0, 1, 0, &G, 4, player); 

    if ((result = assert_function(G.coins >= coins + 2)))
    {
        printf("\tUnittest %d Passes - coins incremented by 2: coins = %d, prevcoins = %d\n", unittest, G.coins, coins);
    }
    else
    {
        printf("\tUnittest %d Fails - coins not incremented by 2: coins = %d prevcoins = %d\n", unittest, G.coins, coins);
    }
    unittest++;
	
	//test check choice2 draw 4
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    //player2 hand
    G.hand[1][0] = mine;
    G.hand[1][1] = mine;
    G.hand[1][2] = mine;
    G.hand[1][3] = mine;
    G.hand[1][4] = mine;
    G.handCount[1] = 5; //handCount set

    G.hand[player][4] = minion; //hand has a minion
    int handCount = G.handCount[player];
	//play minion choice2
    minionEffect(0, 0, 1, &G, 4, player); 

    if ((result = assert_function(G.handCount[player] < handCount)))
    {
        printf("\tUnittest %d Passes - player drew 4: amount = %d\n", unittest, G.handCount[player]);
    }
    else
    {
        printf("\tUnittest %d Fails - player drew > 4: amount = %d\n", unittest, G.handCount[player]);
    }
    unittest++;

   

    //test checks player actions incremented once 
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;
	//play minion
    minionEffect(0, 0, 0, &G, 4, player); 

    if ((result = assert_function(G.numActions > 1)))
    {
        printf("\tUnittest %d Passes - numActions incremented: numAction = %d\n", unittest, G.numActions);
    }
    else
    {
        printf("\tUnittest %d Fails - numActions not incremented: numAction = %d\n", unittest, G.numActions);
    }
    unittest++;

    

    //test checks that minion is discarded
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][4] = minion;
    //play minion
    minionEffect(0, 1, 0, &G, 4, player); 
    //should be -1
    if ((result = assert_function(G.hand[player][4] == -1))) 
    {
        printf("\tUnittest %d Passes - minion discarded: amount = %d\n", unittest, G.hand[player][4]); 
    }
    else
    {
        printf("\tUnittest %d Fails - minion not discarded: amount = %d\n", unittest, G.hand[player][4]);
    }
    unittest++;

	 printf("** End Function Test 2: minionEffect **");
}



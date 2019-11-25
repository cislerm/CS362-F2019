//unittest4.c tributeEffect
//tributeEffect test

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//state = &G

// assert function 
int assert_function(int evaluate)
{
    //return 0 for false 
    
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
    int player1 = 0;
    int player2 = 1;
    int unittest = 1;
    int tributeRevealed[2] = {-1, -1};
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    printf("** Function Test for Tribute Card **\n");
	
	// Test checks number of coins incremented
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // tributeRevealed reset
    tributeRevealed[0] = copper;
    tributeRevealed[1] = copper;

    int numCoins = G.coins;

    // player 1 hand
    G.hand[player1][4] = tribute;

    // player 2 hand
    G.discardCount[player2] = 2;
    G.deckCount[player2] = 2;

    tributeEffect(tribute, tributeRevealed, &G, player1, player2);

    // only adds 2 coins 
    if (assert_function(G.coins == numCoins + 2))
    {
        printf("\tUnittest %d Passes - coin total + 2: coint total = %d\n", unittest, G.coins);
    }
    else
    {
        printf("\tUnittest %d Fails - coint total + >2: coin total = %d\n", unittest, G.coins);
    }
    unittest++;
	

    // Test checks statement that decrements nextPlayer discardCount
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // tributeRevealed reset
    tributeRevealed[0] = -1;
    tributeRevealed[1] = -1;

    // player1 hand
    G.hand[player1][4] = tribute;

    // player2 hand
    G.discardCount[player2] = 1;
    G.deckCount[player2] = 0;

    tributeEffect(tribute, tributeRevealed, &G, player1, player2);

    if (assert_function(G.discardCount[player2] == 0))
    {
        printf("\tUnittest %d Passes - player2 deckCount was decremented: discardCount = %d\n", unittest, G.discardCount[player2]);
    }
    else
    {
        printf("\tUnittest %d Fails - player2 deckCount not decremented: discardCount = %d\n", unittest, G.discardCount[player2]);
    }
    unittest++;

	
	
	 // Test checks if statement when the nextPlayer deckCount is decremented
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    // player1 hand
    G.hand[player1][4] = tribute;

    // player2 hand
    G.discardCount[player2] = 0;
    G.deckCount[player2] = 1;

    tributeEffect(tribute, tributeRevealed, &G, player1, player2);

    // deckCount decremented by 1
    if (assert_function(G.deckCount[player2] == 0))
    {
        printf("\tUnittest %d Passes - player2 deckCount was decremented: deckCount = %d\n", unittest, G.deckCount[player2]);
    }
    else
    {
        printf("\tUnittest %d Fails - player2 deckCount not decremented: deckCount = %d\n", unittest, G.deckCount[player2]);
    }
    unittest++;
	
	// Test checks number of coins decremented
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
    // tributeRevealed reset
    tributeRevealed[0] = copper;
    tributeRevealed[1] = copper;

    //int numCoins = G.coins;

    // player 1 hand
    G.hand[player1][4] = tribute;

    // player 2 hand
    G.discardCount[player2] = 2;
    G.deckCount[player2] = 2;

    tributeEffect(tribute, tributeRevealed, &G, player1, player2);

    // check if subtracts 2 coins 
    if (assert_function(G.coins == numCoins - 2))
    {
        printf("\tUnittest %d Passes - coin total - 2: coint total = %d\n", unittest, G.coins);
    }
    else
    {
        printf("\tUnittest %d Fails - coint total - >2: coin total = %d\n", unittest, G.coins);
    }
    unittest++;
	
	printf("** End Function Test 4: tributeEffect **\n");
   
}


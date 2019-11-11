//unittest3.c ambassadorEffect
//ambassadorEffect test

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//state = %G 

//assert function
int assert_Function(int evaluate)
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
    
	printf("** Function Test for Ambassador Card **\n");

	 //test checks player discards more than they should
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

	//player has 1 curse, 1 ambassador
    G.hand[player][3] = curse;     
    G.hand[player][4] = ambassador; 

	//choice1 and discard more than they should 
    result = ambassadorEffect(0, 3, 2, &G, 4, 0); 

    //-3, correct and didn't discard too many
    if (assert_Function(result == -3))
    {
        printf("\tUnittest %d Passes - won't discard more than they have: amount = %d\n", unittest, result);
    }
    else
    {
        printf("\tUnittest %d Fails - discards more than they have: amount = %d\n", unittest, result);
    }
    unittest++;
	
	 //test checks that opponent gets discarded card copy 
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

	//player has curse and ambassador
    G.hand[player][3] = curse;     
    G.hand[player][4] = ambassador; 

    int discardCount = G.discardCount[1];
    ambassadorEffect(0, 3, 1, &G, 4, 0);

    if (assert_Function(G.discardCount[1] > discardCount))
    {
        printf("\tUnittest %d Passes - Opponent gets copy of discard: amount = %d\n", unittest, G.discardCount[1]);
    }
    else
    {
        printf("\tUnittest %d Fails - Opponent does not get copy of discard: amountt = %d\n", unittest, G.discardCount[1]);
    }
    unittest++;
	
	 //test checks choice1 correct 
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

	//player1 has ambassador, 1 curse 
    G.hand[player][3] = curse;     
    G.hand[player][4] = ambassador; 
	
	//choice1 matches handPos 
    result = ambassadorEffect(0, 4, 2, &G, 4, 0); 

    //-2, choice1 correct
    if (assert_Function(result == -2))
    {
        printf("\tUnittest %d Passes - choice1 correct: amount = %d\n", unittest, result);
    }
    else
    {
        printf("\tUnittest %d Fails - choice1 wrong: amount = %d\n", unittest, result);
    }
    unittest++;

    //test checks choice2 is correct 
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
	
	//player1 has ambassador, 2 curse
    G.hand[player][3] = curse;
    G.hand[player][3] = curse;      
    G.hand[player][4] = ambassador; 

	//choice2 result out of bounds
    result = ambassadorEffect(0, 0, 3, &G, 4, 0);
    
    //-1, correct 
    if (assert_Function(result == -1))
    {
        printf("\tUnittest %d Passes - choice2 correct: amount = %d\n", unittest, result);
    }
    else
    {
        printf("\tUnittest %d Fails - choice2 wrong: amount = %d\n", unittest, result);
    }
    unittest++;

   

    printf("** End Function Test 3: ambassadorEffect **");
}

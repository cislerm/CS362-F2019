/**************************************************************************
//randomtestcard3.c test function tributeEffect
*************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <time.h>


//assert function, return 1 for true
//A = Actual, B = Expected

int assert_function(int A, int B){
	printf("Actual: %d, Expected: %d\n", A, B);
    if(A == B) return 1;
	else return 0;
}


//gameState assert function, return 1 for true
//A = Pre, B = Post

int assert_statefunction(struct gameState *pre, struct gameState *post){
  if(memcmp(pre, post, sizeof(struct gameState)) == 0) return 1;
else return 0;
}

//compare pre/post gameState of tribute card
//pass returns 1, fails returns 0

int testTribute(int preState, int postState, struct gameState *post){

  struct gameState pre;
  int revealed[2] = {-1, -1};
  memcpy (&pre, post, sizeof(struct gameState));

  int r;

  r = tributeEffect(0, 0, 0, 0, post, 0, 0, preState, postState, revealed);

  int j;
  int i;
  int c;
  int count;
  int deckCounter;
  
  if ((pre.discardCount[postState] + pre.deckCount[postState]) <= 1){
    if(pre.deckCount[postState] > 0){
      revealed[0] = pre.deck[postState][pre.deckCount[postState]-1];
      pre.deckCount[postState]--;
    }
    else if (pre.discardCount[postState] > 0){
	  revealed[0] = pre.discard[postState][pre.discardCount[postState]-1];
      pre.discardCount[postState]--;
    }
  }

  else{
    if (pre.deckCount[postState] == 0){
      for (i = 0; i < pre.discardCount[postState]; i++){
        pre.deck[postState][i] = pre.discard[postState][i];
        pre.deckCount[postState]++;
        pre.discard[postState][i] = -1;
        pre.discardCount[postState]--;
      }
      shuffle(postState, &pre);
    }
    revealed[0] = pre.deck[postState][pre.deckCount[postState]-1];
    pre.deck[postState][pre.deckCount[postState]--] = -1;
    pre.deckCount[postState]--;
    revealed[1] = pre.deck[postState][pre.deckCount[postState]-1];
    pre.deck[postState][pre.deckCount[postState]--] = -1;
    pre.deckCount[postState]--;
  }

  if (revealed[0] == revealed[1]){
    pre.playedCards[pre.playedCardCount] = revealed[1];
    pre.playedCardCount++;
    revealed[1] = -1;
  }

  for (j = 0; j <= 2; j++){
    if (revealed[j] == copper || revealed[j] == silver || revealed[j] == gold){
      pre.coins += 2;
    }
    else if (revealed[j] == estate || revealed[j] == duchy || revealed[j] == province || revealed[j] == gardens || revealed[j] == great_hall){
      //draw 2 cards
      for(c = 0; c < 2; c++){
        //draw cards, copied from drawCard
        if (pre.deckCount[preState] <= 0){
          for (i = 0; i < pre.discardCount[preState];i++){
            pre.deck[preState][i] = pre.discard[preState][i];
            pre.discard[preState][i] = -1;
          }

          pre.deckCount[preState] = pre.discardCount[preState];
          pre.discardCount[preState] = 0;

          shuffle(preState, &pre);

          pre.discardCount[preState] = 0;
          count = pre.handCount[preState];

          deckCounter = pre.deckCount[preState];

          if (deckCounter == 0) return -1;

          pre.hand[preState][count] = pre.deck[preState][deckCounter - 1];
          pre.deckCount[preState]--;
          pre.handCount[preState]++;
        }
        else{
          count = pre.handCount[preState];
          deckCounter = pre.deckCount[preState];
          pre.hand[preState][count] = pre.deck[preState][deckCounter - 1];
          pre.deckCount[preState]--;
          pre.handCount[preState]++;
        }
      }
    }
    else if (revealed[j] != curse && revealed[j] != -1){
      pre.numActions = pre.numActions + 2;
    }
  }

  if(assert_function(r, 0) && assert_statefunction(&pre, post)) return 1;
  
  else return 0;
}

int main() {
  int n;
  int i;
  int numTests = 2000;
  int count = 0;
  clock_t t;
  struct gameState G;
  int maxp = 4;
  int preState;
  int postState;

  //run random tests
  printf("**Function Test for Tribute Card **\n");
  
  t = clock();
  for (n = 0; n < numTests; n++){
    for(i = 0; i < sizeof(struct gameState); i++){
      ((char*)&G)[i] = floor(Random() *256);
    }
    preState = floor(Random() * maxp);
    if(preState == 3) postState = 0;
    else postState = preState + 1;
    G.deckCount[preState] = floor(Random() * MAX_DECK);
    G.discardCount[preState] = floor(Random() * MAX_DECK);
    G.playedCardCount = floor(Random() * MAX_DECK);
    G.handCount[preState] = floor(Random() * MAX_HAND);
    for(i = 0; i < G.handCount[preState]; i++){
      G.hand[preState][i] = floor(Random() * 27);
    }
    if(n < numTests/4){
      //selection narrowed to get greater chance of values <=1
      G.deckCount[postState] = floor(Random() * 21);
      G.discardCount[postState] = floor(Random() * 21);
    } else {
      //test whole range possible values 
      G.deckCount[postState] = floor(Random() * MAX_DECK);
      G.discardCount[postState] = floor(Random() * MAX_DECK);
    }
      G.handCount[postState] = floor(Random() * MAX_HAND);
      for(i = 0; i < G.deckCount[postState]; i++){
      G.deck[postState][i] = floor(Random() * 27);
    }
      for(i = 0; i < G.playedCardCount; i++){
      G.playedCards[i] = floor(Random() * 27);
    }
      count += testTribute(preState, postState, &G);
	
  }

  t = clock() - t;
  printf("%d out of %d passed, took %f seconds\n", count, numTests, ((float)t) / CLOCKS_PER_SEC);

  return 0;
}


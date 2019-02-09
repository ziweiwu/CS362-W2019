#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

/*
Functions to test

villageAction
*/
static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;

void testVillageAction() {
  int allPassed = 0;

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, 1, &G);

  int original_hand_size = G.handCount[CURRENT_PLAYER];
  int original_num_actions = G.numActions;
  
  cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
  // Assert +1 card
  if (assert(G.handCount[CURRENT_PLAYER], original_hand_size + 1 - 1)) {
    printf("villageAction: PASS, draw 1 card\n");
  } else {
    allPassed++;
  }

  // Assert +2 action
  if (assert(G.numActions, original_num_actions + 2 - 1)) {
    printf("villageAction: PASS, add 2 actions\n");
  } else {
    allPassed++;
  }

  // reset game state
  memset(&G, 23, sizeof(struct gameState));
  initializeGame(PLAYERS, k, 1, &G);

  if (allPassed==2) {
    printf("---villageAction: All Passed---\n");
  } else if(allPassed == 0){
    printf("---villageAction: None Passed ---\n");
  }else{
    printf("---villageAction: Some Passed ---\n");
  }
}

int main() {
  printf("---Testing for villageAction---\n");
  testVillageAction();
  return 0;
}

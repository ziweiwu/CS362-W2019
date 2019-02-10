#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

/*
test card village
*/
static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;

void testVillage() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, 1, &G);

  // Assert +1 card
  int original_hand_size = G.handCount[CURRENT_PLAYER];
  /*printf("original hand size is %d\n", original_hand_size);*/
  for (int i = 0; i < 5; i++) {
    cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
    if (assert(G.handCount[CURRENT_PLAYER], original_hand_size)) {
      printf("played village, hand size remains at %d\n", original_hand_size);
    }
  }

  memset(&G, 23, sizeof(struct gameState));
  initializeGame(PLAYERS, k, 1, &G);

  // Assert +2 action
  int original_num_actions = G.numActions;
  /*printf("original number of actions is %d\n", original_num_actions);*/
  for (int i = 0; i < 5; i++) {
    cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
    if (assert(G.numActions, original_num_actions + 2 * (i + 1))) {
      printf("played village, added 2 actions\n");
    }
  }
}

int main() {
  printf("---Testing for villageAction---\n");
  testVillage();
  return 0;
}

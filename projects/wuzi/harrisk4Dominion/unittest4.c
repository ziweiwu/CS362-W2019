#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

/*
test function isGameOver
*/
static const int PLAYERS = 4;
static const int SEED = 1;

void testIsGameOver() {
  printf("---Testing for isGameOver---\n");
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, SEED, &G);

  int allPassed = 1;
  // check based empty supply pile count
  for (int i = 0; i < 25; i++) {
    G.supplyCount[i] = 0;
    if (i < 2) {
      if (assert(isGameOver(&G), 0) == 0) {
        allPassed = -1;
      }
    } else {
      if (assert(isGameOver(&G), 1) == 0) {
        allPassed = -1;
      }
    }
  }

  // reset game state
  memset(&G, 0, sizeof(struct gameState));
  initializeGame(PLAYERS, k, SEED, &G);

  // check based on province count
  for (int i = 10; i >= 0; i--) {
    G.supplyCount[province] = i;
    if (i > 0) {
      if (assert(isGameOver(&G), 0) == 0) {
        allPassed = -1;
      }
    } else {
      if (assert(isGameOver(&G), 1) == 0) {
        allPassed = -1;
      }
    }
  }

  if (allPassed == -1) {
    printf("---TEST FAILED---\n");
  } else {
    printf("---TEST PASSED---\n");
  }
}

int main() {
  testIsGameOver();
  return 0;
}

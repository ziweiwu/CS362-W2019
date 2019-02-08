#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/*
Functions to test

isGameOver
*/
static const int PLAYERS = 4;

void testIsGameOver() {
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
	       remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, 1, &G);

  // check based empty supply pile count
  for (int i = 0; i < 25; i++) {
    G.supplyCount[i] = 0;
    if (i < 2) {
      assert(isGameOver(&G) == 0);
      printf(
	  "isGameOver: PASS, the number of empty supply piles is %d, game is "
	  "not over\n",
	  i + 1);
    } else {
      assert(isGameOver(&G) == 1);
      printf(
	  "isGameOver: PASS, the number of empty supply piles is %d, game is "
	  "over\n",
	  i + 1);
    }
  }

  // reset game state
  memset(&G, 23, sizeof(struct gameState));
  initializeGame(PLAYERS, k, 1, &G);

  // check based on province count
  G.supplyCount[province] = 1;
  assert(isGameOver(&G) == 0);
  printf(
      "isGameOver: PASS, the number of province is not 0, game is not over\n");

  G.supplyCount[province] = 0;
  assert(isGameOver(&G) == 1);
  printf("isGameOver: PASS, the number of province is 1, game is over\n");
}

int main() {
  printf("---Testing for isGameOver---\n");
  testIsGameOver();
  printf("---isGameOver: All Passed---\n");
  return 0;
}

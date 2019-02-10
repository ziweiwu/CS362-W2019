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

whoseTurn
*/
static const int PLAYERS = 4;
static const int SEED = 1;
void testWhoseTurn() {
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, SEED, &G);

  assert(whoseTurn(&G), 0);
  printf("whoseTurn, player 1's turn\n");

  endTurn(&G);
  assert(whoseTurn(&G), 1);
  printf("whoseTurn, player 2's turn\n");

  endTurn(&G);
  assert(whoseTurn(&G), 2);
  printf("whoseTurn, player 3's turn\n");

  endTurn(&G);
  assert(whoseTurn(&G), 3);
  printf("whoseTurn, player 4's turn\n");

  endTurn(&G);
  assert(whoseTurn(&G), 0);
  printf("whoseTurn, player 1's turn\n");
}

int main() {
  printf("---Testing for whoseTurn---\n");
  testWhoseTurn();
  return 0;
}

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

fullDeckCount: return the total count of a specific card from hand + deck +
discard
*/

static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;
static const int SEED = 1;

void testFullDeckCount() {
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, SEED, &G);

  // Test for initial deck
  int estate_count = fullDeckCount(CURRENT_PLAYER, estate, &G);
  assert(estate_count, 3);
  printf("fullDeckCount, estate count is 3\n");

  int copper_count = fullDeckCount(CURRENT_PLAYER, copper, &G);
  assert(copper_count, 7);
  printf("fullDeckCount, copper count is 7\n");

  // Add three more cards to discard
  G.discard[CURRENT_PLAYER][0] = copper;
  G.discard[CURRENT_PLAYER][1] = copper;
  G.discard[CURRENT_PLAYER][2] = estate;
  G.discardCount[CURRENT_PLAYER] = 3;

  estate_count = fullDeckCount(CURRENT_PLAYER, estate, &G);
  assert(estate_count, 4);
  printf("fullDeckCount, estate count is 4\n");

  copper_count = fullDeckCount(CURRENT_PLAYER, copper, &G);
  assert(copper_count, 9);
  printf("fullDeckCount, copper count is 9\n");

  // Add three more cards to deck
  G.deck[CURRENT_PLAYER][10] = copper;
  G.deck[CURRENT_PLAYER][11] = copper;
  G.deck[CURRENT_PLAYER][12] = estate;
  G.deckCount[CURRENT_PLAYER] = G.deckCount[CURRENT_PLAYER] + 3;

  estate_count = fullDeckCount(CURRENT_PLAYER, estate, &G);
  assert(estate_count, 5);
  printf("fullDeckCount, estate count is 5\n");

  copper_count = fullDeckCount(CURRENT_PLAYER, copper, &G);
  assert(copper_count, 11);
  printf("fullDeckCount, copper count is 11\n");
}

int main() {
  printf("---Testing for fullDeckCount---\n");
  testFullDeckCount();
  return 0;
}

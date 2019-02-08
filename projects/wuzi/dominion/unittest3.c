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

fullDeckCount
*/

static const int PLAYERS = 4;
static const int PLAYER_1 = 0;

void testFullDeckCount() {
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, 1, &G);

  // Test for initial deck
  int estate_count = fullDeckCount(PLAYER_1, estate, &G);
  assert(estate_count == 3);
  printf("fullDeckCount: PASS, estate count is 3\n");

  int copper_count = fullDeckCount(PLAYER_1, copper, &G);
  assert(copper_count == 7);
  printf("fullDeckCount: PASS, copper count is 7\n");

  // Add three more cards to discard
  G.discard[PLAYER_1][0] = copper;
  G.discard[PLAYER_1][1] = copper;
  G.discard[PLAYER_1][2] = estate;
  G.discardCount[PLAYER_1] = 3;

  estate_count = fullDeckCount(PLAYER_1, estate, &G);
  assert(estate_count == 4);
  printf("fullDeckCount: PASS, estate count is 4\n");

  copper_count = fullDeckCount(PLAYER_1, copper, &G);
  assert(copper_count == 9);
  printf("fullDeckCount: PASS, copper count is 9\n");

  // Add three more cards to deck
  G.deck[PLAYER_1][10] = copper;
  G.deck[PLAYER_1][11] = copper;
  G.deck[PLAYER_1][12] = estate;
  G.deckCount[PLAYER_1] = G.deckCount[PLAYER_1] + 3;

  estate_count = fullDeckCount(PLAYER_1, estate, &G);
  assert(estate_count == 5);
  printf("fullDeckCount: PASS, estate count is 5\n");

  copper_count = fullDeckCount(PLAYER_1, copper, &G);
  assert(copper_count == 11);
  printf("fullDeckCount: PASS, copper count is 11\n");
}

int main() {
  testFullDeckCount();
  return 0;
}

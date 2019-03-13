#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;
static const int SEED = 1;
static const int STARTING_ESTATE = 3;
static const int STARTING_COPPER = 7;

/*
test function fullDeckCount
*/
void testFullDeckCount() {
  printf("---Testing for fullDeckCount---\n");
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, SEED, &G);

  int estate_count = STARTING_ESTATE;
  int copper_count = STARTING_COPPER;

  int allPassed = 1;
  // Test for initial deck
  ;
  if (assert(fullDeckCount(CURRENT_PLAYER, estate, &G), estate_count) == 0) {
    allPassed = -1;
  }

  if (assert(fullDeckCount(CURRENT_PLAYER, copper, &G), copper_count) == 0) {
    allPassed = -1;
  }

  // Test adding cards to discard
  for (int i = 0; i < 5; i++) {
    G.discard[CURRENT_PLAYER][i] = copper;
    G.discardCount[CURRENT_PLAYER]++;
    copper_count++;
    if (assert(fullDeckCount(CURRENT_PLAYER, copper, &G), copper_count) == 0) {
      allPassed = -1;
    }
  }
  for (int i = 5; i < 10; i++) {
    G.discard[CURRENT_PLAYER][i] = estate;
    G.discardCount[CURRENT_PLAYER]++;
    estate_count++;
    if (assert(fullDeckCount(CURRENT_PLAYER, estate, &G), estate_count) == 0) {
      allPassed = -1;
    }
  }

  // Test adding cards to deck
  for (int i = 10; i < 15; i++) {
    G.discard[CURRENT_PLAYER][i] = copper;
    G.discardCount[CURRENT_PLAYER]++;
    copper_count++;
    if (assert(fullDeckCount(CURRENT_PLAYER, copper, &G), copper_count) == 0) {
      allPassed = -1;
    }
  }
  for (int i = 15; i < 20; i++) {
    G.discard[CURRENT_PLAYER][i] = estate;
    G.discardCount[CURRENT_PLAYER]++;
    estate_count++;
    if (assert(fullDeckCount(CURRENT_PLAYER, estate, &G), estate_count) == 0) {
      allPassed = -1;
    }
  }

  if (allPassed == -1) {
    printf("---TEST FAILED---\n");
  } else {
    printf("---TEST PASSED---\n");
  }
}

int main() {
  testFullDeckCount();
  return 0;
}

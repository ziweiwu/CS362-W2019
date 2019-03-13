#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

static const int PLAYERS = 4;
static const int NUM_CARDS_STARTING = 5;
static const int SEED = 1;

/*
  test function numHandCards
*/
void testNumHandCards() {
  printf("---Testing for numHandCards---\n");
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};

  struct gameState G;
  initializeGame(PLAYERS, k, SEED, &G);

  // test starting hand
  int allPassed = 1;
  if (assert(numHandCards(&G), NUM_CARDS_STARTING) == 0) {
    allPassed = -1;
  };

  // test after draw more cards
  for (int i = 0; i < 5; i++) {
    drawCard(whoseTurn(&G), &G);
    if (assert(numHandCards(&G), NUM_CARDS_STARTING + i + 1) == 0) {
      allPassed = -1;
    }
  }

  // test for discarding
  for (int i = 0; i < 10; i++) {
    discardCard(10 - i, whoseTurn(&G), &G, 0);
    if (assert(numHandCards(&G), 10 - i - 1) == 0) {
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
  testNumHandCards();
  return 0;
}

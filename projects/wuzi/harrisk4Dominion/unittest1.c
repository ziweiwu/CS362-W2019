#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

static const int PLAYERS = 4;
static const int SEED = 1;

/*
test function whoseTurn
*/
void testWhoseTurn() {
  printf("---Testing for whoseTurn---\n");
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  struct gameState G;
  initializeGame(PLAYERS, k, SEED, &G);

  // This loops ran endturn() 20 times
  // and check if whoseTurn return the right value
  int allPassed = 1;
  for (int i = 0; i < 20; i++) {
    if (assert(whoseTurn(&G), i % 4) == 0) {
      allPassed = -1;
    }
    endTurn(&G);
  }

  if (allPassed == -1) {
    printf("---TEST FAILED---\n");
  } else {
    printf("---TEST PASSED---\n");
  }
}

int main() {
  testWhoseTurn();
  return 0;
}

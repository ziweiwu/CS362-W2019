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

numHandCards

*/
static const int PLAYERS = 4;
static const int NUM_CARDS_STARTING = 5;
void testNumHandCards() {
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};

  struct gameState G;
  initializeGame(PLAYERS, k, 1, &G);

  // test starting hand
  assert(numHandCards(&G) == NUM_CARDS_STARTING);
  printf("numHandCards: PASS, number of cards in starting hand is 5\n");

  // test after draw more cards
  for (int i = 0; i < 5; i++) {
    drawCard(whoseTurn(&G), &G);
    assert(numHandCards(&G) == NUM_CARDS_STARTING + i + 1);
    printf("numHandCards: PASS, number of cards in starting hand is %d\n",
            5 + i + 1);
  }

  // test for discarding
  for (int i = 0; i < 10; i++) {
    discardCard(10 - i, whoseTurn(&G), &G, 0);
    assert(numHandCards(&G) == 10 - i - 1);
    printf("numHandCards: PASS, number of cards in the hand is %d\n",
           10 - i - 1);
  }
}

int main() {
  testNumHandCards();
  return 0;
}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

static char *const CARD_NAME = "Village";
static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;
static const int SEED = 1;
/*
test card village
*/
void testVillage() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};

  int allPassed = 1;

  struct gameState G, T;
  memset(&G, 0, sizeof(struct gameState));
  memset(&T, 0, sizeof(struct gameState));
  initializeGame(PLAYERS, k, SEED, &G);

  // copy over game state to test
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, &G, sizeof(struct gameState));

  // play the card
  printf("Assert card effect\n");
  cardEffect(village, choice1, choice2, choice3, &T, handpos, &bonus);

  printf("Hand count\n");
  if (assert(T.handCount[CURRENT_PLAYER], G.handCount[CURRENT_PLAYER]) == 0) {
    allPassed = -1;
  }
  printf("Deck count\n");
  if (assert(T.deckCount[CURRENT_PLAYER], G.deckCount[CURRENT_PLAYER] - 1) ==
      0) {
    allPassed = -1;
  }
  printf("Number of actions\n");
  if (assert(T.numActions, G.numActions + 2) == 0) {
    allPassed = -1;
  }
  printf("Number of buys\n");
  if (assert(T.numBuys, G.numBuys) == 0) {
    allPassed = -1;
  }
  printf("Coins\n");
  if (assert(T.coins, G.coins) == 0) {
    allPassed = -1;
  }

  // assert for other player state, kingdom and victory piles
  printf("Assert state change for other players\n");
  if (assertOtherPlayerStateChange(&G, &T, CURRENT_PLAYER) == 0) {
    allPassed = -1;
  }

  printf("Assert state change for victoria pile\n");
  if (assertVictoriaPileChange(&G, &T) == 0) {
    allPassed = -1;
  };

  printf("Assert state change for kingdom pile\n");
  if (assertKingdomPileChange(&G, &T, k, 10) == 0) {
    allPassed = -1;
  }

  if (allPassed == -1) {
    printf("---TEST FAILED---\n");
  } else {
    printf("---TEST PASSED---\n");
  }
}

int main() {
  printf("---Testing for %s---\n", CARD_NAME);
  testVillage();
  return 0;
}

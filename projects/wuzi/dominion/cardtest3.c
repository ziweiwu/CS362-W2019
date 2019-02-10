#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

/*
Card to test smithy
*/
static char *const CARD_NAME = "Smithy";
static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;
static const int SEED = 1;

void testGreatHall() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};

  struct gameState G, T;
  initializeGame(PLAYERS, k, SEED, &G);

  // copy over game state to test
  memcpy(&T, &G, sizeof(struct gameState));

  // play the card
  cardEffect(smithy, choice1, choice2, choice3, &T, handpos, &bonus);
  assert(T.handCount[CURRENT_PLAYER], G.handCount[CURRENT_PLAYER]+2);
  assert(T.deckCount[CURRENT_PLAYER], G.deckCount[CURRENT_PLAYER]-3);
  assert(T.numActions, G.numActions);
  assert(T.numBuys, G.numBuys);
  assert(T.coins, G.coins);

  // assert for other player state, kingdom and victory piles
  printf("Assert state change for other players\n");
  assertOtherPlayerStateChange(&G, &T, CURRENT_PLAYER);

  printf("Assert state change for victoria pile\n");
  assertVictoriaPileChange(&G, &T);

  printf("Assert state change for kingdom pile\n");
  assertKingdomPileChange(&G, &T, k, 10);
}

int main() {
  printf("---Testing for %s---\n", CARD_NAME);
  testGreatHall();
  return 0;
}

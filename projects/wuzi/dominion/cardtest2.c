#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

/*
Card to test greathall
*/
static char *const CARD_NAME = "Great hall";
static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;
static const int SEED = 1;

void testSteward() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};

  struct gameState G, T;
  initializeGame(PLAYERS, k, SEED, &G);
  // copy over game state to test
  memcpy(&T, &G, sizeof(struct gameState));
  int initial_hand_size = T.handCount[CURRENT_PLAYER];
  printf("Initial hand size %d\n", initial_hand_size);
  int initial_deck_size = T.deckCount[CURRENT_PLAYER];
  printf("Initial deck size %d\n", initial_deck_size);
  int initial_coins = T.coins;
  printf("Initial coin %d\n", T.coins);
  int initial_num_action = T.numActions;
  printf("Initial number of actions %d\n", initial_num_action);

  cardEffect(great_hall, choice1, choice2, choice3, &T, handpos, &bonus);
  assert(T.handCount[CURRENT_PLAYER], initial_hand_size + 1 - 1);
  assert(T.numActions, initial_num_action + 1);
  assert(T.deckCount[CURRENT_PLAYER], initial_deck_size - 1);
  assert(T.coins, initial_coins);
}

int main() {
  printf("---Testing for %s---\n", CARD_NAME);
  testSteward();
  return 0;
}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

/*
Card to test Adventurer
reveal your deck until two treasure are found
put the treasure card into your hand and discard other reveal cards
*/
static char *const CARD_NAME = "Adventure";
static const int PLAYERS = 4;
static const int CURRENT_PLAYER = 0;
static const int SEED = 1;

void testGreatHall() {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};

  struct gameState G, T;
  memset(&G, 0, sizeof(struct gameState));
  memset(&T, 0, sizeof(struct gameState));

  initializeGame(PLAYERS, k, SEED, &G);

  // copy over game state to test
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, &G, sizeof(struct gameState));

  // play the card
  printf("Assert card effect for copper treasure\n");
  cardEffect(adventurer, choice1, choice2, choice3, &T, handpos, &bonus);
  assert(T.handCount[CURRENT_PLAYER], G.handCount[CURRENT_PLAYER] + 2);
  assert(T.deckCount[CURRENT_PLAYER], G.deckCount[CURRENT_PLAYER] - 2);
  assert(T.hand[CURRENT_PLAYER][5], copper);
  assert(T.hand[CURRENT_PLAYER][6], copper);
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

  // assert for silver
  printf("Assert card effect for silver treasure\n");
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, &G, sizeof(struct gameState));
  T.deck[CURRENT_PLAYER][0] = silver;
  T.deck[CURRENT_PLAYER][1] = silver;

  cardEffect(adventurer, choice1, choice2, choice3, &T, handpos, &bonus);
  assert(T.handCount[CURRENT_PLAYER], G.handCount[CURRENT_PLAYER] + 2);
  assert(T.deckCount[CURRENT_PLAYER], G.deckCount[CURRENT_PLAYER] - 2);
  assert(T.hand[CURRENT_PLAYER][5], copper);
  assert(T.hand[CURRENT_PLAYER][6], copper);
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

  // assert for gold
  printf("Assert card effect for silver treasure\n");
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, &G, sizeof(struct gameState));
  T.deck[CURRENT_PLAYER][0] = gold;
  T.deck[CURRENT_PLAYER][1] = gold;

  cardEffect(adventurer, choice1, choice2, choice3, &T, handpos, &bonus);
  assert(T.handCount[CURRENT_PLAYER], G.handCount[CURRENT_PLAYER] + 2);
  assert(T.deckCount[CURRENT_PLAYER], G.deckCount[CURRENT_PLAYER] - 2);
  assert(T.hand[CURRENT_PLAYER][5], copper);
  assert(T.hand[CURRENT_PLAYER][6], copper);
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

  // assert when deck is empty
  printf("Assert card effect when deck is empty\n");
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, &G, sizeof(struct gameState));

  T.deckCount[CURRENT_PLAYER] = 0;
  T.discardCount[CURRENT_PLAYER] = 2;
  T.discard[CURRENT_PLAYER][0] = copper;
  T.discard[CURRENT_PLAYER][1] = silver;

  cardEffect(adventurer, choice1, choice2, choice3, &T, handpos, &bonus);
  assert(T.handCount[CURRENT_PLAYER], G.handCount[CURRENT_PLAYER]+2);
  assert(T.deckCount[CURRENT_PLAYER], 0);
  assert(T.hand[CURRENT_PLAYER][5], copper);
  assert(T.hand[CURRENT_PLAYER][6], silver);
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

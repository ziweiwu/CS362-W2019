#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "myAssert.h"
#include "rngs.h"

static char* const CARD_NAME = "Adventurer";
static int SEED = 1;
static int TOTAL_RUNS = 20000;
static int MIN_PLAYERS = 2;
static int MIN_DECK_SIZE = 3;
static int K[10] = {adventurer, council_room, feast,   gardens, mine,
                    remodel,    smithy,       village, baron,   great_hall};

/*
test card adventurer
*/
int testAdventurer(int player, int treasure, struct gameState* G) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int allPassed = 1;

  struct gameState T;
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, G, sizeof(struct gameState));

  int num_treasures = 0;
  for (int i = 0; i < G->deckCount[player]; i++) {
    if (G->deck[player][i] == treasure) {
      num_treasures++;
    }
  }

  cardEffect(adventurer, choice1, choice2, choice3, &T, handpos, &bonus);

  // if there are two treasures in the deck
  if (num_treasures >= 2) {
    printf("There are more than two treasure cards\n");
    printf("Hand count\n");
    if (assert(T.handCount[player], G->handCount[player] + 2) == 0) {
      allPassed = 0;
    }
    printf("if added treasure to hand\n");
    if (assert(T.hand[player][G->handCount[player]], treasure) == 0) {
      allPassed = 0;
    }
    if (assert(T.hand[player][G->handCount[player] + 1], treasure) == 0) {
      allPassed = 0;
    }
  }

  // if there is one treasure in the deck
  if (num_treasures == 1) {
    printf("There are only 1 treasure card\n");
    printf("Hand count\n");
    if (assert(T.handCount[player], G->handCount[player] + 1) == 0) {
      allPassed = 0;
    }
    printf("if added treasure to hand\n");
    if (assert(T.hand[player][G->handCount[player]], treasure) == 0) {
      allPassed = 0;
    }
  }

  // if there is no treasure, treasure cards are drawned from discard
  if (num_treasures == 0) {
    printf("There are no treasure cards, shuffle and drawn from discard\n");
    printf("Hand count\n");
    if (assert(T.handCount[player], G->handCount[player] + 2) == 0) {
      allPassed = 0;
    }
    printf("if added treasure to hand\n");
    if (assert(T.hand[player][G->handCount[player]], treasure) == 0) {
      allPassed = 0;
    }
    if (assert(T.hand[player][G->handCount[player] + 1], treasure) == 0) {
      allPassed = 0;
    }
  }

  // Check for the consistent states
  printf("Number of actions\n");
  if (assert(T.numActions, G->numActions) == 0) {
    allPassed = 0;
  }
  printf("Number of buys\n");
  if (assert(T.numBuys, G->numBuys) == 0) {
    allPassed = 0;
  }
  printf("Coins\n");
  if (assert(T.coins, G->coins) == 0) {
    allPassed = 0;
  }
  printf("Assert state change for other players\n");
  if (assertOtherPlayerStateChange(G, &T, player) == 0) {
    allPassed = 0;
  }
  printf("Assert state change for victoria pile\n");
  if (assertVictoriaPileChange(G, &T) == 0) {
    allPassed = 0;
  };

  printf("Assert state change for kingdom pile\n");
  if (assertKingdomPileChange(G, &T, K, 10) == 0) {
    allPassed = 0;
  }
  return allPassed;
}

/*
Random test card adventurer
*/
void testAdventurerRandom() {
  // set random seed
  SelectStream(0);
  PutSeed(SEED);

  int numPasses = 0;
  struct gameState G;
  for (int n = 0; n < TOTAL_RUNS; n++) {
    // total players should be between 2 and 4
    int total_players = floor(Random() * (MAX_PLAYERS - 1)) + MIN_PLAYERS;

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(total_players, K, SEED, &G);

    int player = floor(Random() * total_players);
    G.deckCount[player] = floor(Random() * (MAX_DECK));

    // test for when there are only 3 cards in the deck
    // required for when shuffle is needed
    if (n > floor(TOTAL_RUNS * 0.5)) {
      G.deckCount[player] = MIN_DECK_SIZE;
    }
    G.discardCount[player] = floor(Random() * MAX_DECK);
    G.handCount[player] = floor(Random() * MAX_HAND);
    G.whoseTurn = player;

    // remove current treasures from deck
    for (int i = 0; i < G.deckCount[player]; i++) {
      if (G.deck[player][i] == copper) {
        G.deck[player][i] = estate;
      }
    }

    // choose a random treasure type
    int num_treasures = floor(Random() * G.deckCount[player]);
    int treasure_choice = floor(Random() * 3);
    int treasure;
    if (treasure_choice == 0) {
      treasure = copper;
    }
    if (treasure_choice == 1) {
      treasure = silver;
    }
    if (treasure_choice == 2) {
      treasure = gold;
    }

    // insert treasures at random index in the deck
    while (num_treasures > 0) {
      int random_index = floor(Random() * G.deckCount[player]);
      if (G.deck[player][random_index] != treasure) {
        G.deck[player][random_index] = treasure;
        num_treasures--;
      }
    }
    numPasses += testAdventurer(player, treasure, &G);
  }

  if (numPasses == 0) {
    printf("None of the random tests passed for %s\n", CARD_NAME);
    return;
  }
  if (numPasses < TOTAL_RUNS) {
    printf("%d out of %d random tests passed for %s\n", numPasses, TOTAL_RUNS,
           CARD_NAME);
    return;
  }
  if (numPasses == TOTAL_RUNS) {
    printf("All random tests passed for %s\n", CARD_NAME);
    return;
  }
}

int main() {
  printf("---Random Testing for %s---\n", CARD_NAME);
  testAdventurerRandom();
  return 0;
}

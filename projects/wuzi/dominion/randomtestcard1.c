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

static char* const CARD_NAME = "Village";
static int SEED = 1;
static int TOTAL_RUNS = 2000;
static int MIN_PLAYERS = 2;
static int K[10] = {adventurer, council_room, feast,   gardens, mine,
                    remodel,    smithy,       village, baron,   great_hall};

/*
test card village
*/
int testVillage(int player, struct gameState* G) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int allPassed = 1;
  
	struct gameState T;
  memset(&T, 0, sizeof(struct gameState));
  memcpy(&T, G, sizeof(struct gameState));

  cardEffect(village, choice1, choice2, choice3, &T, handpos, &bonus);
	
	// check for current player state change
	printf("Hand count\n");
  if (assert(T.handCount[player], G->handCount[player]) == 0) {
    allPassed = 0;
  }

	printf("Deck count\n");
  if (assert(T.deckCount[player], G->deckCount[player] - 1) == 0) {
    allPassed = 0;
  }

	printf("Number of actions\n");
  if (assert(T.numActions, G->numActions + 2) == 0) {
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

  // assert for other player state, kingdom and victory piles
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
Random test card village
*/
void testVillageRandom() {
  // set random seed
  SelectStream(0);
  PutSeed(SEED);

  int numPasses = 0;
  struct gameState G;
  for (int n = 0; n < TOTAL_RUNS; n++) {
    // At least two players are needed
    int total_players = floor(Random() *  MAX_PLAYERS-1) + MIN_PLAYERS;

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(total_players, K, SEED, &G);

    // random set game state
    int player = floor(Random() * total_players);
    G.deckCount[player] = floor(Random() * MAX_DECK);
    G.discardCount[player] = floor(Random() * MAX_DECK);
    G.handCount[player] = floor(Random() * MAX_HAND);
    G.whoseTurn = player;
	 	
		// run tests	
		numPasses += testVillage(player, &G);
  }

	// no tests passed
  if (numPasses == 0) {
    printf("None of the random tests passed for %s\n", CARD_NAME);
    return;
  }
	
	// some tests passed
  if (numPasses < TOTAL_RUNS) {
    printf("%d out of %d random tests passed for %s\n", numPasses, TOTAL_RUNS,
           CARD_NAME);
    return;
  }

	// all tests passed
  if (numPasses == TOTAL_RUNS) {
    printf("All random tests passed for %s\n", CARD_NAME);
    return;
  }
}

int main() {
  printf("---Random Testing for %s---\n", CARD_NAME);
  testVillageRandom();
  return 0;
}

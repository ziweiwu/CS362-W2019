#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

int assert(int a, int b) {
  if (a == b) {
    /*fprintf(stdout, "PASS: %d equals to %d\n", a, b);*/
    return 1;
  }
  fprintf(stdout, "FAIL: %d not equals to %d\n", a, b);
  return 0;
}

void assertOtherPlayerStateChange(struct gameState *before,
                                  struct gameState *after, int current_player) {
  // Check if state is same for other players
  for (int i = 0; i < after->numPlayers; i++) {
    if (i == current_player) {
      continue;
    }
    int player = i;
    if (assert(before->handCount[player], after->handCount[player])) {
      for (int i = 0; i < after->handCount[player]; i++) {
        assert(before->hand[player][i], after->hand[player][i]);
      }
    }
    if (assert(before->deckCount[player], after->deckCount[player])) {
      for (int i = 0; i < after->deckCount[player]; i++) {
        assert(before->deck[player][i], after->deck[player][i]);
      }
    };
  }
}

void assertVictoriaPileChange(struct gameState *before,
                              struct gameState *after) {
  // Check if state is same for victory cards
  assert(before->supplyCount[estate], after->supplyCount[estate]);
  assert(before->supplyCount[duchy], after->supplyCount[duchy]);
  assert(before->supplyCount[province], after->supplyCount[province]);
}
void assertKingdomPileChange(struct gameState *before, struct gameState *after,
                             int *kingdom, int kingdom_size) {
  for (int i = 0; i < kingdom_size; i++) {
    assert(before->supplyCount[kingdom[i]], after->supplyCount[kingdom[i]]);
  }
}

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

int assert(int a, int b) {
  if (a == b) {
    fprintf(stdout, "PASS: %d equals to %d\n", a, b);
    return 1;
  }
  fprintf(stdout, "FAIL: %d not equals to %d\n", a, b);
  return 0;
}

int assertOtherPlayerStateChange(struct gameState *before,
                                 struct gameState *after, int current_player) {
  // Check if state is same for other players
  int isPass = 1;
  for (int i = 0; i < after->numPlayers; i++) {
    if (i == current_player) {
      continue;
    }
    int player = i;
    if (assert(before->handCount[player], after->handCount[player])) {
      for (int i = 0; i < after->handCount[player]; i++) {
        if (assert(before->hand[player][i], after->hand[player][i]) == 0) {
          isPass = 0;
        }
      }
    } else {
      isPass = 0;
    }
    if (assert(before->deckCount[player], after->deckCount[player])) {
      for (int i = 0; i < after->deckCount[player]; i++) {
        if (assert(before->deck[player][i], after->deck[player][i]) == 0) {
          isPass = 0;
        }
      }
    } else {
      isPass = 0;
    }
  }
  return isPass;
}

int assertVictoriaPileChange(struct gameState *before,
                             struct gameState *after) {
  int isPass = 1;
  // Check if state is same for victory cards
  if (assert(before->supplyCount[estate], after->supplyCount[estate]) == 0) {
    isPass = 0;
  }
  if (assert(before->supplyCount[duchy], after->supplyCount[duchy]) == 0) {
    isPass = 0;
  }
  if (assert(before->supplyCount[province], after->supplyCount[province]) ==
      0) {
    isPass = 0;
  }
  return isPass;
}

int assertKingdomPileChange(struct gameState *before, struct gameState *after,
                            int *kingdom, int kingdom_size) {
  int isPass = 1;
  for (int i = 0; i < kingdom_size; i++) {
    if (assert(before->supplyCount[kingdom[i]],
               after->supplyCount[kingdom[i]]) == 0) {
      isPass = 0;
    }
  }
  return isPass;
}

#ifndef _MYASSERT_H
#define _MYASSERT_H

int assert(int a, int b);
void assertOtherPlayerStateChange(struct gameState *before,
                                  struct gameState *after, int current_player);
void assertVictoriaPileChange(struct gameState *before,
                              struct gameState *after);
void assertKingdomPileChange(struct gameState *before, struct gameState *after,
                             int *kingdom, int kingdom_size);
#endif

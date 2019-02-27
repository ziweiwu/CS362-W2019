#ifndef _MYASSERT_H
#define _MYASSERT_H

int assert(int a, int b);

int assertOtherPlayerStateChange(struct gameState *before,
                                 struct gameState *after, int current_player);

int assertVictoriaPileChange(struct gameState *before, struct gameState *after);

int assertKingdomPileChange(struct gameState *before, struct gameState *after,
                            int *kingdom, int kingdom_size);
#endif

#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "card.h"

typedef struct {
  CardInfo* hand[7];
} Player;

void initPlayer();
CardInfo* getHand(int index);
#endif

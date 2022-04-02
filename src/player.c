#include "player.h"
#include <stdio.h>

Player player;


void initPlayer(){

  for(int i = 0; i < 7; i++){
    player.hand[i] = NULL;
  }

  player.hand[0] = getCard(0);
  player.hand[1] = getCard(0);

}

CardInfo* getHand(int index) {
  if(index >= 7 || index < 0) {
    return NULL;
  }

  return player.hand[index];
}

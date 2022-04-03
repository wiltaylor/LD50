#include "player.h"
#include <stdio.h>

Player player;


void initPlayer(){

  for(int i = 0; i < 7; i++){
    player.hand[i] = NULL;
  }

  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    player.backRow[0] = makeUnitInstance(NULL_ID);
    player.frontRow[0] = makeUnitInstance(NULL_ID);
  }

  player.hand[0] = getCard(0);
  player.hand[1] = getCard(1);

  player.backRow[0] = makeUnitInstance(0);
  player.backRow[1] = makeUnitInstance(0);

  player.backRow[0].hp = 1;

  player.frontRow[0] = makeUnitInstance(0);

  player.gold = 10;
  player.wood = 20;
  player.iron = 30;
  player.food = 40;
  player.faith = 50;

}

CardInfo* getHand(int index) {
  if(index >= 7 || index < 0) {
    return NULL;
  }

  return player.hand[index];
}

UnitInstance* getPlayerUnitFront(int index) {
  return &player.frontRow[index];

}

UnitInstance* getPlayerUnitBack(int index) {
  return &player.backRow[index];
}

int getPlayerGold(){
  return player.gold;
}

int getPlayerWood(){
  return player.wood;

}
int getPlayerIron(){
  return player.iron;
}
int getPlayerFood(){
  return player.food;
}
int getPlayerFaith(){
  return player.faith;
}

int getWorkersGold(){
  return player.workersGold;
}
int getWorkersWood(){
  return player.workersWood;
}
int getWorkersIron(){
  return player.workersIron;
}
int getWorkersFood(){
  return player.workersFood;
}
int getWorkersFaith(){
  return player.workersFaith;
}


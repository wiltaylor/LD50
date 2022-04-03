#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "card.h"
#include "constants.h"

typedef struct {
  CardInfo *hand[7];
  UnitInstance frontRow[MAX_UNITS_PER_ROW];
  UnitInstance backRow[MAX_UNITS_PER_ROW];

  int gold;
  int wood;
  int iron;
  int food;
  int faith;
  int workersGold;
  int workersWood;
  int workersIron;
  int workersFood;
  int workersFaith;
} Player;

void initPlayer();

CardInfo *getHand(int index);
UnitInstance *getPlayerUnitFront(int index);
UnitInstance *getPlayerUnitBack(int index);

int getPlayerGold();
int getPlayerWood();
int getPlayerIron();
int getPlayerFood();
int getPlayerFaith();

int getWorkersGold();
int getWorkersWood();
int getWorkersIron();
int getWorkersFood();
int getWorkersFaith();

#endif

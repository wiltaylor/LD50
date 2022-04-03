#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "card.h"
#include "constants.h"

typedef enum {
  NONE,
  SELECT_COMBAT,
  SELECT_RANGED_COMBAT,
} SelectionMode;

typedef struct {
  bool inUse;
  bool attackerFront;
  int attackerIndex;
  Vector2 attackerVector;
  
  bool defenderFront;
  int defenderIndex;
  Vector2 defenderVector;
} AttackInfo;


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
  int turn;
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

void selectFrontRowUnit(int index);
void selectBackRowUnit(int index);
void selectFrontEnemyUnit(int index);
void selectBackEnemyUnit(int index);

Vector2 getCombatStartPoint();

SelectionMode getCurrentSelectionMode();
AttackInfo* getAttackInfo(int index);

void resetSelection();

bool canEndTurn();

int getTurnCount();
void endPlayerTurn();

int damagePlayerFrontUnit(int index, int qty);
int damagePlayerBackUnit(int index, int qty);

void removeDeadPlayerUnits();

int getNextPlayerBackUnit(int index);
int getNextPlayerFrontUnit(int index);

bool canPlayerTargetBackRow();

void DrawCard();
bool canDraw();

bool canCastCard(int index);
void castCard(int index);

#endif

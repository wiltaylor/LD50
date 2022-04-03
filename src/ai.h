#ifndef __AI_H_
#define __AI_H_
#include "card.h"
#include "constants.h"
#include "player.h"

void initAI();
UnitInstance* getAIUnitFront(int index);
UnitInstance* getAIUnitBack(int index);

typedef struct {
  UnitInstance frontRow[MAX_UNITS_PER_ROW];
  UnitInstance backRow[MAX_UNITS_PER_ROW];
  int level;
  int turnsToNextLevel;
} AI;

int damageAIFrontUnit(int index, int qty);
int damageAIBackUnit(int index, int qty);

void removeDeadAIUnits();

void aiTurn();

AttackInfo* getAIAttackInfo(int index);

int countAIBackUnits();
int countAIFrontUnits();

int getAILevel();

#endif

#ifndef __AI_H_
#define __AI_H_
#include "card.h"
#include "constants.h"

void initAI();
UnitInstance* getAIUnitFront(int index);
UnitInstance* getAIUnitBack(int index);

typedef struct {
  UnitInstance frontRow[MAX_UNITS_PER_ROW];
  UnitInstance backRow[MAX_UNITS_PER_ROW];
} AI;


#endif

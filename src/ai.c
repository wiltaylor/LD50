#include "ai.h"

static AI ai;

void initAI(){
  
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    ai.backRow[0] = makeUnitInstance(NULL_ID);
    ai.frontRow[0] = makeUnitInstance(NULL_ID);
  }

  ai.backRow[0] = makeUnitInstance(0);
  ai.backRow[1] = makeUnitInstance(0);

  ai.backRow[0].hp = 1;

  ai.frontRow[0] = makeUnitInstance(0);

  
}

UnitInstance* getAIUnitFront(int index){
  return &ai.frontRow[index];
}
UnitInstance* getAIUnitBack(int index){
  return &ai.backRow[index];
}

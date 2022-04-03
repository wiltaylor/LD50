#include "ai.h"
#include <stdio.h>
#include "gamemode.h"
#include "player.h"

static AI ai;
static float aiTurnTimer;
static bool doneAICombat;
int unitAICounter = 0;

static AttackInfo attacks[MAX_UNITS_PER_ROW * 2];

void initAI(){
  
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    ai.backRow[i] = makeUnitInstance(NULL_ID);
    ai.frontRow[i] = makeUnitInstance(NULL_ID);
  }

  ai.level = 1;
  ai.turnsToNextLevel = 10;

  aiTurnTimer = AI_TURN_LENGTH;
  doneAICombat = false;
}

UnitInstance* getAIUnitFront(int index){
  return &ai.frontRow[index];
}
UnitInstance* getAIUnitBack(int index){
  return &ai.backRow[index];
}

int damageAIFrontUnit(int index, int qty) {
  ai.frontRow[index].hp -= qty;

  if(ai.frontRow[index].unitType == NULL) {
    return 0;
  }

  return ai.frontRow[index].unitType->attack;
}

int damageAIBackUnit(int index, int qty) {
  ai.backRow[index].hp -= qty;

  if(ai.backRow[index].unitType == NULL) {
    return 0;
  }

  return ai.backRow[index].unitType->attack;
}

void removeDeadAIUnits() {
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    if(ai.frontRow[i].hp <= 0) {
      ai.frontRow[i].unitType = NULL;
      ai.frontRow[i].hp = 0;
    }

    if(ai.backRow[i].hp <= 0) {
      ai.backRow[i].unitType = NULL;
      ai.backRow[i].hp =  0;
    }
  }
}

AttackInfo* nextFreeAIAttack() {
  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
    if(attacks[i].inUse == false){
      return &attacks[i];
    }
  }

  return NULL;
}

void AddAIUnit(UnitType type){
  UnitInstance unit = makeUnitInstance(type);

  if(unit.unitType->front) {
    for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
      if(ai.frontRow[i].unitType == NULL) {
        ai.frontRow[i] = unit;
        return;
      }
    }
  }else{
    for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
      if(ai.backRow[i].unitType == NULL) {
        ai.backRow[i] = unit;
        return;
      }

    }
  }
  
}

void processAILevel(){

  unitAICounter--;

  switch(ai.level) {
    case 1:
      if(unitAICounter <= 0){
        AddAIUnit(GOBLIN_ARCHER);
        AddAIUnit(GOBLIN_ARCHER);
        AddAIUnit(GOBLIN_ARCHER);
        unitAICounter = 3;
      }
      break;
    case 2:
      if(unitAICounter <= 0) {
        
        AddAIUnit(ORC);
        AddAIUnit(GOBLIN_ARCHER);
        AddAIUnit(GOBLIN_ARCHER);

        unitAICounter = 2;
      }
      break;
    case 3:
      if(unitAICounter <= 0) {
        AddAIUnit(ORC);
        AddAIUnit(GOBLIN_ARCHER);
        AddAIUnit(ORC);
      }
      break;
    case 4:
      if(unitAICounter <= 0) {
        AddAIUnit(ORC);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(ORC);

        unitAICounter = 2;
      }
      break;
    case 5:
      if(unitAICounter <= 0) {
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(EVIL_MAGE);

        unitAICounter = 2;
      }
      break;
    case 6:
      if(unitAICounter <= 0) {
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(EVIL_MAGE);

        unitAICounter = 2;
      }
      break;
    default:
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(SKELLETON_KNIGHT);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(EVIL_MAGE);
        AddAIUnit(EVIL_MAGE);
      break;
  }

  ai.turnsToNextLevel--;

  if(ai.turnsToNextLevel <= 0){
    ai.turnsToNextLevel = 10;
    ai.level++;
  }

}

void doAICombatTargets(){
  int index = 0;
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++) {
    Vector2 frontAtkVec = {
      AI_FRONT_ROW_FIRST_UNIT.x + i * AI_FRONT_ROW_FIRST_UNIT.width + CARD_PADDING * i + CARD_PADDING + AI_FRONT_ROW_FIRST_UNIT.width / 2,
      AI_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING + AI_FRONT_ROW_FIRST_UNIT.height / 2
    };

    Vector2 backAtkVec = {
      AI_BACK_ROW_FIRST_UNIT.x + i * AI_BACK_ROW_FIRST_UNIT.width + CARD_PADDING * i + CARD_PADDING + AI_BACK_ROW_FIRST_UNIT.width / 2,
      AI_BACK_ROW_FIRST_UNIT.y + CARD_PADDING + AI_BACK_ROW_FIRST_UNIT.height / 2
    };


    if(ai.frontRow[i].unitType != NULL) {
      AttackInfo* atk = nextFreeAIAttack();
    
      atk->inUse = true;
      atk->attackerFront = true;
      atk->attackerIndex = i;
      atk->attackerVector = frontAtkVec;

      atk->defenderFront = true;
      atk->defenderIndex = getNextPlayerFrontUnit(index);

      if (atk->defenderIndex == NULL_ID){
        atk->defenderIndex = getNextPlayerBackUnit(index);
        atk->defenderFront = false;
      }

      if(atk->defenderFront){
        atk->defenderVector.x = PLAYER_FRONT_ROW_FIRST_UNIT.x + atk->defenderIndex * PLAYER_FRONT_ROW_FIRST_UNIT.width + CARD_PADDING * atk->defenderIndex + CARD_PADDING + PLAYER_FRONT_ROW_FIRST_UNIT.width / 2;
        atk->defenderVector.y = PLAYER_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING + PLAYER_FRONT_ROW_FIRST_UNIT.height / 2;
      }else{
        atk->defenderVector.x = PLAYER_BACK_ROW_FIRST_UNIT.x + atk->defenderIndex * PLAYER_BACK_ROW_FIRST_UNIT.width + CARD_PADDING * atk->defenderIndex + CARD_PADDING + PLAYER_BACK_ROW_FIRST_UNIT.width / 2;
        atk->defenderVector.y = PLAYER_BACK_ROW_FIRST_UNIT.y + CARD_PADDING + PLAYER_BACK_ROW_FIRST_UNIT.height / 2;
      }

      index++;
    }

    if(ai.backRow[i].unitType != NULL) {
      AttackInfo* atk = nextFreeAIAttack();

      atk->inUse = true;
      atk->attackerFront = false;
      atk->attackerIndex = i;
      atk->attackerVector = backAtkVec;

      atk->defenderFront = false;
      atk->defenderIndex = getNextPlayerBackUnit(index);

      if (atk->defenderIndex == NULL_ID){
        atk->defenderIndex = getNextPlayerFrontUnit(index);
        atk->defenderFront = true;
      }

      if(atk->defenderFront){
        atk->defenderVector.x = PLAYER_FRONT_ROW_FIRST_UNIT.x + atk->defenderIndex * PLAYER_FRONT_ROW_FIRST_UNIT.width + CARD_PADDING * atk->defenderIndex + CARD_PADDING + PLAYER_FRONT_ROW_FIRST_UNIT.width / 2;
        atk->defenderVector.y = PLAYER_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING + PLAYER_FRONT_ROW_FIRST_UNIT.height / 2;
      }else{
        atk->defenderVector.x = PLAYER_BACK_ROW_FIRST_UNIT.x + atk->defenderIndex * PLAYER_BACK_ROW_FIRST_UNIT.width + CARD_PADDING * atk->defenderIndex + CARD_PADDING + PLAYER_BACK_ROW_FIRST_UNIT.width / 2;
        atk->defenderVector.y = PLAYER_BACK_ROW_FIRST_UNIT.y + CARD_PADDING + PLAYER_BACK_ROW_FIRST_UNIT.height / 2;
      }

      index++;
    }
  }
}

void completeCombat(){
  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++) {
    if(attacks[i].inUse) {
      if(attacks[i].attackerFront) {
        int dmg = ai.frontRow[attacks[i].attackerIndex].unitType->attack;

        if(attacks[i].defenderFront) {
          ai.frontRow[attacks[i].attackerIndex].hp -= damagePlayerFrontUnit(attacks[i].defenderIndex, dmg);
        }else{
          ai.frontRow[attacks[i].attackerIndex].hp -= damagePlayerBackUnit(attacks[i].defenderIndex, dmg);
        }

      }else{
        int dmg = ai.backRow[attacks[i].attackerIndex].unitType->rngAttack;

        if(attacks[i].defenderFront) {
          damagePlayerFrontUnit(attacks[i].defenderIndex, dmg);
        }else{
          damagePlayerBackUnit(attacks[i].defenderIndex, dmg);
        }
      }
    }
    attacks[i].inUse = false;
  }

  removeDeadPlayerUnits();
  removeDeadAIUnits();
}

void aiTurn(){

  aiTurnTimer -= GetFrameTime();

  if(aiTurnTimer <= 0.0f) {
    aiTurnTimer = AI_TURN_LENGTH;
    doneAICombat = false;
    completeCombat();

    setGameMode(MAINGAME_MODE);    
    return;
  }

  if(!doneAICombat) {

    processAILevel();
    doAICombatTargets();
    doneAICombat = true;
  }
}

AttackInfo* getAIAttackInfo(int index) {

  if(index < 0 || index > MAX_UNITS_PER_ROW * 2) {
    return NULL;
  }

  if(attacks[index].inUse) {
    return &attacks[index];
  }

  return NULL;
}

int countAIBackUnits(){
  int count = 0;
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    if(ai.backRow[i].unitType != NULL) {
      count++;
    }
  }

  return count;
}

int countAIFrontUnits() {
  int count = 0;
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    if(ai.frontRow[i].unitType != NULL) {
      count++;
    }
  }

  return count;
}

int getAILevel() {
  return ai.level;
}

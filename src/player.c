#include "player.h"
#include <stdio.h>
#include "ai.h"
#include "gamemode.h"

Player player;
Vector2 combatVector;
int attackerIndex;
bool attackerFront;
bool canEndTurnChecked;
static int backUnitCount = 0;
static int frontUnitCount = 0;
bool haveDrawnThisTurn = false;

SelectionMode selectionMode;
AttackInfo attacks[MAX_UNITS_PER_ROW * 2];

bool canTargetBackRow = false;

void initPlayer(){

  for(int i = 0; i < MAX_HAND_SIZE; i++){
    player.hand[i] = NULL;
  }

  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    player.backRow[0] = makeUnitInstance(NULL_ID);
    player.frontRow[0] = makeUnitInstance(NULL_ID);
  }

  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
    attacks[i].inUse = false;
  }

  player.turn = 1;

  player.gold = STARTING_CARDS * 5;

  for(int i = 0; i < STARTING_CARDS; i++) {
    DrawCard();
    haveDrawnThisTurn = false;
  }

  player.gold = 100;
  player.workersGold = 1;
}

int freeHandPosition() {
  for(int i = 0; i < MAX_HAND_SIZE; i++) {
    if(player.hand[i] == NULL){
      return i;
    }
  }

  return NULL_ID;
}

CardInfo* getHand(int index) {
  if(index >= 7 || index < 0) {
    return NULL;
  }

  return player.hand[index];
}

void checkTargets(){
  int enemyFront = countAIFrontUnits();

  canTargetBackRow = enemyFront == 0;
}

bool CheckIfAllCombatAssigned(){
  int totalUnits = 0;
  int totalAttacks = 0;
  int totalFrontUnits = 0;
  int totalBackUnits = 0;

  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    if(player.backRow[i].unitType != NULL) {
      totalUnits++;
      totalBackUnits++;
    }

    if(player.frontRow[i].unitType != NULL) {
      totalUnits++;
      totalFrontUnits++;
    }
  }

  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
    if(attacks[i].inUse) {
      totalAttacks++;
    }
  }

  frontUnitCount = totalFrontUnits;
  backUnitCount = totalBackUnits;

  return totalUnits <= totalAttacks;
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

void selectFrontRowUnit(int index) {
  checkTargets();

  if(selectionMode == NONE) {
    combatVector.x = PLAYER_FRONT_ROW_FIRST_UNIT.x + index * PLAYER_FRONT_ROW_FIRST_UNIT.width + CARD_PADDING * index + CARD_PADDING + PLAYER_FRONT_ROW_FIRST_UNIT.width / 2;
    combatVector.y = PLAYER_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING + PLAYER_FRONT_ROW_FIRST_UNIT.height / 2;
    attackerIndex = index;
    attackerFront = true;
    selectionMode = SELECT_COMBAT;

    for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
      if(attacks[i].attackerFront && attacks[i].inUse && attacks[i].attackerIndex == index) {
        attacks[i].inUse = false;
      }
    }
  }  
}

void selectBackRowUnit(int index){
  checkTargets();
  if(selectionMode == NONE) {
    combatVector.x = PLAYER_BACK_ROW_FIRST_UNIT.x + index * PLAYER_BACK_ROW_FIRST_UNIT.width + CARD_PADDING * index + CARD_PADDING + PLAYER_BACK_ROW_FIRST_UNIT.width / 2;
    combatVector.y = PLAYER_BACK_ROW_FIRST_UNIT.y + CARD_PADDING + PLAYER_BACK_ROW_FIRST_UNIT.height / 2;
    attackerIndex = index;
    attackerFront = false;
    selectionMode = SELECT_RANGED_COMBAT;

    for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
      if(attacks[i].attackerFront == false && attacks[i].inUse && attacks[i].attackerIndex == index) {
        attacks[i].inUse = false;
      }
    }
  }
}

AttackInfo* nextFreeAttack() {
  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
    if(attacks[i].inUse == false){
      return &attacks[i];
    }
  }

  return NULL;
}

void selectFrontEnemyUnit(int index){
  if(selectionMode == SELECT_COMBAT || SELECT_RANGED_COMBAT) {
    AttackInfo* atk = nextFreeAttack();

    Vector2 targetVector = {
      AI_FRONT_ROW_FIRST_UNIT.x + index * AI_FRONT_ROW_FIRST_UNIT.width + CARD_PADDING * index + CARD_PADDING + AI_FRONT_ROW_FIRST_UNIT.width / 2,
      AI_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING + AI_FRONT_ROW_FIRST_UNIT.height / 2
    };
    
    atk->inUse = true;
    atk->attackerFront = attackerFront;
    atk->attackerIndex = attackerIndex;
    atk->attackerVector = combatVector;

    atk->defenderFront = true;
    atk->defenderIndex = index;
    atk->defenderVector = targetVector;

    selectionMode = NONE;

    canEndTurnChecked = CheckIfAllCombatAssigned();
  }
}

void doCombat() {
  TraceLog(LOG_INFO, "Doing combat");

  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++) {
    TraceLog(LOG_WARNING, TextFormat("%d", i));
    if(attacks[i].inUse) {
      if(attacks[i].attackerFront) {
        int dmg = player.frontRow[attacks[i].attackerIndex].unitType->attack;
        if(attacks[i].defenderFront) {
          player.frontRow[attacks[i].attackerIndex].hp -= damageAIFrontUnit(attacks[i].defenderIndex, dmg);
        }else{
          player.frontRow[attacks[i].attackerIndex].hp -= damageAIBackUnit(attacks[i].defenderIndex, dmg);
        }
      } else {
        int dmg = player.backRow[attacks[i].attackerIndex].unitType->rngAttack;
        if(attacks[i].defenderFront) {
          damageAIFrontUnit(attacks[i].defenderIndex, dmg);
        }else{
          damageAIBackUnit(attacks[i].defenderIndex, dmg);
        }
      }
    }
  }
}

void selectBackEnemyUnit(int index){
  if(selectionMode == SELECT_RANGED_COMBAT || (selectionMode == SELECT_COMBAT && canTargetBackRow)) {
    AttackInfo* atk = nextFreeAttack();

    Vector2 targetVector = {
      AI_BACK_ROW_FIRST_UNIT.x + index * AI_BACK_ROW_FIRST_UNIT.width + CARD_PADDING * index + CARD_PADDING + AI_BACK_ROW_FIRST_UNIT.width / 2,
      AI_BACK_ROW_FIRST_UNIT.y + CARD_PADDING + AI_BACK_ROW_FIRST_UNIT.height / 2
    };
    
    atk->inUse = true;
    atk->attackerFront = attackerFront;
    atk->attackerIndex = attackerIndex;
    atk->attackerVector = combatVector;

    atk->defenderFront = false;
    atk->defenderIndex = index;
    atk->defenderVector = targetVector;

    selectionMode = NONE;

    canEndTurnChecked = CheckIfAllCombatAssigned();
  }
}

Vector2 getCombatStartPoint(){
  return combatVector;
}

SelectionMode getCurrentSelectionMode(){
  return selectionMode;
}

AttackInfo* getAttackInfo(int index) {
  if(index < 0 || index > MAX_UNITS_PER_ROW * 2) {
    return NULL;
  }

  if(attacks[index].inUse == false) {
    return NULL;
  }

  return &attacks[index];
}

void resetSelection() {
  selectionMode = NONE;
  canEndTurnChecked = CheckIfAllCombatAssigned();
}

bool canDrawFaith(){
  return player.faith >= DRAW_DECK_FAITH_COST;
}

bool canDrawGold(){
  return player.gold >= DRAW_DECK_GOLD_COST;
}

bool canEndTurn() {
  return canEndTurnChecked;
}

int getTurnCount() {
  return player.turn;
}

void removeDeadPlayerUnits() {
  for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
    if(player.frontRow[i].hp <= 0) {
      player.frontRow[i].unitType = NULL;
      player.frontRow[i].hp = 0;
      frontUnitCount--;
    }

    if(player.backRow[i].hp <= 0) {
      player.backRow[i].unitType = NULL;
      player.backRow[i].hp =  0;
      backUnitCount--;
    }
  }
}

void endPlayerTurn() {
  doCombat();

  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++){
    attacks[i].inUse = false;
  }

  removeDeadPlayerUnits();
  removeDeadAIUnits();

  setGameMode(AITURN_MODE);

  //No units so game over
  if(getNextPlayerBackUnit(0) == NULL_ID && getNextPlayerFrontUnit(0) == NULL_ID) {
    setGameMode(GAMEOVER_MODE);
    return;
  }

  player.turn++;
  haveDrawnThisTurn = false;
  player.gold += player.workersGold * GOLD_PER_WORKER;

}

int damagePlayerFrontUnit(int index, int qty) {
  if(index == NULL_ID) {
    return 0;
  }

  player.frontRow[index].hp -= qty;

  if(player.frontRow[index].unitType == NULL) {
    return 0;
  }

  return player.frontRow[index].unitType->attack;
}

int damagePlayerBackUnit(int index, int qty) {
  if(index == NULL_ID) {
    return 0;
  }

  player.backRow[index].hp -= qty;

  if(player.backRow[index].unitType == NULL) {
    return 0;
  }

  return player.backRow[index].unitType->attack;
}

int getNextPlayerBackUnit(int index) {

  CheckIfAllCombatAssigned();
  if(backUnitCount <= 0) {
    return NULL_ID;
  }

  int count = index % backUnitCount;

  for(int i = 0; i < MAX_UNITS_PER_ROW; i++) {
    if(player.backRow[i].unitType != NULL) {

      if(count <= 0) {
        return i;
      }

      count--;
    }
  }

  return NULL_ID;
}

int getNextPlayerFrontUnit(int index){

  CheckIfAllCombatAssigned();
  if(frontUnitCount <= 0) {
    return NULL_ID;
  }

  int count = index % frontUnitCount;

  TraceLog(LOG_WARNING, "Count %d", count);

  for(int i = 0; i < MAX_UNITS_PER_ROW; i++) {
    if(player.frontRow[i].unitType != NULL) {
      if(count <= 0) {
        return i;
      }

      count--;
    }
  }

  return NULL_ID;
}

bool canPlayerTargetBackRow() {
  return canTargetBackRow;
}

bool canDraw() {

  if(freeHandPosition() == NULL_ID) {
    return false;
  }
  
  return !haveDrawnThisTurn;
}

void DrawCard(){
  if(haveDrawnThisTurn) {
    return;
  }

  haveDrawnThisTurn = true;

  int index = freeHandPosition();

  player.hand[index] = drawCardFromDeck();
}

bool canCastCard(int index) {
  if(player.hand[index] == NULL) {
    return false;
  }

  return true;
}

void castCard(int index) {

  if(!canCastCard(index)) {
    return;
  }

  CardInfo* card = player.hand[index];

  if(player.gold < card->costGold) {
    return;
  }

  player.gold -= card->costGold;

  if(card->type == WORKER_CARD) {
    player.workersGold++;
    player.hand[index] = NULL;
  }

  if(card->type == UNIT_CARD) {
    UnitInstance unit = makeUnitInstance(card->unit);

    if(unit.unitType->front) {
      for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
        if(player.frontRow[i].unitType == NULL) {
          player.frontRow[i] = unit;

          player.hand[index] = NULL;
          return;
        }
      }
    }else{
      for(int i = 0; i < MAX_UNITS_PER_ROW; i++){
        if(player.backRow[i].unitType == NULL) {
          player.backRow[i] = unit;

          player.hand[index] = NULL;
          return;
        }
      }
    }
  }
}

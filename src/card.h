#ifndef __CARD_H_
#define __CARD_H_
#include "raylib.h"

typedef enum {
  UNIT_CARD = 0,
  WORKER_CARD = 1,

} CardType;

typedef enum {
  PIKE_MAN = 0,
  ARCHER = 1,
  KNIGHT = 2,
  MAGE = 3,
  GOBLIN_ARCHER = 4,
  ORC = 5,
  SKELLETON_KNIGHT = 6,
  EVIL_MAGE = 7,
} UnitType;

typedef struct {
  char* name;
  Texture2D image;
  CardType type;
  int costGold;
  char* text[4];
  int index;
  UnitType unit;

} CardInfo;

typedef struct {
  int cardId;
  Texture2D image;
  int maxHP;
  int attack;
  int rngAttack;
  int index;
  bool front;
} UnitInfo;

typedef struct {
  UnitInfo* unitType;
  int hp;
} UnitInstance;

void initCards();
CardInfo* getCard(int id); 
CardInfo* getPreviewCard();
void selectPreviewCard(int id);

UnitInstance makeUnitInstance(UnitType id);

CardInfo* drawCardFromDeck();

#endif

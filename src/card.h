#ifndef __CARD_H_
#define __CARD_H_
#include "raylib.h"

typedef enum {
  UNIT_CARD = 0,
  AIUNIT_CARD = 1,
  CURSE_CARD = 2,
  BLESS_CARD = 3,
  BUILDING_CARD = 4,
  ACTION_CARD = 5

} CardType;

typedef struct {
  char* name;
  Texture2D image;
  CardType type;
  int costGold;
  int costWood;
  int costIron;
  char* text[5];
} CardInfo;

void initCards();
CardInfo* getCard(int id); 
#endif

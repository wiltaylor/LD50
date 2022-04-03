#include "card.h"
#include <stdio.h>
#include "constants.h"

CardInfo cards[2];
UnitInfo units[1];
int previewCard = -1;


void initCards() {
  cards[0].name = "Call To Arms";
  cards[0].text[0] = "Call a Peasant into service as";
  cards[0].text[1] = "either a Pikeman or a Worker!";
  cards[0].text[2] = "";
  cards[0].text[3] = "";
  cards[0].text[4] = "";
  cards[0].image = LoadTexture("src/resource/unknown_card_big.png");
  cards[0].type = UNIT_CARD;
  cards[0].costWood = 0;
  cards[0].costIron = 0;
  cards[0].costGold = 0;
  cards[0].index = 0;

  cards[1].name = "Call To Arms v2";
  cards[1].text[0] = "Call a Peasant into service as";
  cards[1].text[1] = "either a Pikeman or a Worker! woo";
  cards[1].text[2] = "";
  cards[1].text[3] = "";
  cards[1].text[4] = "";
  cards[1].image = LoadTexture("src/resource/unknown_card_big.png");
  cards[1].type = UNIT_CARD;
  cards[1].costWood = 0;
  cards[1].costIron = 0;
  cards[1].costGold = 0;
  cards[1].index = 1;

  units[0].cardId = 0;
  units[0].image = LoadTexture("src/resource/unknown_unit_big.png");
  units[0].maxHP = 2;
  units[0].attack = 1;
  units[0].rngAttack = 0;
  units[0].index = 0;
}

CardInfo* getCard(int id) {
  return &cards[id];
}

UnitInfo* getUnit(int id) {
  if(id == -1) {
    return NULL;
  }

  return &units[id];
}

CardInfo* getPreviewCard() {
  if(previewCard == NULL_ID) {
    return NULL;
  }

  return &cards[previewCard];
}

void selectPreviewCard(int id) {
  previewCard = id;
}

UnitInstance makeUnitInstance(int id){
  UnitInfo* unit = getUnit(id);

  int hp = 0;

  if(unit!= NULL){
    hp = unit->maxHP;
  }

  UnitInstance result = {
    unit,
    hp
  };

  return result;
}

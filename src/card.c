#include "card.h"
#include <stdio.h>
#include "constants.h"

CardInfo cards[9];
UnitInfo units[8];
int previewCard = -1;


void initCards() {
  cards[0].name = "Pikeman";
  cards[0].text[0] = "Call a Peasant into service as";
  cards[0].text[1] = "either a Pikeman or a Worker!";
  cards[0].text[2] = "Atk: 2 Hp: 5";
  cards[0].text[3] = "cost: 5g";
  cards[0].image = LoadTexture("src/resource/pikeman_card_big.png");
  cards[0].type = UNIT_CARD;
  cards[0].costGold = 5;
  cards[0].index = 0;
  cards[0].unit = PIKE_MAN;

  cards[1].name = "Pesant";
  cards[1].text[0] = "Call a Peasant into service as";
  cards[1].text[1] = "to work on your local gold mine.";
  cards[1].text[2] = "";
  cards[1].text[3] = "";
  cards[1].image = LoadTexture("src/resource/pesant_card_big.png");
  cards[1].type = WORKER_CARD;
  cards[1].costGold = 0;
  cards[1].index = 1;
  cards[1].unit = PIKE_MAN;

  cards[2].name = "Archer";
  cards[2].text[0] = "Calls archer to service";
  cards[2].text[1] = "Ranged Unit.";
  cards[2].text[2] = "Rng-Atk: 3 Hp: 3";
  cards[2].text[3] = "cost: 5g";
  cards[2].image = LoadTexture("src/resource/archer_card_big.png");
  cards[2].type = UNIT_CARD;
  cards[2].costGold = 10;
  cards[2].index = 0;
  cards[2].unit = ARCHER;

  cards[3].name = "Knight";
  cards[3].text[0] = "Calls knight to service.";
  cards[3].text[1] = "Heavy melee unit.";
  cards[3].text[2] = "Atk: 8 Hp: 10";
  cards[3].text[3] = "cost: 20g";
  cards[3].image = LoadTexture("src/resource/knight_card_big.png");
  cards[3].type = UNIT_CARD;
  cards[3].costGold = 20;
  cards[3].index = 0;
  cards[3].unit = KNIGHT;

  cards[4].name = "Mage";
  cards[4].text[0] = "Calls Mage to service.";
  cards[4].text[1] = "Heavy damage Ranged unit.";
  cards[4].text[2] = "Rng-Atk: 10 Hp: 3";
  cards[4].text[3] = "cost: 100g";
  cards[4].image = LoadTexture("src/resource/mage_card_big.png");
  cards[4].type = UNIT_CARD;
  cards[4].costGold = 100;
  cards[4].index = 0;
  cards[4].unit = MAGE;

  cards[5].name = "Goblin Archer";
  cards[5].text[0] = "Weak but annoying";
  cards[5].text[1] = "Ranged Unit";
  cards[5].text[2] = "";
  cards[5].text[3] = "Atk: 1 Hp: 2";
  cards[5].image = LoadTexture("src/resource/goblin_card_big.png");
  cards[5].type = UNIT_CARD;
  cards[5].costGold = 5;
  cards[5].index = 0;
  cards[5].unit = GOBLIN_ARCHER;

  cards[6].name = "Orc";
  cards[6].text[0] = "Easy melee unit";
  cards[6].text[1] = "";
  cards[6].text[2] = "";
  cards[6].text[3] = "Atk: 3 Hp: 5";
  cards[6].image = LoadTexture("src/resource/orc_card_big.png");
  cards[6].type = UNIT_CARD;
  cards[6].costGold = 5;
  cards[6].index = 0;
  cards[6].unit = ORC;

  cards[7].name = "Skelleton Knight";
  cards[7].text[0] = "Hard melee unit";
  cards[7].text[1] = "";
  cards[7].text[2] = "";
  cards[7].text[3] = "Atk: 5 Hp: 20";
  cards[7].image = LoadTexture("src/resource/skelleton_card_big.png");
  cards[7].type = UNIT_CARD;
  cards[7].costGold = 5;
  cards[7].index = 0;
  cards[7].unit = SKELLETON_KNIGHT;

  cards[8].name = "Dark Mage";
  cards[8].text[0] = "Hard ranged Unit";
  cards[8].text[1] = "";
  cards[8].text[2] = "";
  cards[8].text[3] = "Atk: 20 Hp: 1";
  cards[8].image = LoadTexture("src/resource/mage_evil_card_big.png");
  cards[8].type = UNIT_CARD;
  cards[8].costGold = 5;
  cards[8].index = 0;
  cards[8].unit = EVIL_MAGE;

  //Pike Man
  units[0].cardId = 0;
  units[0].image = LoadTexture("src/resource/pike_unit_big.png");
  units[0].maxHP = 5;
  units[0].attack = 2;
  units[0].rngAttack = 0;
  units[0].index = 0;
  units[0].front = true;

  //Archer
  units[1].cardId = 2;
  units[1].image = LoadTexture("src/resource/archer_unit_big.png");
  units[1].maxHP = 3;
  units[1].attack = 1;
  units[1].rngAttack = 3;
  units[1].index = 0;
  units[1].front = false;

  //Knight
  units[2].cardId = 3;
  units[2].image = LoadTexture("src/resource/knight_unit_big.png");
  units[2].maxHP = 10;
  units[2].attack = 8;
  units[2].rngAttack = 0;
  units[2].index = 0;
  units[2].front = true;

  //Mage
  units[3].cardId = 4;
  units[3].image = LoadTexture("src/resource/mage_unit_big.png");
  units[3].maxHP = 3;
  units[3].attack = 1;
  units[3].rngAttack = 10;
  units[3].index = 0;
  units[3].front = false;

  //Goblin Archer
  units[4].cardId = 5;
  units[4].image = LoadTexture("src/resource/goblin_unit_big.png");
  units[4].maxHP = 2;
  units[4].attack = 1;
  units[4].rngAttack = 1;
  units[4].index = 0;
  units[4].front = false;

  //Orc
  units[5].cardId = 6;
  units[5].image = LoadTexture("src/resource/orc_unit_big.png");
  units[5].maxHP = 5;
  units[5].attack = 3;
  units[5].rngAttack = 0;
  units[5].index = 0;
  units[5].front = true;

  //Skelleton Knight
  units[6].cardId = 7;
  units[6].image = LoadTexture("src/resource/skelleton_unit_big.png");
  units[6].maxHP = 20;
  units[6].attack = 5;
  units[6].rngAttack = 0;
  units[6].index = 0;
  units[6].front = true;

  //Evil Mage
  units[7].cardId = 8;
  units[7].image = LoadTexture("src/resource/mage_evil_unit_big.png");
  units[7].maxHP = 1;
  units[7].attack = 1;
  units[7].rngAttack = 10;
  units[7].index = 0;
  units[7].front = false;
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

UnitInstance makeUnitInstance(UnitType id){
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

CardInfo* drawCardFromDeck(){
  int number = GetRandomValue(0, 32);

  //Pikeman
  if(number < 10) {
    return &cards[0];
  }

  if(number < 20) {
    return &cards[1];
  }

  if(number < 25) {
    return &cards[2];
  }

  if(number < 30) {
    return &cards[3];
  }

  if(number < 32) {
    return &cards[4];
  }

  return &cards[0];

}



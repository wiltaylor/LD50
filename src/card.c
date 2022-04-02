#include "card.h"

CardInfo cards[1];


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
}

CardInfo* getCard(int id) {
  return &cards[id];
}

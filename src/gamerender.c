#include "gamerender.h"
#include "card.h"
#include "constants.h"
#include "player.h"
#include <stdio.h>

static const int cardPadding = 10;
static const int cardTextPadding = 15;
static const int cardPaddingTop = 20;
static const int largeUnitSize = 64;
static const int smallUnitSize = 32;
static const int unitRowButtonSize = 16;

const int aiHeight =
    largeUnitSize * 2 +
    cardPadding *
        7; // 7 because its 2 on each line and spaces between lines too.

const Rectangle aiArea = {0, 0, SCREEN_WIDTH, aiHeight};
const Rectangle playerArea = {0, aiHeight, SCREEN_WIDTH,
                              SCREEN_HEIGHT - aiHeight};
const Rectangle darkWizard = {SCREEN_WIDTH - 256, 0, 256, aiHeight};
const Rectangle endTurn = {SCREEN_WIDTH - 256, aiHeight - 32, 256, 32};
const Rectangle cardPreview = {cardPadding, aiHeight + cardPadding, 256, 320};


void DrawUnitGrid(int x, int y, int rows, int cols, int cardSize,
                   bool scrollable) {
  int width = cols * cardSize + cols * cardPadding + cardPadding;

  if (scrollable) {
    width += cardPadding + 16;
  }

  int height = rows * cardSize + cardPadding * rows + cardPadding;

  DrawRectangle(x, y, width, height, BLACK);

  if (scrollable) {
    DrawRectangle(x + width - unitRowButtonSize - cardPadding, y + cardPadding,
                  unitRowButtonSize, unitRowButtonSize, RED);
    DrawRectangle(x + width - unitRowButtonSize - cardPadding,
                  y + height - cardPadding - unitRowButtonSize,
                  unitRowButtonSize, unitRowButtonSize, RED);
  }

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      DrawRectangle(x + cardPadding + (col * cardSize) + (col * cardPadding),
                    y + cardPadding + (row * cardSize) + (row * cardPadding),
                    cardSize, cardSize, WHITE);
    }
  }
}

void DrawCardPreview(CardInfo *card) {
  Rectangle image = {cardPreview.x + cardPadding,
                     cardPreview.y + cardTextPadding, 220, 236};

  Rectangle text = {
      cardPreview.x + cardPadding, cardPreview.y + image.height + cardPadding,
      cardPreview.width - 2 * cardPadding,
      cardPreview.height - image.height - (2 * cardPadding) - cardTextPadding};

  int lineHeight = 12;

  // Drawing care preview
  DrawRectangleRec(cardPreview, ORANGE);

  DrawTexture(card->image, image.x, image.y, WHITE);
  DrawRectangleRec(text, WHITE);

  DrawText(card->name, cardPreview.x + cardPadding, cardPreview.y, 12, BLACK);

  for (int i = 0; i < 5; i++) {
    DrawText(card->text[i], text.x + 5, text.y + 5 + (lineHeight * i), 12,
             BLACK);
  }
}

void DrawDarkWizard() {
  DrawRectangleRec(darkWizard, PURPLE);

  DrawText("Evil Wizard - Level 100", darkWizard.x + cardTextPadding,
           darkWizard.y + cardTextPadding, 12, BLACK);

  DrawText("Survived Turns: 56", darkWizard.x + cardTextPadding,
           darkWizard.y + cardTextPadding + 12, 12, BLACK);

  DrawRectangleRec(endTurn, DARKGRAY);

  DrawText("End Turn", endTurn.x + cardPadding, endTurn.y + cardPadding, 12,
           BLACK);
}

void DrawAIUnits() {
  int backRowX = aiArea.x + cardPadding;
  int backRowY = aiArea.y + cardPadding;
  DrawUnitGrid(backRowX, backRowY, 1, 13, largeUnitSize, true);

  int frontRowX = aiArea.x + cardPadding;
  int frontRowY =
      aiArea.y + (largeUnitSize + cardPadding * 2) + cardPadding * 2;
  DrawUnitGrid(frontRowX, frontRowY, 1, 13, largeUnitSize, true);
}

void DrawPlayerUnits() {
  int backRowX = cardPreview.x + cardPadding + cardPreview.width;
  int backRowY = playerArea.y + cardPadding;
  DrawUnitGrid(backRowX, backRowY, 1, 13, largeUnitSize, true);

  int frontRowX = backRowX;
  int frontRowY =
      playerArea.y + (largeUnitSize + cardPadding * 2) + cardPadding * 2;
  DrawUnitGrid(frontRowX, frontRowY, 1, 13, largeUnitSize, true);
}

int bottomOfPlayerUnitRow(){

  int playerUnitRowHeight = playerArea.y + (largeUnitSize + cardPadding * 4) + cardPadding * 4;

  return playerUnitRowHeight + smallUnitSize + cardPadding * 2;
}

void DrawResourceArea() {

  int playerUnitRowHeight = playerArea.y + (largeUnitSize + cardPadding * 4) + cardPadding * 4;


  Rectangle area = {
    cardPreview.x + cardPreview.width + cardPadding,
    bottomOfPlayerUnitRow(),
    (SCREEN_WIDTH - cardPreview.width - (4 * cardPadding)) / 2 - 65,
    138
  };

  int goldx = area.x + cardPadding;
  int goldy = area.y + cardPadding;
  int goldText = goldx + 16 + cardPadding;

  int woodx = goldx;
  int woody = goldy + 16 + cardPadding;
  int woodText = woodx + 16 + cardPadding;

  int ironx = goldx;
  int irony = woody + 16 + cardPadding;
  int ironText = ironx + 16 + cardPadding;

  int foodx = goldx;
  int foody = irony + 16 + cardPadding;
  int foodText = foodx + 16 + cardPadding;

  int faithx = goldx;
  int faithy = foody + 16 + cardPadding;
  int faithText = faithx + 16 + cardPadding;

  DrawRectangleRec(area, WHITE);

  DrawRectangle(goldx, goldy, 16, 16, YELLOW);
  DrawText("Gold: 1000 (+7 Per Turn)", goldText, goldy, 12, BLACK);

  DrawRectangle(woodx, woody, 16, 16, BROWN);
  DrawText("Wood: 1000 (+7 Per Turn)", woodText, woody, 12, BLACK);

  DrawRectangle(ironx, irony, 16, 16, DARKGRAY);
  DrawText("Iron: 1000 (+7 Per Turn)", ironText, irony, 12, BLACK);

  DrawRectangle(foodx, foody, 16, 16, RED);
  DrawText("Food: 1000 (+7 Per Turn) (Using 3 Per Turn)", foodText, foody, 12,
           BLACK);

  DrawRectangle(faithx, faithy, 16, 16, PURPLE);
  DrawText("Faith: 1000 (+7 Per Turn)", faithText, faithy, 12, BLACK);
}

void DrawBuildingArea() {
  
  int resourceWidth =  (SCREEN_WIDTH - cardPreview.width - (4 * cardPadding)) / 2 - 65;
  int resourceX = cardPreview.x + cardPreview.width + cardPadding;
  int buildingAreaX = resourceX+ resourceWidth + cardPadding;
  int buildingAreaY = bottomOfPlayerUnitRow();
  int buildingAreaWidth = cardPadding * 5 + smallUnitSize * 5 + 2 * cardPadding;

  DrawUnitGrid(buildingAreaX, buildingAreaY, 3, 5, smallUnitSize, false);
  DrawUnitGrid(buildingAreaX + buildingAreaWidth, buildingAreaY, 3, 7, smallUnitSize, true);
}

void DrawHand() {
 int x = playerArea.x + cardPreview.x + cardPreview.width + (cardPadding * 2);
  int y = playerArea.y + playerArea.height - 128;

  const int handWidth = 128;
  const int handHeight = 128;

  const int imageHeight = 220;
  const int imageWidth = 236;

  for (int i = 0; i < 7; i++) {
    CardInfo* card = getHand(i);

    if(card == NULL) {
      continue;
    }

    DrawRectangle(x+ (handWidth * i) + (cardPadding * i), y, handWidth,
                  handHeight, YELLOW);
    Vector2 vec = {x+ (handWidth * i) + (cardPadding * i) +
                       (cardPadding / 2.0f),
                   y + (cardPaddingTop / 2.0f)};
    DrawText(card->name,
             x + (handWidth * i) + (cardPadding * i) + (cardPadding / 2.0f),
             y , 6, BLACK);
    DrawTextureEx(card->image, vec, 0, 0.5f, WHITE);
  }
}

void drawDecks(){

  Rectangle faith = { 
    playerArea.x + cardPadding,
    cardPreview.y + cardPreview.height + cardPadding,
    122,
    170
  };

  Rectangle main = {
    faith.x + faith.width + cardPadding,
    faith.y,
    122,
    170
  };

  DrawRectangleRec(faith, BLUE);
  DrawRectangleRec(main, BLUE);

}

void renderGame() {
  CardInfo *card = getCard(0);

  // Clear Player Areas
  DrawRectangle(aiArea.x, aiArea.y, aiArea.width, aiArea.height, RED);
  DrawRectangle(playerArea.x, playerArea.y, playerArea.width, playerArea.height,
                GREEN);

  DrawAIUnits();
  DrawPlayerUnits();

  DrawDarkWizard();
  DrawCardPreview(card);

  DrawResourceArea();
  DrawBuildingArea();

  DrawHand();
  drawDecks();
}

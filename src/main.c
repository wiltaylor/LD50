#include "gamemode.h"
#include "raylib.h"
#include "card.h"

static GameMode gameMode = MAINGAME_MODE;

const int screenWidth = 1280;
const int screenHeight = 720;

const int cardPadding = 10;
const int cardPaddingTop = 20;
const int unitCardSize = 64;
const int cardsPerRow = 13;
const int unitRowButtonSize = 16;
const int unitRowHeight = unitCardSize + 2 * cardPadding;
const int cardTextPadding = 15;

Texture2D unknownCard;

void mainMenu_Update() {
  if (IsKeyDown(KEY_ESCAPE)) {
  }
}

void mainMenu_Draw() {
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}

Vector2 UnitGridSize(int x, int y, int rows, int cols, int cardSize, bool scrollable) {
  int width = cols * cardSize + cols * cardPadding + cardPadding;

  if(scrollable) {
    width += cardPadding + 16;
  }

  int height = rows * cardSize + cardPadding * rows + cardPadding;
  Vector2 result = {width, height};
  return  result;
}

void DrawUnitGrid(int x, int y, int rows, int cols, int cardSize,
                  bool scrollable) {
  int width = cols * cardSize + cols * cardPadding + cardPadding;

  if(scrollable) {
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
                    y + cardPadding + (row * cardSize) + (row * cardPadding), cardSize, cardSize,
                    WHITE);
    }
  }
}

void DrawUnitRow(int x, int y, int cards) {
  DrawUnitGrid(x, y, 1, cards, unitCardSize, true);
}

void DrawResourceArea(int x, int y, int width, int height) {

  int goldx = x + cardPadding;
  int goldy = y + cardPadding;
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

  DrawRectangle(x, y, width, height, WHITE);

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

void DrawBuildingArea(int x, int y) {

  DrawUnitGrid(x, y, 3, 5, 32, false);
}

void DrawEffectsArea(int x, int y) {
  DrawUnitGrid(x, y, 3, 7, 32, true);
}

void DrawCardPreview(int x, int y, CardInfo* card) {
  int width = 256;
  int height = 320;

  int imageX = x + cardPadding;
  int imageY = y + cardTextPadding;
  int imageHeight = 220;
  int imageWidth = 236;

  int textX = x + cardPadding;
  int textY = y + imageHeight + cardPadding + cardTextPadding;
  int textWidth = imageWidth;
  int textHeight = height -imageHeight - (2 * cardPadding) - cardTextPadding;
  int lineHeight = 12;
  
  // Drawing care preview
  DrawRectangle(x, y, width, height, ORANGE);

  DrawTexture(card->image, imageX, imageY, WHITE);
  DrawRectangle(textX, textY, textWidth, textHeight, WHITE);

  DrawText(card->name, x + cardPadding, y, 12, BLACK);

  for (int i = 0; i < 5; i++) {
    DrawText(card->text[i], textX + 5,
             textY + 5 + (lineHeight * i), 12, BLACK);
  }
}

void DrawHand(int x, int y) {
  const int handWidth = 128;
  const int handHeight = 128;

  const int imageHeight = 220;
  const int imageWidth = 236;

  for (int i = 0; i < 7; i++) {
    DrawRectangle(x+ (handWidth * i) + (cardPadding * i), y, handWidth,
                  handHeight, YELLOW);
    Vector2 vec = {x+ (handWidth * i) + (cardPadding * i) +
                       (cardPadding / 2.0f),
                   y + (cardPaddingTop / 2.0f)};
    DrawText("Card title",
             x + (handWidth * i) + (cardPadding * i) + (cardPadding / 2.0f),
             y , 6, BLACK);
    DrawTextureEx(unknownCard, vec, 0, 0.5f, WHITE);
  }
}

void mainScreen_Draw() {
  CardInfo* card = getCard(0);

  int aiAreaX = 0;
  int aiAreaY = 0;
  int aiAreaWidth = screenWidth;
  int aiAreaHeight = unitRowHeight * 2 + cardPadding * 3;

  int aiDarkWizardX = aiAreaWidth - 256;
  int aiDarkWizardY = aiAreaY;
  int aiDarkWizardWidth = 256;
  int aiDarkWizardHeight = aiAreaHeight;

  int endTurnX = aiDarkWizardX;
  int endTurnY = aiDarkWizardY + aiDarkWizardHeight - 32;
  int endTurnWidth = aiDarkWizardWidth;
  int endTurnHeight = 32;

  int aiBackRowX = aiAreaX + cardPadding;
  int aiBackRowY = aiAreaY + cardPadding;

  int aiFrontRowX = aiBackRowX;
  int aiFrontRowY = aiBackRowY + cardPadding + unitRowHeight;

  int playerAreaX = 0;
  int playerAreaY = aiAreaY + aiAreaHeight;
  int playerAreaWidth = screenWidth;
  int playerAreaHeight = screenHeight - aiAreaHeight;

  int cardPreviewX = playerAreaX + cardPadding;
  int cardPreviewY = playerAreaY + cardPadding;
  int cardPreviewWidth = 256;
  int cardPreviewHeight = 320;

  int titleX = cardPreviewX + cardPadding;
  int titleY = cardPreviewY + 5;

  int cardImageX = cardPreviewX + cardPadding;
  int cardImageY = cardPreviewY + cardPaddingTop;
  int cardImageWidth = cardPreviewWidth - (cardPadding * 2);
  int cardImageHeight =
      cardPreviewHeight / 2 - ((cardPadding * 3) + cardPaddingTop);

  int cardTextX = cardPreviewX + cardPadding;
  int cardTextY = cardImageY + cardImageHeight + cardPadding;
  int cardTextWidth = cardPreviewWidth - (cardPadding * 2);
  int cardTextHeight = cardPreviewHeight - cardImageHeight - (4 * cardPadding);

  int cardTextLineHeight = 12;

  int deckFaithX = playerAreaX + cardPadding;
  int deckFaithY = cardPreviewY + cardPreviewHeight + cardPadding;
  int deckFaithWidth = 122;
  int deckFaithHeight = 170;

  int deckMainX = deckFaithX + deckFaithWidth + cardPadding;
  int deckMainY = deckFaithY;
  int deckMainWidth = deckFaithWidth;
  int deckMainHeight = deckFaithHeight;

  int handX = playerAreaX + cardPreviewX + cardPreviewWidth + (cardPadding * 2);
  int handY = playerAreaY + playerAreaHeight - 128;
  int handWidth = 128;
  int handHeight = 128;

  int playerFrontRowX = cardPreviewX + cardPreviewWidth + cardPadding;
  int playerFrontRowY = playerAreaY + cardPadding;

  int playerBackRowX = playerFrontRowX;
  int playerBackRowY = playerFrontRowY + unitRowHeight + cardPadding;

  int resourceAreaX = playerFrontRowX;
  int resourceAreaY = playerBackRowY + unitRowHeight + cardPadding;
  int resourceAreaWidth =
      (screenWidth - cardPreviewWidth - (4 * cardPadding)) / 2 - 65;
  int resourceAreaHeight = 150;

  int buildingAreaX = resourceAreaX + resourceAreaWidth + cardPadding;
  int buildingAreaY = resourceAreaY;
  Vector2 buildingSize = UnitGridSize(buildingAreaX, buildingAreaY, 2, 5, 32, false);

  int effectsAreaX = buildingAreaX + buildingSize.x + cardPadding;
  int effectsAreaY = buildingAreaY;

  // Player Areas
  DrawRectangle(aiAreaX, aiAreaY, aiAreaWidth, aiAreaHeight, RED); // Enemy
  DrawRectangle(playerAreaX, playerAreaY, playerAreaWidth, playerAreaHeight,
                GREEN); // Player Area

  DrawRectangle(aiDarkWizardX, aiDarkWizardY, aiDarkWizardWidth,
                aiDarkWizardHeight, PURPLE);
  DrawText("Evil Wizard - Level 100", aiDarkWizardX + cardTextPadding,
           aiDarkWizardY + cardTextPadding, 12, BLACK);
  DrawText("Survived Turns: 56", aiDarkWizardX + cardTextPadding,
           aiDarkWizardY + cardTextPadding + cardTextLineHeight, 12, BLACK);

  DrawRectangle(endTurnX, endTurnY, endTurnWidth, endTurnHeight, DARKGRAY);
  DrawText("End Turn", endTurnX + cardPadding, endTurnY + cardPadding, 12,
           BLACK);

  DrawUnitRow(aiBackRowX, aiBackRowY, 13);
  DrawUnitRow(aiFrontRowX, aiFrontRowY, 13);
  DrawUnitRow(playerFrontRowX, playerFrontRowY, 13);
  DrawUnitRow(playerBackRowX, playerBackRowY, 13);

  // Resource Area
  DrawResourceArea(resourceAreaX, resourceAreaY, resourceAreaWidth,
                   resourceAreaHeight);
  DrawBuildingArea(buildingAreaX, buildingAreaY);

  DrawEffectsArea(effectsAreaX, effectsAreaY);

  DrawCardPreview(cardPreviewX, cardPreviewY, card);

  // Drawing faith and main decks
  DrawRectangle(deckFaithX, deckFaithY, deckFaithWidth, deckFaithHeight, BLUE);
  DrawRectangle(deckMainX, deckMainY, deckMainWidth, deckMainHeight, BLUE);

  // Draw Hand
  DrawHand(handX, handY);
}

int main(void) {

  InitWindow(screenWidth, screenHeight, "LD50");

  SetExitKey(KEY_NULL);

  Image img = LoadImage("src/resource/unknown_card_big.png");
  unknownCard = LoadTextureFromImage(img);
  UnloadImage(img);

  initCards();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    switch (gameMode) {
    case MAINMENU_MODE:
      mainMenu_Update();
      break;
    default:
      break;
    }

    if (IsKeyDown(KEY_F12)) {
      CloseWindow();
      break;
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);

    switch (gameMode) {
    case MAINMENU_MODE:
      mainMenu_Draw();
      break;
    case MAINGAME_MODE:
      mainScreen_Draw();
      break;
    default:
      break;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

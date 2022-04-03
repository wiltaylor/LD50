#include "gamerender.h"
#include "card.h"
#include "constants.h"
#include "player.h"
#include <stdio.h>
#include "ai.h"
#include "gamemode.h"

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
const Rectangle darkWizard = {SCREEN_WIDTH - 256 - CARD_PADDING * 3, CARD_PADDING, 256, aiHeight - CARD_PADDING * 2};
const Rectangle endTurn = {SCREEN_WIDTH - 256 - CARD_PADDING * 2, aiHeight - 32 - CARD_PADDING * 2, 256 - CARD_PADDING * 2, 32};
const Rectangle cardPreview = {cardPadding, aiHeight + cardPadding, 256, 320};

void DrawUnitGrid(int x, int y, int rows, int cols, int cardSize,
                  bool scrollable, UnitInstance* units, int count, bool selectable, char* title) {
  int width = cols * cardSize + cols * cardPadding + cardPadding;

  if (scrollable) {
    width += cardPadding + 16;
  }

  int height = rows * cardSize + cardPadding * rows + cardPadding;
  int textWidth = MeasureText(title, 18);
  int textX = x + (width / 2) - (textWidth / 2);
  int textY = y + (height / 2) - 9;

  Rectangle rec = {x, y, width, height};

  DrawRectangleRounded(rec, 0.05f, 0, Fade(BLACK, 0.2f));
  DrawText(title, textX, textY, 18, WHITE);

  if (scrollable) {
    DrawRectangle(x + width - unitRowButtonSize - cardPadding, y + cardPadding,
                  unitRowButtonSize, unitRowButtonSize, RED);
    DrawRectangle(x + width - unitRowButtonSize - cardPadding,
                  y + height - cardPadding - unitRowButtonSize,
                  unitRowButtonSize, unitRowButtonSize, RED);
  }

  int index = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if(index < count) {
        Rectangle unitRect = {
          x + cardPadding + (col * cardSize) + (col * cardPadding),
          y + cardPadding + (row * cardSize) + (row * cardPadding),
          cardSize,
          cardSize
        };

        if(units[index].unitType == NULL) {
          index++;
          continue;
        }

        DrawRectangleRec(unitRect, WHITE);
        DrawTexture(units[index].unitType->image, unitRect.x, unitRect.y, selectable ? YELLOW : WHITE);

        float currentHP = units[index].hp;

        float hpPercent = currentHP / units[index].unitType->maxHP;
        float widthPercent = hpPercent * unitRect.width;

        DrawRectangle(unitRect.x, unitRect.y, unitRect.width, 10, RED);
        DrawRectangle(unitRect.x, unitRect.y, widthPercent, 10, GREEN);

      }
      index++;
    }
  }
}

void DrawCardPreview() {
  CardInfo* card = getPreviewCard();

  Rectangle image = {cardPreview.x + cardPadding,
                     cardPreview.y + cardTextPadding, 220, 236};

  Rectangle text = {
      cardPreview.x + cardPadding, cardPreview.y + image.height + cardPadding,
      cardPreview.width - 2 * cardPadding,
      cardPreview.height - image.height - (1 * cardPadding) - cardTextPadding};

  int lineHeight = 12;

  // Drawing card preview
  DrawRectangleRounded(cardPreview,0.05, 0, DARKGRAY);

  if(card == NULL) {
    return;
  }

  DrawTexture(card->image, image.x, image.y, WHITE);
  DrawRectangleRec(text, Fade(WHITE, 0.75f));

  DrawText(card->name, cardPreview.x + cardPadding, cardPreview.y, 12, RAYWHITE);

  for (int i = 0; i < 4; i++) {
    DrawText(card->text[i], text.x + 5, text.y + 5 + (lineHeight * i), 12,
             BLACK);
  }
}

void DrawDarkWizard() {
  DrawRectangleRounded(darkWizard, 0.05, 0, Fade(BLACK, 0.2f));

  DrawText(TextFormat("Evil Wizard - Level %d", getAILevel()), darkWizard.x + cardTextPadding,
           darkWizard.y + cardTextPadding, 12, RAYWHITE);

  DrawText(TextFormat("Survived Turns: %d", getTurnCount()), darkWizard.x + cardTextPadding,
           darkWizard.y + cardTextPadding + 12, 12, RAYWHITE);

  if(getGameMode() == MAINGAME_MODE){
    DrawRectangleRounded(endTurn, 0.05, 0, DARKGREEN);

    int txtLen = MeasureText("Attack & End Turn", 12);

    DrawText("Attack & End Turn", endTurn.x + endTurn.width / 2.0f - txtLen / 2.0f, endTurn.y + cardPadding, 12,
             RAYWHITE);
  }else{

    DrawRectangleRounded(endTurn, 0.05, 0, DARKGRAY);

    int txtLen = MeasureText("Evil Wizards Turn", 12);

    DrawText("Evil Wizards Turn", endTurn.x + endTurn.width / 2.0f - txtLen / 2.0f, endTurn.y + cardPadding, 12,
         GRAY);
  }
}

void DrawAIUnits() {
  SelectionMode mode = getCurrentSelectionMode();

  UnitInstance* firstFrontUnit = getAIUnitFront(0);
  UnitInstance* firstBackUnit = getAIUnitBack(0);

  int backRowX = aiArea.x + cardPadding;
  int backRowY = aiArea.y + cardPadding;
  DrawUnitGrid(backRowX, backRowY, 1, 13, largeUnitSize, false, firstBackUnit, MAX_UNITS_PER_ROW, mode == SELECT_RANGED_COMBAT || (mode == SELECT_COMBAT && canPlayerTargetBackRow()), "Enemy Back Row");


  int frontRowX = aiArea.x + cardPadding;
  int frontRowY =
      aiArea.y + (largeUnitSize + cardPadding * 2) + cardPadding * 2;
  DrawUnitGrid(frontRowX, frontRowY, 1, 13, largeUnitSize, false, firstFrontUnit, MAX_UNITS_PER_ROW, mode == SELECT_COMBAT || mode == SELECT_RANGED_COMBAT, "Enemy Front Row");
}

void DrawPlayerUnits() {
  UnitInstance* firstFrontUnit = getPlayerUnitFront(0);
  UnitInstance* firstBackUnit = getPlayerUnitBack(0);

  int frontRowX = cardPreview.x + cardPadding + cardPreview.width;
  int frontRowY = playerArea.y + cardPadding;
  DrawUnitGrid(frontRowX, frontRowY, 1, 13, largeUnitSize, false, firstFrontUnit, MAX_UNITS_PER_ROW, false, "Front Row");

  int backRowX = frontRowX;
  int backRowY =
      playerArea.y + (largeUnitSize + cardPadding * 2) + cardPadding * 2;
  DrawUnitGrid(backRowX, backRowY, 1, MAX_UNITS_PER_ROW, largeUnitSize, false, firstBackUnit, MAX_UNITS_PER_ROW, false, "Back Row");

}

int bottomOfPlayerUnitRow() {

  int playerUnitRowHeight =
      playerArea.y + (largeUnitSize + cardPadding * 4) + cardPadding * 4;

  return playerUnitRowHeight + smallUnitSize + cardPadding * 2;
}

void DrawResourceArea() {

  int playerUnitRowHeight =
      playerArea.y + (largeUnitSize + cardPadding * 4) + cardPadding * 4;

  Rectangle area = {
      cardPreview.x + cardPreview.width + cardPadding, bottomOfPlayerUnitRow(),
      (SCREEN_WIDTH - cardPreview.width - (4 * cardPadding)) / 2 - 65, 138};

  int goldx = area.x + cardPadding;
  int goldy = area.y + cardPadding;
  int goldText = goldx + 16 + cardPadding;

  DrawRectangleRounded(area, 0.05f, 0, Fade(BLACK, 0.2f));

  DrawRectangle(goldx, goldy, 16, 16, YELLOW);
  DrawText(TextFormat("Gold: %d (Workers: %d)", getPlayerGold(), getWorkersGold()), goldText, goldy, 12, WHITE);
}

void DrawBuildingArea() {

  int resourceWidth =
      (SCREEN_WIDTH - cardPreview.width - (4 * cardPadding)) / 2 - 65;
  int resourceX = cardPreview.x + cardPreview.width + cardPadding;
  int buildingAreaX = resourceX + resourceWidth + cardPadding;
  int buildingAreaY = bottomOfPlayerUnitRow();
  int buildingAreaWidth = cardPadding * 5 + smallUnitSize * 5 + 2 * cardPadding;

  DrawUnitGrid(buildingAreaX, buildingAreaY, 3, 5, smallUnitSize, false, NULL, 0, false, "Buildings");
  DrawUnitGrid(buildingAreaX + buildingAreaWidth, buildingAreaY, 3, 7,
               smallUnitSize, false, NULL, 0, false, "Curses and Blessings");
}

void DrawHand() {
  int x = playerArea.x + cardPreview.x + cardPreview.width + (cardPadding * 2);
  int y = playerArea.y + playerArea.height - 128;

  const int handWidth = 128;
  const int handHeight = 128;

  const int imageHeight = 220;
  const int imageWidth = 236;

  for (int i = 0; i < MAX_HAND_SIZE; i++) {
    bool canCast = canCastCard(i);
    CardInfo *card = getHand(i);

    if (card == NULL) {
      continue;
    }

    Rectangle rec = {x + (handWidth * i) + (cardPadding * i), 
      y, 
      handWidth,
      handHeight
    };

    DrawRectangleRounded(rec, 0.05f, 0, DARKGRAY);
    Vector2 vec = {x + (handWidth * i) + (cardPadding * i) +
                       (cardPadding / 2.0f),
                   y + (cardPaddingTop / 2.0f)};
    DrawText(card->name,
             x + (handWidth * i) + (cardPadding * i) + (cardPadding / 2.0f), y,
             6, RAYWHITE);
    DrawTextureEx(card->image, vec, 0, 0.5f, canCast ? WHITE : DARKGRAY);

  }
}

void DrawDecks() {

  if(!canDraw()){
    return;
  }

  Rectangle main = {playerArea.x + cardPadding,
                     cardPreview.y + cardPreview.height + cardPadding, 122,
                     170};

  DrawRectangleRounded(main, 0.05f, 0, DARKGRAY);
  DrawEllipse(main.x + main.width / 2.0f, main.y + main.height / 2.0f, 50, 70, Fade(BLUE, 0.2f));

  int textLength = MeasureText("Draw (5 Gold)", 16);

  DrawText("Draw (5 Gold)", main.x + main.width / 2.0f - textLength / 2.0f, main.y + main.height / 2.0f, 16, RAYWHITE);


}

void DrawCombatIndicators(){
  SelectionMode mode = getCurrentSelectionMode();

  Vector2 mousePos = {GetMouseX(), GetMouseY()};
  Vector2 combatStart = getCombatStartPoint();
  if(mode == SELECT_COMBAT || mode == SELECT_RANGED_COMBAT) {
    DrawLineEx(combatStart, mousePos, 1.0f, RED);
    DrawCircleV(combatStart, 5.0f, RED);
  }

  for(int i = 0; i < MAX_UNITS_PER_ROW * 2; i++) {
    AttackInfo* attack = getAttackInfo(i);
    AttackInfo* aiAttack = getAIAttackInfo(i);

    if(attack != NULL) {
      DrawLineEx(attack->attackerVector, attack->defenderVector, 2.0f, RED);
      DrawCircleV(attack->defenderVector, 5.0f, RED);
      DrawCircleV(attack->attackerVector, 5.0f, RED);
    }

    if(aiAttack != NULL) {
      DrawLineEx(aiAttack->attackerVector, aiAttack->defenderVector, 2.0f, DARKPURPLE);
      DrawCircleV(aiAttack->defenderVector, 5.0f, DARKPURPLE);
      DrawCircleV(aiAttack->attackerVector, 5.0f, DARKPURPLE);
    }
  }
}

void renderGame() {
  // Clear Player Areas
  DrawRectangle(aiArea.x, aiArea.y, aiArea.width, aiArea.height, GRAY);
  DrawRectangle(playerArea.x, playerArea.y, playerArea.width, playerArea.height,
                GRAY);

  DrawAIUnits();
  DrawPlayerUnits();

  DrawDarkWizard();
  DrawCardPreview();

  DrawResourceArea();

  DrawHand();
  DrawDecks();
  
  DrawCombatIndicators();
}

void renderGameOver(){

  const char* turnsText = TextFormat("You managed to survive for %d turns!", getTurnCount());

  int gameOverWidth = MeasureText("GAME OVER", 64);
  int turnsWidth = MeasureText(turnsText, 32);
  int continueText = MeasureText("Click to play again!", 32);
  

  DrawText("GAME OVER", SCREEN_WIDTH / 2.0f - gameOverWidth / 2.0f, 50, 64, RAYWHITE);
  DrawText(turnsText, SCREEN_WIDTH / 2.0f - turnsWidth / 2.0f, 200, 32, RAYWHITE);
  DrawText("Click to play again!", SCREEN_WIDTH / 2.0f - continueText / 2.0f, 250, 32, RAYWHITE);

}

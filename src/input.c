#include "input.h"
#include "raylib.h"
#include "constants.h"
#include "card.h"
#include "player.h"
#include <stdio.h>
#include "ai.h"

void checkGameInput() {
  Vector2 mousePos = { GetMouseX(), GetMouseY() };

  for(int i = 0; i < MAX_HAND_SIZE; i++) {
    Rectangle cardRec = {
      HAND_FIRST_CARD.x + HAND_FIRST_CARD.width * i + CARD_PADDING * i,
      HAND_FIRST_CARD.y,
      HAND_FIRST_CARD.width,
      HAND_FIRST_CARD.height
    };

    if(CheckCollisionPointRec(mousePos, cardRec)) {
      CardInfo* card = getHand(i);

      if(card != NULL) {
        selectPreviewCard(card->index);

        if(IsMouseButtonPressed(0)) {
          TraceLog(LOG_WARNING, "Pressed card");
        }
      }
    }
  }

  for(int i = 0; i < MAX_UNITS_PER_ROW; i++) {
    Rectangle playerFront = {
      PLAYER_FRONT_ROW_FIRST_UNIT.x + PLAYER_FRONT_ROW_FIRST_UNIT.width * i + CARD_PADDING * i + CARD_PADDING,
      PLAYER_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING,
      PLAYER_FRONT_ROW_FIRST_UNIT.width,
      PLAYER_FRONT_ROW_FIRST_UNIT.height
    };

    Rectangle playerBack = {
      PLAYER_BACK_ROW_FIRST_UNIT.x + PLAYER_BACK_ROW_FIRST_UNIT.width * i + CARD_PADDING * i + CARD_PADDING,
      PLAYER_BACK_ROW_FIRST_UNIT.y + CARD_PADDING,
      PLAYER_BACK_ROW_FIRST_UNIT.width,
      PLAYER_BACK_ROW_FIRST_UNIT.height
    };

    Rectangle aiFront = {
      AI_FRONT_ROW_FIRST_UNIT.x + AI_FRONT_ROW_FIRST_UNIT.width * i + CARD_PADDING * i + CARD_PADDING,
      AI_FRONT_ROW_FIRST_UNIT.y + CARD_PADDING,
      AI_FRONT_ROW_FIRST_UNIT.width,
      AI_FRONT_ROW_FIRST_UNIT.height
    };

    Rectangle aiBack = {
      AI_BACK_ROW_FIRST_UNIT.x + AI_BACK_ROW_FIRST_UNIT.width * i + CARD_PADDING * i + CARD_PADDING,
      AI_BACK_ROW_FIRST_UNIT.y + CARD_PADDING,
      AI_BACK_ROW_FIRST_UNIT.width,
      AI_BACK_ROW_FIRST_UNIT.height
    };

    if(CheckCollisionPointRec(mousePos, playerFront)) {
      UnitInstance* unit = getPlayerUnitFront(i);

      if(unit != NULL && unit->unitType != NULL) {
        selectPreviewCard(unit->unitType->cardId);
        if(IsMouseButtonPressed(0)) {
          TraceLog(LOG_WARNING, "Clicked player front Unit");
        }
      }

    }

    if(CheckCollisionPointRec(mousePos, playerBack)) {
      UnitInstance* unit = getPlayerUnitBack(i);

      if(unit != NULL && unit->unitType != NULL) {
        selectPreviewCard(unit->unitType->cardId);
        if(IsMouseButtonPressed(0)) {
          TraceLog(LOG_WARNING, "Clicked player back Unit");
        }
      }
    }

    if(CheckCollisionPointRec(mousePos, aiFront)) {
      UnitInstance* unit = getAIUnitFront(i);

      if(unit != NULL && unit->unitType != NULL) {
        selectPreviewCard(unit->unitType->cardId);
        if(IsMouseButtonPressed(0)) {
          TraceLog(LOG_WARNING, "Clicked ai front Unit");
        }
      }

    }

    if(CheckCollisionPointRec(mousePos, aiBack)) {
      UnitInstance* unit = getAIUnitBack(i);

      if(unit != NULL && unit->unitType != NULL) {
        selectPreviewCard(unit->unitType->cardId);
        if(IsMouseButtonPressed(0)) {
          TraceLog(LOG_WARNING, "Clicked ai back Unit");
        }
      }
    }
  }
}

#include "ai.h"
#include "card.h"
#include "constants.h"
#include "gamemode.h"
#include "gamerender.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

const int cardPadding = 10;
const int cardPaddingTop = 20;
const int unitCardSize = 64;
const int cardsPerRow = 13;
const int unitRowButtonSize = 16;
const int unitRowHeight = unitCardSize + 2 * cardPadding;
const int cardTextPadding = 15;

void mainMenu_Update() {
  if (IsKeyDown(KEY_ESCAPE)) {
  }
}

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LD50");

  SetExitKey(KEY_NULL);


  initCards();

  setGameMode(INIT_MODE);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    switch (getGameMode()) {
    case INIT_MODE:
      setGameMode(MAINGAME_MODE);

      initPlayer();
      initAI();

      continue;
      break;
    case MAINGAME_MODE:
      checkGameInput();
      break;
    case AITURN_MODE:
      aiTurn();
      break;
    case GAMEOVER_MODE:
      checkGameOverInput();
    default:
      break;
    }

    if (IsKeyDown(KEY_F11)) {
      CloseWindow();
      break;
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);

    switch (getGameMode()) {
    case MAINGAME_MODE:
      renderGame();
      break;
    case AITURN_MODE:
      renderGame();
      break;
    case GAMEOVER_MODE:
      renderGameOver();
      break;
    default:
      break;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

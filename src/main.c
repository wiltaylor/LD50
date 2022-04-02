#include <stdio.h>
#include "gamemode.h"
#include "raylib.h"
#include "card.h"
#include "player.h"
#include "gamerender.h"
#include "constants.h"

static GameMode gameMode = MAINGAME_MODE;

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

void mainMenu_Draw() {
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LD50");

  SetExitKey(KEY_NULL);

  initCards();
  initPlayer();

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
      renderGame();
      break;
    default:
      break;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

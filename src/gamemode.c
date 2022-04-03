#include "gamemode.h"

GameMode currentGameMode;

void setGameMode(GameMode mode) {
  currentGameMode = mode;
}

GameMode getGameMode() {
  return currentGameMode;
}

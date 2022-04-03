#ifndef __GAMEMODE_H_
#define __GAMEMODE_H_
typedef enum GameMode {
  INIT_MODE = 0,
  MAINGAME_MODE = 1,
  AITURN_MODE = 2,
  GAMEOVER_MODE = 3,
} GameMode;

void setGameMode(GameMode mode);
GameMode getGameMode();

#endif

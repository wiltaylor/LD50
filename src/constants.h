#ifndef __CONSTANTS_H_
#define __CONSTANTS_H_
#include "raylib.h"

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;

static const int MAX_HAND_SIZE = 7;
static const float AI_TURN_LENGTH = 1.0f;

static const Rectangle HAND_FIRST_CARD = {286, 592, 128, 128};
static const Rectangle PLAYER_FRONT_ROW_FIRST_UNIT = { 276, 208, 64, 64 };
static const Rectangle PLAYER_BACK_ROW_FIRST_UNIT = { 276, 302, 64, 64 };
static const Rectangle AI_BACK_ROW_FIRST_UNIT = { 10, 10, 64, 64 };
static const Rectangle AI_FRONT_ROW_FIRST_UNIT = { 10, 104, 64, 64 };
static const Rectangle MAIN_DECK = { 10, 538, 122, 170};
static const Rectangle END_TURN = {1004, 146, 236, 32};

static const int CARD_PADDING = 10;

//static const int MAX_UNITS_PER_ROW = 13;
#define MAX_UNITS_PER_ROW 13

static const int NULL_ID = -1;

static const int DRAW_DECK_GOLD_COST = 5;
static const int DRAW_DECK_FAITH_COST = 5;

static const int STARTING_CARDS = 3;

static const int GOLD_PER_WORKER = 5;

#endif

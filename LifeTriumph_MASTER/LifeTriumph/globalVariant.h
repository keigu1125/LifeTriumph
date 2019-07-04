#include "defines.h"
#include "image.h"
#include "Player.h"
#include "Setting.h"
#include "Form.h"

Arduboy ab;
Player p[2];

Setting setting;
long tStop = 0;
long tPressed = 0;

Form* menu;
Form* time;
Form* life;

Form* sett;

Form* util;
Form* match;
Form* dice;
Form* discard;
Form* storm;
Form* counter;
Form* utils[6];

bool isTitle = false;
bool isMain = false;
bool isSound = true;
bool isInvertOpponent = false;
bool isTimer = false;
bool isTwoSideFromt = true;
bool pressFirst = true;
bool isAlarm = false;
bool isCursorUtil = false;
int changeLife = 0;
short changeCounter = 0;
byte pCount = 0;

byte winLoseRatio = 0;

byte matchCount = 0;
byte gameCount = 0;
byte winCount = 0;
byte loseCount = 0;
byte drawCount = 0;
byte m_winCount = 0;
byte m_loseCount = 0;
byte m_drawCount = 0;

byte g_his[MATCH_GAME_MAX];

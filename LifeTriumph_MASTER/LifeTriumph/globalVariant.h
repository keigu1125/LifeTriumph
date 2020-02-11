#include "defines.h"
#include "image.h"
#include "Player.h"
#include "Setting.h"
#include "Form.h"

Arduboy ab;
Player p[PLAYER_COUNT];

Setting setting;
long tStop = 0;
long tPressed = 0;

Form* menu;
Form* life;

Form* sett;

Form* util;
Form* mTimer;
Form* mLog;
Form* dice;
Form* discard;
Form* storm;
Form* utils[6];

bool isTitle = false;
bool isMain = false;
bool isSound = true;
bool isTimer = false;
bool isTwoSideFromt = true;
bool pressFirst = true;
bool pressPole = false;
bool isEnableAlarm = false;
bool isAlarm = false;
bool isAlarmOnce = true;
bool isCursorUtil = false;
byte pCount = 0;

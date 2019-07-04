// FPS
#define FPS_SLEEP 3

// LifeArdent.ino
#define BUTTON_REPEAT 330
#define TONE_LIFE     40
#define TIME_TITLE    3000
#define TONE_ONELIFE  20
#define TONE_MIN      200
#define PLAYER_COUNT  4

// displayMenu.h
#define MENU_ICON_SIZE_X  11
#define MENU_ICON_SIZE_Y  14
#define DISP_RESET_SECOND 5000

// displayMatch.h
#define MATCH_WIN  (byte)1
#define MATCH_LOSE (byte)2
#define MATCH_DRAW (byte)3
#define MATCH_PL_MAX (byte)2
#define MATCH_GAME_MAX  (byte)3

// displayLife.h
#define CURSOR_RECT_W 9
#define CURSOR_RECT_H 7
#define EDH_GENERAL_DAMAGE_RIMIT 21

//displayUtil.h
#define DICE_ALL_MAX 8
#define DICE_MAX     3
#define CARD_MAX     11
#define DISCARD_MAX  9
#define STORM_MAX    7
#define MATCH_MAX    6

//displaySetting.h
#define HIGHT 8
#define IND   12

// enum
enum Menu
{
  M_HEAD = 0,
  M_MATCH = 0,
  M_DICE = 1,
  M_DISCARD = 2,
  M_STORM = 3,
  M_COUNT = 4,
  M_SETTING = 5,
  M_TAIL = 5
};

enum SettingMenuTitle
{
  SMT_HEAD = 0,
  SMT_MENU = 0,
  SMT_MATCH = 1,
  SMT_DISPLAY = 2,
  SMT_TIMER = 3,
  SMT_FRAME = 4,
  SMT_EXIT = 5,
  SMT_TAIL = 5,
};

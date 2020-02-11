// Player.h
#define CHANGE_LIFE_LOG 3

// Setting.h
#define FPS_SLEEP 3

// LifeArdent.ino
#define BUTTON_REPEAT 330
#define TONE_LIFE     40
#define TIME_TITLE    3000
#define TONE_ONELIFE  20
#define TONE_MIN      200
#define PLAYER_COUNT  2

// displayMenu.h
#define MENU_ICON_SIZE_X  11
#define MENU_ICON_SIZE_Y  14
#define DISP_RESET_SECOND 5000

// displayLife.h
#define CURSOR_RECT_W 9
#define CURSOR_RECT_H 7

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
  M_TIMER = 0,
  M_DICE = 1,
  M_LOG = 2,
  M_DISCARD = 3,
  M_STORM = 4,
  M_SETTING = 5,
  M_TAIL = 5
};

enum SettingMenuTitle
{
  SMT_HEAD = 0,
  SMT_MENU = 0,
  SMT_DISPLAY = 1,
  SMT_SOUND = 2,
  SMT_TIMER = 3,
  SMT_FRAME = 4,
  SMT_EXIT = 5,
  SMT_TAIL = 5
};

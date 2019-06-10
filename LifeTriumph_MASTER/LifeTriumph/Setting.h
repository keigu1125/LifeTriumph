class Setting
{
#define DEF_IS_WRITE_SETTING    0x01
#define DEF_SHOW_TITLE          0x01
#define DEF_IS_SOUND_DEFAULT    0x01
#define DEF_IS_SOUND_TIMER      0x01
#define DEF_BASE_TONE           1000
#define DEF_IS_LED_TIMER        0x01
#define DEF_TIMER_DEFAULT_MIN   50
#define DEF_FRAME_RATE_MAIN     30
#define DEF_FRAME_RATE_SLEEP    0x03
#define DEF_BLACK_SCREEN        0x00
#define DEF_INVERT_OPPONENT     0x00
#define DEF_MENU_ENABLE_DICE    0x01
#define DEF_MENU_ENABLE_DISCARD 0x01
#define DEF_MENU_ENABLE_STORM   0x01
#define DEF_MENU_ENABLE_COUNT   0x01
#define DEF_SUM_GAME_WIN        0x00
#define DEF_SUM_GAME_LOSE       0x00
#define DEF_SUM_GAME_DRAW       0x00

  public:
    byte isWritedSetting = 0x00;
    byte showTitle = 0x00;
    byte isSoundDefault = 0x00;
    byte isSoundTimer = 0x00;
    int  baseTone = 0;
    byte isLedTimer = 0x00;
    byte timerDefaultMin = 0x00;
    byte frameRateMain = 0x00;
    byte frameRateSleep = 0x00;
    byte blackScreen = 0x00;
    byte invertOpponent = 0x00;
    byte menuEnableDice = 0x00;
    byte menuEnableDiscard = 0x00;
    byte menuEnableStorm = 0x00;
    byte menuEnableCount = 0x00;
    byte menuRotate = 0x00;
    int  sumGameWin = 0x00;
    int  sumGameLose = 0x00;
    int  sumGameDraw = 0x00;

    void readEepRomSetting()
    {
      byte point = 16;
      isWritedSetting = EEPROM.read(point++);
      if (isWritedSetting == 0x00)
      {
        setDefaultSetting();
        return;
      }

      showTitle = EEPROM.read(point++);
      isSoundDefault = EEPROM.read(point++);
      isSoundTimer = EEPROM.read(point++);
      baseTone = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      isLedTimer = EEPROM.read(point++);
      timerDefaultMin = EEPROM.read(point++);
      frameRateMain = EEPROM.read(point++);
      frameRateSleep = EEPROM.read(point++);
      blackScreen = EEPROM.read(point++);
      invertOpponent = EEPROM.read(point++);
      menuEnableDice = EEPROM.read(point++);
      menuEnableDiscard = EEPROM.read(point++);
      menuEnableStorm = EEPROM.read(point++);
      menuEnableCount = EEPROM.read(point++);
      menuRotate = EEPROM.read(point++);
      sumGameWin = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      sumGameLose = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      sumGameDraw = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
    }

    void writeEepRomSetting()
    {
      // *** !! BE CAREFUL !! *** //
      byte point = 16;
      EEPROM.write(point++, isWritedSetting);
      EEPROM.write(point++, showTitle);
      EEPROM.write(point++, isSoundDefault);
      EEPROM.write(point++, isSoundTimer);
      EEPROM.write(point++, ((baseTone >> 8) & 0xFF));
      EEPROM.write(point++, (baseTone & 0xFF));
      EEPROM.write(point++, isLedTimer);
      EEPROM.write(point++, timerDefaultMin);
      EEPROM.write(point++, frameRateMain);
      EEPROM.write(point++, frameRateSleep);
      EEPROM.write(point++, blackScreen);
      EEPROM.write(point++, invertOpponent);
      EEPROM.write(point++, menuEnableDice);
      EEPROM.write(point++, menuEnableDiscard);
      EEPROM.write(point++, menuEnableStorm);
      EEPROM.write(point++, menuEnableCount);
    }

    void setDefaultSetting()
    {
      isWritedSetting = DEF_IS_WRITE_SETTING;
      showTitle = DEF_SHOW_TITLE;
      isSoundDefault = DEF_IS_SOUND_DEFAULT;
      isSoundTimer = DEF_IS_SOUND_TIMER;
      baseTone = DEF_BASE_TONE;
      isLedTimer = DEF_IS_LED_TIMER;
      timerDefaultMin = DEF_TIMER_DEFAULT_MIN;
      frameRateMain = DEF_FRAME_RATE_MAIN;
      frameRateSleep = DEF_FRAME_RATE_SLEEP;
      blackScreen = DEF_BLACK_SCREEN;
      invertOpponent = DEF_INVERT_OPPONENT;
      menuEnableDice = DEF_MENU_ENABLE_DICE;
      menuEnableDiscard = DEF_MENU_ENABLE_DISCARD;
      menuEnableStorm = DEF_MENU_ENABLE_STORM;
      menuEnableCount = DEF_MENU_ENABLE_COUNT;
    }

  private:
};

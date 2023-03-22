class DisplaySetting : public Form
{
  private:
    byte cursorC = 0;
  public:
    byte cursorCMax = 0;

    DisplaySetting()
    {
      // x = 0;
      // y = 0;
      w = 128;
      h = 64;
      // isCursor = false;
      // cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;
      icon = i_setting;
    }

    void display()
    {
      displayHead();
      displayDetail();
      drawCursor();
    }

    void execute() {};

    virtual void upButton()
    {
      subValue(&cursorC, 0);
    }

    virtual void downButton()
    {
      addValue(&cursorC, cursorCMax);
    }

    virtual void leftButton()
    {
      if (cursorC == 0)
      {
        subValue(&cursor, SMT_HEAD);
        return;
      }

      switch (cursor)
      {
        case SMT_MENU:
          switch (cursorC)
          {
            case 0x01:
              subValue(&setting.menuRotate, 0x00);
              break;
            case 0x02:
              subValue(&setting.menuEnableDice, 0x00);
              break;
            case 0x03:
              subValue(&setting.menuEnableLog, 0x00);
              break;
            case 0x04:
              subValue(&setting.menuEnableDiscard, 0x00);
              break;
            case 0x05:
              subValue(&setting.menuEnableStorm, 0x00);
              break;
            case 0x06:
              subValue(&setting.menuDefault, Menu::M_HEAD);
              break;
          }
          break;
        case SMT_DISPLAY:
          switch (cursorC)
          {
            case 0x01:
              subValue(&setting.showTitle, 0x00);
              break;
            case 0x02:
              subValue(&setting.blackScreen, 0x00);
              break;
            case 0x03:
              subValue(&setting.invertOpponent, 0x00);
              break;
          }
          break;
        case SMT_SOUND:
          switch (cursorC)
          {
            case 0x01:
              subValue(&setting.isSoundKeyPress, 0x00);
              break;
            case 0x02:
              if (setting.baseTone > 100)
              {
                setting.baseTone -= 10;
              }
              break;
          }
          break;
        case SMT_TIMER:
          switch (cursorC)
          {
            case 0x01:
              subValue(&setting.timerDefaultMin, 0x00);
              break;
            case 0x02:
              subValue(&setting.isSoundTimer, 0x00);
              break;
            case 0x03:
              subValue(&setting.isLedTimer, 0x00);
              break;
          }
          break;
        case SMT_FRAME:
          switch (cursorC)
          {
            case 0x01:
              subValue(&setting.frameRateMain, 0x01);
              break;
            case 0x02:
              subValue(&setting.frameRateSleep, 0x01);
              break;
          }
          break;
        case SMT_EXIT:
          break;
      }
    }

    virtual void rightButton()
    {
      if (cursorC == 0x00)
      {
        addValue(&cursor, SMT_TAIL);
        return;
      }

      switch (cursor)
      {
        case SMT_MENU:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.menuRotate, 0x01);
              break;
            case 0x02:
              addValue(&setting.menuEnableDice, 0x01);
              break;
            case 0x03:
              addValue(&setting.menuEnableLog, 0x01);
              break;
            case 0x04:
              addValue(&setting.menuEnableDiscard, 0x01);
              break;
            case 0x05:
              addValue(&setting.menuEnableStorm, 0x01);
              break;
            case 0x06:
              addValue(&setting.menuDefault, Menu::M_TAIL);
              break;
          }
          break;
        case SMT_DISPLAY:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.showTitle, 0x01);
              break;
            case 0x02:
              addValue(&setting.blackScreen, 0x01);
              break;
            case 0x03:
              addValue(&setting.invertOpponent, 0x01);
              break;
          }
          break;
        case SMT_SOUND:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.isSoundKeyPress, 0x01);
              break;
            case 0x02:
              if (setting.baseTone < 6000)
              {
                setting.baseTone += 10;
              }
              break;
          }
          break;
        case SMT_TIMER:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.timerDefaultMin, 60);
              break;
            case 0x02:
              addValue(&setting.isSoundTimer, 0x01);
              break;
            case 0x03:
              addValue(&setting.isLedTimer, 0x01);
              break;
          }
          break;
        case SMT_FRAME:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.frameRateMain, 60);
              break;
            case 0x02:
              addValue(&setting.frameRateSleep, setting.frameRateMain);
              break;
          }
        case SMT_EXIT:
          break;
      }
    }

    virtual void aButton() {}

    virtual void bButton()
    {
      if (cursor != SMT_EXIT || cursorC == 0)
      {
        return;
      }

      switch (cursor)
      {
        case SMT_EXIT:
          switch (cursorC)
          {
            case 0x01:
              setting.isWritedSetting = 0x01;
              break;
            case 0x02:
              activeMenu();
              return;
            case 0x03:
              setting.isWritedSetting = 0x00;
              break;
          }

          setting.writeEepRomSetting();
          delay(1000);
          asm volatile ("   jmp 0");
          break;
      }
    }

    virtual void abButton() {}
    virtual void udButton() {}

  private:
    char* getMenuTitle(byte c)
    {
      switch (c)
      {
        case SMT_MENU:
          return "MENU ";
        case SMT_DISPLAY:
          return "DISP ";
        case SMT_SOUND:
          return "SOUND";
        case SMT_TIMER:
          return "TIMER";
        case SMT_FRAME:
          return "FRAME";
        case SMT_EXIT:
          return "EXIT ";
        case SMT_ABOUT:
          return "ABOUT";
      }
    }

    void DisplaySetting::displayHead()
    {
      ab.drawLine(0, 10, 128, 10, WHITE);

      byte drawX = 0;
      for (byte i = SMT_HEAD; i <= SMT_TAIL; i++)
      {
        if (i != cursor)
        {
          ab.drawRect(drawX, 2, 10, 6, WHITE);
          drawX += 13;
        }
        else
        {
          ab.drawRect(drawX, 0, 39, 11, WHITE);
          if (cursorC == 0)
          {
            drawArrowLeft(drawX + 3, 2, WHITE);
          }
          drawText(drawX + 8, 2, 1, getMenuTitle(i));
          drawX += 42;
        }
      }
    }

    void DisplaySetting::displayDetail()
    {
      byte row = 0;
      byte drawX = 7;
      byte drawY = 13;
      switch (cursor)
      {
        case SMT_MENU:
          cursorCMax = 6;
          drawText(drawX, drawY + (row * HIGHT), 1, "Menu Rotate");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuRotate));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Dice");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableDice));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use LifeLog");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableLog));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Discard");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableDiscard));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Storm");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableStorm));
          drawText(drawX, drawY + (row * HIGHT), 1, "DEFAULT : ");
          drawText(drawX + IND + 48, drawY + (row++ * HIGHT) + 1, 1, getMenuName(setting.menuDefault));
          break;
        case SMT_DISPLAY:
          cursorCMax = 3;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Title");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.showTitle));
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Screen");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getBlackWhite(setting.blackScreen));
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Invert Opponent");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.invertOpponent));
          break;
        case SMT_SOUND:
          cursorCMax = 2;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "KeyPress Sound");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.isSoundKeyPress));
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Base Tone");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.baseTone) + " Hz");
          break;
        case SMT_TIMER:
          cursorCMax = 3;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Def Match Time");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.timerDefaultMin) + " min");
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Alarm Sound");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.isSoundTimer));
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Alarm LED");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.isLedTimer));
          break;
        case SMT_FRAME:
          cursorCMax = 2;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Frame Rate (Main)");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.frameRateMain) + " fps");
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Frame Rate (Sleep)");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.frameRateSleep) + " fps");
          break;
        case SMT_EXIT:
          cursorCMax = 3;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Save and Reboot");
          row++;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Discard Changes");
          row++;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "*Erase and Reboot*");
          row++;
          break;
        case SMT_ABOUT:
          cursorCMax = 0;
          row++;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "   Life Triumph");
          drawText(drawX, drawY + (row++ * HIGHT), 1, " -MTG LifeCounter-");
          row++;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "@keigu1");
          drawText(drawX, drawY + (row++ * HIGHT), 1, APP_VER);
          break;
      }
    }

    void DisplaySetting::drawCursor()
    {
      if (cursorC == 0)
      {
        return;
      }

      if (cursor == SMT_MENU)
      {
        drawArrowLeft(1, 13 + ((cursorC - 1) * HIGHT), WHITE);
      }
      else
      {
        drawArrowLeft(1, 13 + ((cursorC - 1) * HIGHT * 2), WHITE);
      }
    }
};

class DisplaySetting : public Form
{
  private:
    byte cursorC = 0;
    bool isResetMatch = false;
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
            case 1:
              subValue(&setting.menuRotate, 0x00);
              break;
            case 2:
              subValue(&setting.menuEnableDice, 0x00);
              break;
            case 3:
              subValue(&setting.menuEnableDiscard, 0x00);
              break;
            case 4:
              subValue(&setting.menuEnableStorm, 0x00);
              break;
            case 5:
              subValue(&setting.menuEnableCount, 0x00);
              break;
          }
          break;
        case SMT_MATCH:
          break;
        case SMT_SOUND:
          break;
        case SMT_DISPLAY:
          switch (cursorC)
          {
            case 1:
              subValue(&setting.showTitle, 0x00);
              break;
            case 2:
              subValue(&setting.blackScreen, 0x00);
              break;
            case 3:
              subValue(&setting.invertOpponent, 0x00);
              break;
          }
          break;
        case SMT_TIMER:
          switch (cursorC)
          {
            case 1:
              subValue(&setting.timerDefaultMin, 0x00);
              break;
            case 2:
              subValue(&setting.isLedTimer, 0x00);
          }
          break;
        case SMT_FRAME:
          switch (cursorC)
          {
            case 1:
              subValue(&setting.frameRateMain, 0x01);
              ab.setFrameRate(setting.frameRateMain);
              break;
            case 2:
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
            case 1:
              addValue(&setting.menuRotate, 0x01);
              break;
            case 2:
              addValue(&setting.menuEnableDice, 0x01);
              break;
            case 3:
              addValue(&setting.menuEnableDiscard, 0x01);
              break;
            case 4:
              addValue(&setting.menuEnableStorm, 0x01);
              break;
            case 5:
              addValue(&setting.menuEnableCount, 0x01);
              break;
          }
          break;
        case SMT_MATCH:
          break;
        case SMT_SOUND:
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
        case SMT_TIMER:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.timerDefaultMin, 60);
              break;
            case 0x02:
              addValue(&setting.isLedTimer, 0x01);
              break;
          }
          break;
        case SMT_FRAME:
          switch (cursorC)
          {
            case 0x01:
              addValue(&setting.frameRateMain, 60);
              ab.setFrameRate(setting.frameRateMain);
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
      if ((cursor != SMT_EXIT && cursor != SMT_MATCH) || cursorC == 0)
      {
        return;
      }

      switch (cursor)
      {
        case SMT_MATCH:
          if (cursorC == 1)
          {
            isResetMatch = !isResetMatch;
          }
          break;
        case SMT_EXIT:
          switch (cursorC)
          {
            case 0x01:
              setting.isWritedSetting = 0x01;
              if (isResetMatch)
              {
                setting.sumMatchWin = 0x00;
                setting.sumMatchLose = 0x00;
                setting.sumMatchDraw = 0x00;
              }
              setting.writeEepRomSetting();
              break;
            case 0x02:
              activeMenu();
              return;
            case 0x03:
              setting.isWritedSetting = 0x00;
              setting.writeEepRomSetting();
              break;
          }

          delay(1000);
          asm volatile ("   jmp 0");
          break;
      }
    }

    virtual void abButton() {}

  private:
    char* getMenuTitle(byte c)
    {
      switch (c)
      {
        case SMT_MENU:
          return "MENU ";
        case SMT_MATCH:
          return "MATCH";
        case SMT_SOUND:
          return "SOUND";
        case SMT_DISPLAY:
          return "DISP ";
        case SMT_TIMER:
          return "TIMER";
        case SMT_FRAME:
          return "FRAME";
        case SMT_EXIT:
          return "EXIT ";
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
          cursorCMax = 5;
          drawText(drawX, drawY + (row * HIGHT), 1, "Menu Rotate");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuRotate));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Dice");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableDice));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Discard");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableDiscard));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Storm");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableStorm));
          drawText(drawX, drawY + (row * HIGHT), 1, "Use Count");
          drawText(drawX + IND + 70, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.menuEnableCount));
          break;
        case SMT_MATCH:
          cursorCMax = 1;
          if (isResetMatch)
          {
            drawText(drawX, drawY + (row * HIGHT), 1, "* Will be Reset *");
          }
          else
          {
            drawText(drawX, drawY + (row * HIGHT), 1, "Reset MatchLog ?");
          }
          row++;
          row++;
          drawText(drawX, drawY + (row * HIGHT), 1, "Win   : ");
          drawText(drawX + IND + 50, drawY + (row++ * HIGHT) + 1, 1, String(setting.sumMatchWin));
          drawText(drawX, drawY + (row * HIGHT), 1, "Lose  : ");
          drawText(drawX + IND + 50, drawY + (row++ * HIGHT) + 1, 1, String(setting.sumMatchLose));
          drawText(drawX, drawY + (row * HIGHT), 1, "Draw  : ");
          drawText(drawX + IND + 50, drawY + (row++ * HIGHT) + 1, 1, String(setting.sumMatchDraw));
          drawText(drawX, drawY + (row * HIGHT), 1, "Ratio : ");
          drawText(drawX + IND + 50, drawY + (row++ * HIGHT) + 1, 1, String(winLoseRatio) + " %");
          break;
        case SMT_SOUND:
          cursorCMax = 0;
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
        case SMT_TIMER:
          cursorCMax = 2;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Def Match Time");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.timerDefaultMin) + " min");
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Timer LED");
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

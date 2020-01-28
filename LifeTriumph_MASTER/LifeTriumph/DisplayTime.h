class DisplayTime : public Form
{
  private:
    byte ledCount = 0;
    byte toneCnt = 0;
    long toneStart = 0;

  public:
    DisplayTime()
    {
      x = 1;
      y = 57;
      // isCursor = false;
      // cursor = 0;
      // cursorMax = 0;
      icon = i_timer;
    }

    void DisplayTime::display()
    {
      dispTimer();
      if (isEnableAlarm && isAlarmOnce)
      {
        checkAlarm();
        if (isAlarm)
        {
          alarm();
        }
      }
    }

    void execute()
    {
      toggle();
    }

    virtual void upButton() {}
    virtual void downButton() {}
    virtual void leftButton() {}
    virtual void rightButton() {}
    virtual void aButton() {}
    virtual void bButton() {}
    virtual void abButton()
    {
      tStop = setting.timerDefaultMin * 60000;
      isAlarmOnce = true;
    }

    void toggle()
    {
      isTimer = !isTimer;

      if (isTimer)
      {
        // Start
        tStop += millis();
      }
      else
      {
        // Pause
        tStop -= millis();
      }
    }

  private:

    void DisplayTime::dispTimer()
    {
      if (isCursor)
      {
        drawArrowLeft(x, y, WHITE);
      }

      ab.drawBitmap(x + 51, y - 1, (isTimer) ? i_s_play : i_s_stop, 9, 9, WHITE);

      long tDisp = 0;
      byte w = 0;
      if (isTimer)
      {
        tDisp = tStop - millis();
      }
      else
      {
        tDisp = tStop;
      }

      if (isOverTime(tDisp))
      {
        drawText(x + 0, y, 1, "-");
      }
      drawText(x + 6, y, 1, getHMS(tDisp));

      w = getMinute(tDisp);

      ab.fillRect(x + 64, y, w > setting.timerDefaultMin ? setting.timerDefaultMin : w, 3, WHITE);
      ab.drawLine(x + 64, y + 6, x + 64 + setting.timerDefaultMin, y + 6, WHITE);

      for (byte i = 0; i <= setting.timerDefaultMin; i += 5)
      {
        byte hight = (i % 10 == 0) ? 2 : 1;
        byte lineX = x + 64 + i;
        byte lineY = y + 6;
        ab.drawLine(lineX, lineY - hight, lineX, lineY, WHITE);
      }
    }

    void checkAlarm()
    {
      if (!isTimer)
      {
        return;
      }
      
      long tDisp = tStop - millis();
      if (getSecond(tDisp) != 1 || !isOverTime(tDisp))
      {
        return;
      }
      
      isAlarm = true;
    }

    void alarm()
    {
      pressPole = true;
      byte toneCnt = 0;
      long toneStart = millis();
      while (!someButtonPressed())
      {
        int time = millis() - toneStart;
        if ((toneCnt == 0 && time >= 0) || (toneCnt == 1 && time >= 250))
        {
          toneCnt++;
          if (setting.isLedTimer)
          {
            ab.setRGBled(1, 0, 0);
          }
          if (setting.isSoundTimer)
          {
            ab.tunes.tone(setting.baseTone, 200);
          }
        }
        else if (toneCnt == 2)
        {
          toneCnt++;
          ab.setRGBled(0, 0, 0);
        }
        else if (time > 1000)
        {
          toneCnt = 0;
          toneStart = millis();
        }
      }
      ab.setRGBled(0, 0, 0);
      
      pressPole = true;
      pressFirst = false;
      isAlarm = false;
      isAlarmOnce = false;
    }

};

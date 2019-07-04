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
    }

    void DisplayTime::display()
    {
      dispTimer();
      alarm();
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
    virtual void abButton() {}

    void toggle()
    {
      isTimer = !isTimer;

      if (isTimer)
      {
        // Start
        tStop = setting.timerDefaultMin * 60000;
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

      if (tStop < millis())
      {
        drawText(x + 2, y, 1, "-" + getHMS(tDisp));
      }
      else
      {
        drawText(x + 6, y, 1, getHMS(tDisp));
      }

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

    void alarm()
    {
      if (!isAlarm || tStop >= millis())
      {
        return;
      }

      if (ledCount == 0)
      {
        toneStart = millis();
        ledCount++;
      }

      if (!someButtonPressed() && ledCount <= 5)
      {
        int time = millis() - toneStart;
        if ((toneCnt == 0 && time >= 0) || (toneCnt == 1 && time >= 250))
        {
          toneCnt++;
          ab.setRGBled(ledCount, 0, 0);
        }
        else if (toneCnt == 2)
        {
          toneCnt++;
          ab.setRGBled(0, 0, 0);
        }
        else if (time > 1000)
        {
          toneCnt = 0;
          ledCount++;
          toneStart = millis();
        }
      }
      else
      {
        ab.setRGBled(0, 0, 0);
        isAlarm = false;
      }
    }
};

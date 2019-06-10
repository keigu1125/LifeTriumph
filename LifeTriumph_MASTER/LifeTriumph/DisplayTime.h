class DisplayTime : public Form
{
  private:
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
        tStop = ALARM_DEFAULT;
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
      byte w = 0;
      if (isTimer)
      {
        drawText(x + 6, y, 1, getHMS(tStop - millis()));
        w = getMinute(tStop - millis());
      }
      else
      {
        drawText(x + 6, y, 1, getHMS(tStop));
        w = getMinute(tStop);
      }

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
};

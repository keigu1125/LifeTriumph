class DisplayStorm : public Form
{
  private:
    byte stormCount[7] = {0, 0, 0, 0, 0, 0, 0};
  public:
    DisplayStorm()
    {
      x = 0;
      y = 43;
      w = 128;
      h = 11;
      // isCursor = false;
      // cursor = 0;
      cursorMax = 6;
      isEnable = setting.menuEnableStorm;
      icon = i_storm;
    }

    void display()
    {
      ab.drawBitmap(x +   2, y + 1, i_s_storm, 9, 9, WHITE);
      ab.drawBitmap(x +  26, y + 1, i_s_white, 9, 9, WHITE);
      ab.drawBitmap(x +  43, y + 1, i_s_blue , 9, 9, WHITE);
      ab.drawBitmap(x +  60, y + 1, i_s_black, 9, 9, WHITE);
      ab.drawBitmap(x +  77, y + 1, i_s_red  , 9, 9, WHITE);
      ab.drawBitmap(x +  94, y + 1, i_s_green, 9, 9, WHITE);
      ab.drawBitmap(x + 111, y + 1, i_s_less , 9, 9, WHITE);

      drawText(x + 12, y + 2, 1, stormCount[6]);
      for (byte i = 0; i < STORM_MAX - 1; i++)
      {
        drawText(x + 35 + (i * 17), y + 2, 1, stormCount[i]);
      }

      if (isCursor)
      {
        ab.drawRect(x, y, w, h, WHITE);
        ab.drawRect(x + 7 + ((cursor + 1) * 17), y + 2, 2, 7, WHITE);
      }
    }

    void execute() {};

    virtual void upButton()
    {
      addValue(&stormCount[cursor], 9);
    }

    virtual void downButton()
    {
      subValue(&stormCount[cursor], 0);
    }

    virtual void leftButton()
    {
      if (cursor == 0)
      {
        isCursorUtil = false;
        activeMenu();
        return;
      }

      rotateDown(&cursor, 0, cursorMax);
    }

    virtual void rightButton()
    {
      rotateUp(&cursor, 0, cursorMax);
      if (cursor >= cursorMax)
      {
        isCursorUtil = false;
        activeMenu();
        return;
      }
    }

    virtual void aButton()
    {
      activeLife();
    }

    virtual void bButton()
    {
      addValue(&stormCount[6], 99);
    }

    virtual void abButton()
    {
      initArray(stormCount, STORM_MAX);
    }

  private:

};

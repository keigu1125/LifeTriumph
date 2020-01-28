class DisplayDice : public Form
{
  private:
  public:
    byte dCount = 2;
    byte dSum1 = 0;
    byte dSum2 = 0;
    byte d1[2] = {0, 0};
    byte d2[2] = {0, 0};

    DisplayDice()
    {
      x = 0;
      y = 43;
      w = 128;
      h = 12;
      // isCursor = false;
      // cursor = 0;
      // cursorMax = 0;
      isEnable = setting.menuEnableDice;
      icon = i_dice_b;
    }

    void display()
    {
      if (!isDisp())
      {
        return;
      }

      ab.drawRect(31, 43, 97, 11, WHITE);
      ab.drawLine(79, 43, 79, 53, WHITE);

      for (byte i = 0; i < dCount; i++)
      {
        drawBigDice(x + 33 + (10 * i), y + 2, d1[i]);
        drawBigDice(x + 82 + (10 * i), y + 2, d2[i]);
      }

      drawText(x + 64, y + 2, 1, dSum1);
      drawText(x + 113, y + 2, 1, dSum2, isInvertOpponent);
    }

    void execute()
    {
      dSum1 = 0;
      dSum2 = 0;

      for (byte i = 0; i < dCount; i++)
      {
        d1[i] = random(6) + 1;
        d2[i] = random(6) + 1;
        dSum1 += d1[i];
        dSum2 += d2[i];
      }

      setTime();
    }

    virtual void upButton() {}
    virtual void downButton() {}
    virtual void leftButton() {}
    virtual void rightButton() {}
    virtual void aButton() {}
    virtual void bButton() {}
    virtual void abButton() {}

  private:

};

class DisplayLog : public Form
{
  private:
  public:
    DisplayLog()
    {
      x = 0;
      y = 43;
      w = 128;
      h = 12;
      // isCursor = false;
      // cursor = 0;
      // cursorMax = 0;
      isEnable = setting.menuEnableLog;
      icon = i_log;
    }

    void display()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        byte lc = (p[i].logCount >= CHANGE_LIFE_LOG) ? CHANGE_LIFE_LOG : p[i].logCount;
        if (lc == 0)
        {
          continue;
        }

        for (byte j = 0; j < lc; j++)
        {
          short l;
          byte drawX;
          byte drawY;
          if (p[i].invert)
          {
            drawX = x + 32 + ((PLAYER_COUNT - i) * 54) + (14 * (CHANGE_LIFE_LOG - j - 1));
            drawY = y + 2;
            l = p[i].lifeLog[j];
          }
          else
          {
            drawX = x + 32 + (i * 54) + (14 * j);
            drawY = y + 2;
            l = p[i].lifeLog[lc - 1 - j];
          }
          drawSmallNumber(drawX, drawY, l, WHITE, p[i].invert);
          ab.drawRect(drawX - 1, y, 15, 11, WHITE);
        }
      }
    }

    void execute() {}
    virtual void upButton() {}
    virtual void downButton() {}
    virtual void leftButton() {}
    virtual void rightButton() {}
    virtual void aButton() {}
    virtual void bButton() {}
    virtual void abButton() {}
    virtual void udButton() {}

  private:
    void drawOneSmallNumber(byte x, byte y, byte number, bool color)
    {
      switch (number)
      {
        case 0:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          break;
        case 1:
          ab.drawLine(x + 3, y + 1, x + 3, y + 5, color);
          break;
        case 2:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 1, y + 2, !color);
          ab.drawPixel(x + 3, y + 4, !color);
          break;
        case 3:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 1, y + 2, !color);
          ab.drawPixel(x + 1, y + 4, !color);
          break;
        case 4:
          ab.drawLine(x + 3, y + 1, x + 3, y + 5, color);
          ab.drawPixel(x + 1, y + 1, color);
          ab.drawPixel(x + 1, y + 2, color);
          ab.drawPixel(x + 1, y + 3, color);
          ab.drawPixel(x + 2, y + 3, color);
          break;
        case 5:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 3, y + 2, !color);
          ab.drawPixel(x + 1, y + 4, !color);
          break;
        case 6:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 3, y + 2, !color);
          break;
        case 7:
          ab.drawLine(x + 3, y + 1, x + 3, y + 5, color);
          ab.drawPixel(x + 1, y + 1, color);
          ab.drawPixel(x + 2, y + 1, color);
          break;
        case 8:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          break;
        case 9:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 1, y + 4, !color);
          break;
        case 10:
          // +
          ab.drawLine(x + 2, y + 2, x + 4, y + 2, color);
          ab.drawLine(x + 1, y + 2, x + 3, y + 2, color);
          break;
        case 11:
          // -
          ab.drawLine(x + 1, y + 3, x + 3, y + 3, color);
          break;
        case 12:
          // brank
          break;
      }
    }

    void drawInvertOneSmallNumber(byte x, byte y, byte number, bool color)
    {
      switch (number)
      {
        case 0:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          break;
        case 1:
          ab.drawLine(x + 1, y + 1, x + 1, y + 5, color);
          break;
        case 2:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 1, y + 2, !color);
          ab.drawPixel(x + 3, y + 4, !color);
          break;
        case 3:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 3, y + 2, !color);
          ab.drawPixel(x + 3, y + 4, !color);
          break;
        case 4:
          ab.drawLine(x + 1, y + 1, x + 1, y + 5, color);
          ab.drawPixel(x + 3, y + 5, color);
          ab.drawPixel(x + 3, y + 4, color);
          ab.drawPixel(x + 3, y + 3, color);
          ab.drawPixel(x + 2, y + 3, color);
          break;
        case 5:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 3, y + 2, !color);
          ab.drawPixel(x + 1, y + 4, !color);
          break;
        case 6:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 1, y + 4, !color);
          break;
        case 7:
          ab.drawLine(x + 1, y + 1, x + 1, y + 5, color);
          ab.drawPixel(x + 3, y + 5, color);
          ab.drawPixel(x + 2, y + 5, color);
          break;
        case 8:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          break;
        case 9:
          ab.drawRect(x + 1, y + 1, 3, 5, color);
          ab.drawPixel(x + 2, y + 3, color);
          ab.drawPixel(x + 3, y + 2, !color);
          break;
        case 10:
          // +
          ab.drawLine(x + 2, y + 2, x + 4, y + 2, color);
          ab.drawLine(x + 1, y + 2, x + 3, y + 2, color);
          break;
        case 11:
          // -
          ab.drawLine(x + 1, y + 3, x + 3, y + 3, color);
          break;
        case 12:
          // brank
          break;
      }
    }

    void drawSmallNumber(byte x, byte y, short num, bool color, bool isInvert)
    {
      byte maxDigit = 3;
      byte digit = 0;
      bool isMinus = (num < 0);

      if (num > 999)
      {
        num = 999;
      }
      else if (num < -99)
      {
        num = -99;
      }

      if (isMinus)
      {
        num *= -1;
      }

      if (num == 0)
      {
        digit = 1;
      }
      else
      {
        short s = num;
        while (s != 0)
        {
          s /= 10;
          digit++;
        }
      }

      byte sb[maxDigit] = {12, 12, 12};
      short s = num;

      for (byte i = 0; i < digit; i++)
      {
        sb[i] = (s % 10);
        s /= 10;
      }

      if (isMinus)
      {
        sb[digit] = 11;
      }

      for (byte i = 0; i < maxDigit; i++)
      {
        if (isInvert)
        {
          drawInvertOneSmallNumber(x + (maxDigit - i - 1) * 4, y, sb[maxDigit - i - 1], color);
        }
        else
        {
          drawOneSmallNumber(x + i * 4, y, sb[maxDigit - i - 1], color);
        }
      }
    }
};

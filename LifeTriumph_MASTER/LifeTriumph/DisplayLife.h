class DisplayLife : public Form
{
  private:
    bool isLifeLink = false;
  public:

    DisplayLife()
    {
      x = 31;
      // y = 0;
      w = 97;
      h = 41;
      // isCursor = false;
      // cursor = 0;
    }

    void display()
    {
      drawFrame();
      drawLife();

      if (isCursor)
      {
        drawCursor();
      }
    }

    void execute() {};

    virtual void upButton()
    {
      addLife(0, 1);
    }

    virtual void downButton()
    {
      addLife(1, -1);
    }

    virtual void leftButton()
    {
      addLife(0, -1);
    }

    virtual void rightButton()
    {
      addLife(1, 1);
    }

    virtual void aButton()
    {
      saveChangeLife();
      isLifeLink = false;
      activeMenu();
    }

    virtual void bButton()
    {
      isLifeLink = !isLifeLink;
    }

    virtual void abButton()
    {
      initPlayerLife();
      saveChangeLife();
    }

  private:
    void DisplayLife::drawFrame()
    {
      byte xCenter = x + (w / 2);
      byte yCenter = y + (h / 2);
      ab.drawLine(xCenter, y, xCenter, h - 1, WHITE);
      ab.drawRect(x, y, w, h, WHITE);

      if (isLifeLink)
      {
        ab.drawLine(xCenter - 4, yCenter, xCenter, yCenter - 6, WHITE);
        ab.drawLine(xCenter - 4, yCenter, xCenter, yCenter + 6, WHITE);
        ab.drawLine(xCenter + 4, yCenter, xCenter, yCenter - 6, WHITE);
        ab.drawLine(xCenter + 4, yCenter, xCenter, yCenter + 6, WHITE);
      }
    }

    void DisplayLife::drawCursor()
    {
      ab.drawRect(x + 1, y + 1, w - 2, h - 2, WHITE);
    }

    void DisplayLife::drawLife()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        Player pl = p[i];

        int life = pl.life;
        byte fSize = 3;
        byte drawX = pl.x + x;
        byte drawY = pl.y + y;

        if (life >= 100 || life <= -10)
        {
          drawX += 7;
          drawY += 14;
          fSize = 2;
        }
        else if (life >= 0 && life <= 9)
        {
          drawX += 17;
          drawY += 10;
          // fSize = 3;
        }
        else
        {
          drawX += 8;
          drawY += 10;
          // fSize = 3;
        }

        drawText(drawX, drawY, fSize, life, setting.invertOpponent && pl.invert);
      }
    }

    void addLife(bool c, short value)
    {
      cursor = c;
      p[cursor].life += value;
      p[cursor].changeLife += value;

      if (isLifeLink)
      {
        p[!cursor].life -= value;
        p[!cursor].changeLife -= value;
      }
    }
};

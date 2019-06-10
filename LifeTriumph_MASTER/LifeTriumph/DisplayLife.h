class DisplayLife : public Form
{
  private:
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
      if (cursor != 0)
      {
        cursor = 0;
        changeLife = 0;
      }
      p[0].life++;
      changeLife++;
    }

    virtual void downButton()
    {
      if (cursor != 1)
      {
        cursor = 1;
        changeLife = 0;
      }
      p[1].life--;
      changeLife--;
    }

    virtual void leftButton()
    {
      if (cursor != 0)
      {
        cursor = 0;
        changeLife = 0;
      }
      p[0].life--;
      changeLife--;
    }

    virtual void rightButton()
    {
      if (cursor != 1)
      {
        cursor = 1;
        changeLife = 0;
      }
      p[1].life++;
      changeLife++;
    }

    virtual void aButton()
    {
      changeLife = 0;
      activeMenu();
    }

    virtual void bButton()
    {
      // LifeLink?
    }

    //    virtual void aButton()
    //    {
    //      char value = (cursor == 0) ? - 1 : + 1;
    //
    //      p[0].life += value;
    //      p[1].life -= value;
    //      changeLife--;
    //    }
    //
    //    virtual void bButton()
    //    {
    //      char value = (cursor == 0) ? + 1 : - 1;
    //
    //      p[0].life += value;
    //      p[1].life -= value;
    //      changeLife++;
    //    }

    virtual void abButton()
    {
      initPlayerLife();
      changeLife = 0;
    }

  private:
    void DisplayLife::drawFrame()
    {
      ab.drawLine(x + (w / 2), y, x + (w / 2), h - 1, WHITE);
      ab.drawRect(x, y, w, h, WHITE);
    }

    void DisplayLife::drawCursor()
    {
      ab.drawRect(x + 1, y + 1, w - 2, h - 2, WHITE);
    }

    void DisplayLife::drawLife()
    {
      for (byte i = 0; i < 2; i++)
      {
        Player pl = p[i];

        int life = pl.life;
        byte fSize = 2;
        byte drawX = pl.x + x;
        byte drawY = pl.y + y;

        if (life >= 100 || life <= -10)
        {
          drawX += 7;
          drawY += 14;
          // fSize = 2;
        }
        else if (life >= 0 && life <= 9)
        {
          drawX += 17;
          drawY += 10;
          fSize = 3;
        }
        else
        {
          drawX += 8;
          drawY += 10;
          fSize = 3;
        }

        drawText(drawX, drawY, fSize, life, isInvertOpponent && pl.invert);
      }
    }
};

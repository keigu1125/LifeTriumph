class DisplayCounter : public Form
{
  private:
  public:

    DisplayCounter()
    {
      x = 0;
      y = 43;
      w = 128;
      h = 11;
      // isCursor = false;
      // cursor = 0;
      cursorMax = 2;
      isEnable = setting.menuEnableCount;
      icon = i_poison;
    }

    void display()
    {
      if (isCursor)
      {
        ab.drawRect(x, y, menu->w, h, WHITE);
        drawArrowLeft(x + 33 + (cursor * 48), y + 2, WHITE);
        if (changeCounter != 0)
        {
          drawText((changeCounter < 10 ) ? x + 9 : x + 5, y + 2, 1, (changeCounter > 0) ? "+" + String(changeCounter) : changeCounter);
        }
        else
        {
          drawText(x +  9, y + 2, 1, "P");
          drawText(x + 15, y + 2, 1, cursor + 1);
        }
      }

      drawUtilForm(true);

      for (byte i = 0; i < p[0].counter; i++)
      {
        byte drawX = x + 39 + (i * 4);
        byte drawY = y + 9;

        byte w = 2;
        byte h = (i == 4) ? 4 : (i == 9) ? 7 : 2;

        ab.fillRect(drawX, drawY - h, w, h, WHITE);
      }
      for (byte i = 0; i < p[1].counter; i++)
      {
        byte drawX = x + 87 + (i * 4);
        byte drawY = y + 9;

        byte w = 2;
        byte h = (i == 4) ? 4 : (i == 9) ? 7 : 2;

        ab.fillRect(drawX, drawY - h, w, h, WHITE);
      }
    }

    void execute() {};

    virtual void upButton()
    {
      if (addValue(&p[cursor].counter, 10))
      {
        changeCounter++;
      }
    }

    virtual void downButton()
    {
      if (subValue(&p[cursor].counter, 0))
      {
        changeCounter--;
      }
    }

    virtual void leftButton()
    {
      changeCounter = 0;

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
      changeCounter = 0;
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
      changeCounter = 0;
      activeLife();
    }

    virtual void bButton() {}
    virtual void abButton()
    {
      initCounter();
    }

  private:

};

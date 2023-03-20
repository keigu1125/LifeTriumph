class DisplayDiscard : public Form
{
  private:
  public:
    byte hand = 7;
    byte discard = 2;
    byte card[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    DisplayDiscard()
    {
      x = 0;
      y = 43;
      w = 128;
      h = 11;
      // isCursor = false;
      // cursor = 0;
      cursorMax = 2;
      isEnable = setting.menuEnableDiscard;
      icon = i_discard;
    }

    void display()
    {
      ab.drawBitmap(x +  6, y + 1, i_s_hand, 9, 9, WHITE);
      ab.drawBitmap(x + 31, y + 1, i_s_down, 9, 9, WHITE);
      drawText(x + 15, y + 2, 1, hand);
      drawText(x + 40, y + 2, 1, discard);

      if (isCursor)
      {
        ab.drawRect(x, y, w, h, WHITE);
        drawArrowLeft(x + 2 + ((cursor == 0) ? 0 : 25), y + 2, WHITE);
      }

      if (!isDisp())
      {
        return;
      }

      for (byte i = 0; i < hand; i++)
      {
        ab.drawBitmap(x + 41 + (CARD_MAX - i) * 7, y + 1, (card[i] == 0) ? i_s_card : i_s_discard, 9, 9, WHITE);
      }
    }

    void execute()
    {
      initArray(card, CARD_MAX);
      byte dc = 0;
      while (dc < discard)
      {
        byte r = random(hand);
        if (card[r] == 0)
        {
          card[r] = 1;
          dc++;
        }
      }

      setTime();
    }

    virtual void upButton()
    {
      switch (cursor)
      {
        case 0:
          addValue(&hand, CARD_MAX);
          break;
        case 1:
          byte max = (DISCARD_MAX < hand) ? DISCARD_MAX : hand;
          addValue(&discard, max);
          break;
      }
    }

    virtual void downButton()
    {
      switch (cursor)
      {
        case 0:
          subValue(&hand, 1);
          if (hand < discard)
          {
            discard = hand;
          }
          break;
        case 1:
          subValue(&discard, 1);
          break;
      }
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
      execute();
    }

    virtual void abButton()
    {
      initArray(card, CARD_MAX);
    }

    virtual void udButton()
    {
      abButton();
    }

  private:

};

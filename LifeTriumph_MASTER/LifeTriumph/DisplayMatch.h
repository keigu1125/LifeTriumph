class DisplayMatch : public Form
{
  private:
    byte lx = life->x;
    byte ly = life->y;
    byte lw = life->w;
    byte lh = life->h;
    bool isMatching = false;
  public:
    byte cursorC = 0;
    byte cursorCMax = 2;

    DisplayMatch()
    {
      x = 0;
      y = 43;
      w = 128;
      h = 11;
      // isCursor = false;
      // cursor = 0;
      cursorMax = 1;
      isEnable = true;
      icon = i_match;
    }

    void display()
    {
      ab.drawRect(x, y, menu->w, h, WHITE);
      drawText((matchCount < 10 ) ? x + 5 : x + 2, y + 2, 1, "M " + String(matchCount));

      if (!isCursor)
      {
        return;
      }

      drawUtilForm(true);
      drawText(x + 50, y + 2, WHITE, getWinLoseDraw());
      drawText(x + 84, y + 2, WHITE, String(m_winCount) + "-" + m_loseCount + "-" + m_drawCount);

      ab.fillRect(lx, ly, lw, lh, BLACK);
      ab.drawRect(lx, ly, lw, lh, WHITE);

      byte row = 0;
      if (!isMatching)
      {
        drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, ">>Match");
        drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, "__Reset");
      }
      else
      {
        drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, "Win");
        drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, "Lose");
        drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, "Draw");
      }

      drawArrowLeft(lx + 3, ly + 5 + ((cursorC) * HIGHT), WHITE);
    }

    void execute()
    {
      activeUtil();
    }

    virtual void upButton()
    {
      if (!subValue(&cursorC, 0) && setting.menuRotate)
      {
        cursorC = cursorCMax - 1;
      }
    }

    virtual void downButton()
    {
      byte max = (setting.menuRotate) ? cursorCMax : cursorCMax - 1;
      addValue(&cursorC, max);

      if (cursorC >= cursorCMax && setting.menuRotate)
      {
        cursorC = 0;
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
      if (isCursor)
      {
        isCursorUtil = false;
        activeMenu();
        return;
      }

      changeCounter = 0;
      activeLife();
    }

    virtual void bButton()
    {
      if (!isCursor)
      {
        activeUtil();
        return;
      }

      switch (cursorC)
      {
        case 0:
          // Match
          if (!isMatching)
          {
            initMatch();
            time->execute();
            isMatching = true;
            cursorCMax = 3;
          }
          else
          {
            // Win
            g_his[gameCount] = MATCH_WIN;
            winCount++;
            gameCount++;
          }
          break;
        case 1:
          if (!isMatching)
          {
            // Reset
            initHist();
            return;
          }
          else
          {
            // Lose
            g_his[gameCount] = MATCH_LOSE;
            loseCount++;
            gameCount++;
          }
          break;
        case 2:
          if (!isMatching) {}
          else
          {
            // Draw
            g_his[gameCount] = MATCH_DRAW;
            drawCount++;
            gameCount++;
            break;
          }
      }

      if (winCount >= 2 || loseCount >= 2 || gameCount >= 3)
      {
        time->execute();

        if (winCount > loseCount)
        {
          m_winCount++;
          setting.sumMatchWin++;
        }
        else if (winCount < loseCount)
        {
          m_loseCount++;
          setting.sumMatchLose++;
        }
        else
        {
          m_drawCount++;
          setting.sumMatchDraw++;
        }

        setting.writeEepRomSetting();

        cursorC = 0;
        cursorCMax = 2;
        isMatching = false;
      }

      initGame();
      isCursorUtil = false;
      activeLife();
      isAlarm = setting.isLedTimer;
    }

    virtual void abButton()
    {
      // reset Match & Time
    }

  private:

    String getWinLoseDraw()
    {
      String s = "";
      for (int i = 0; i < MATCH_GAME_MAX; i++)
      {
        switch (g_his[i])
        {
          case 0:
            s = s + " ";
            break;
          case MATCH_WIN:
            s = s + "O";
            break;
          case MATCH_LOSE:
            s = s + "X";
            break;
          case MATCH_DRAW:
            s = s + "-";
            break;
        }
      }

      return s;
    }

};

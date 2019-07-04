class DisplayMatch : public Form
{
  private:
    byte lx = life->x;
    byte ly = life->y;
    byte lw = life->w;
    byte lh = life->h;
    bool isMatching = false;
    bool isShowHist = false;
  public:
    byte cursorC = 0;
    byte cursorCMax = 3;

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
      drawText((format->match < 10 ) ? x + 5 : x + 2, y + 2, 1, "M " + String(format->match));

      if (!isCursor)
      {
        return;
      }

      if (isShowHist)
      {
        ab.fillRect(0, 0, 128, 64, BLACK);
        ab.drawRect(0, 0, 128, 64, WHITE);

        byte row = 0;
        for (int i = 0; i < format->match; i++)
        {
          byte hisX = (i >= 14) ? 88 : (i >= 7) ? 44 : 4;
          drawText(hisX, 5 + ((row++ % 7)* HIGHT), 1, ((i + 1 < 10) ? " " + String(i + 1) : String(i + 1)) + " " + getWinLoseDraw(i));
        }

        return;
      }

      drawUtilForm(true);
      drawText(x + 50, y + 2, WHITE, getWinLoseDraw(format->match - 1));
      drawText(x + 84, y + 2, WHITE, String(format->m_win) + "-" + format->m_lose + "-" + format->m_draw);

      ab.fillRect(lx, ly, lw, lh, BLACK);
      ab.drawRect(lx, ly, lw, lh, WHITE);

      byte row = 0;
      if (!isMatching)
      {
        if (format->match >= MATCH_HIST_MAX)
        {
          drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, "*MatchHistMax*");
        }
        else
        {
          drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, ">>Match");
        }
        drawText(lx + 8, ly + 5 + (row++ * HIGHT), 1, "//Hist");
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
      if (!subValue(&cursorC, 0))
      {
        cursorC = cursorCMax - 1;
      }
    }

    virtual void downButton()
    {
      addValue(&cursorC, cursorCMax);

      if (cursorC >= cursorCMax)
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
      if (isShowHist)
      {
        isShowHist = false;
        return;
      }

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
      if (isShowHist)
      {
        isShowHist = false;
        return;
      }

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
            if (format->match >= MATCH_HIST_MAX)
            {
              return;
            }
            else
            {
              format->initMatch();
              time->execute();
              isMatching = true;
            }
          }
          else
          {
            // Win
            format->g_his[format->match - 1][format->game] = MATCH_WIN;
            format->win++;
            format->game++;
          }
          break;
        case 1:
          if (!isMatching)
          {
            // Hist
            isShowHist = true;
            return;
          }
          else
          {
            // Lose
            format->g_his[format->match - 1][format->game] = MATCH_LOSE;
            format->lose++;
            format->game++;
          }
          break;
        case 2:
          if (!isMatching)
          {
            // Reset
            format->initHist();
            return;
          }
          else
          {
            // Draw
            format->g_his[format->match - 1][format->game] = MATCH_DRAW;
            format->draw++;
            format->game++;
            break;
          }
      }

      if (format->win >= 2 || format->lose >= 2 || format->game >= 3)
      {
        time->execute();

        if (format->win > format->lose)
        {
          format->m_win++;
          setting.sumMatchWin++;
        }
        else if (format->win < format->lose)
        {
          format->m_lose++;
          setting.sumMatchLose++;
        }
        else
        {
          format->m_draw++;
          setting.sumMatchDraw++;
        }

        setting.writeEepRomSetting();
        
        cursorC = 0;
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

    String getWinLoseDraw(byte match)
    {
      String s = "";
      for (int i = 0; i < MATCH_GAME_MAX; i++)
      {
        switch (format->g_his[match][i])
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

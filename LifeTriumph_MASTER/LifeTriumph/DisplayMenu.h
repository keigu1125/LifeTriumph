class DisplayMenu : public Form
{
  private:
  public:
    DisplayMenu()
    {
      // x = 0;
      // y = 0;
      w = 27;
      h = 41;
      // isCursor = false;
      // cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;
    }

    void display()
    {
      ab.drawRect(x, y, w, h, WHITE);

      if (isCursor)
      {
        ab.drawRect(x + 1, y + 1, 25, 39, WHITE);
        if (setting.menuRotate || cursor != M_HEAD)
        {
          ab.drawBitmap(x + 8, y +  1, i_arrow_up, 11, 7, WHITE);
        }
        if (setting.menuRotate || cursor != M_TAIL)
        {
          ab.drawBitmap(x + 8, y + 32, i_arrow_down, 11, 7, WHITE);
        }
      }

      if (p[0].changeLife == 0 && p[1].changeLife == 0)
      {
        ab.drawBitmap(x + 8, y + 13, utils[cursor]->icon, MENU_ICON_SIZE_X, MENU_ICON_SIZE_Y, WHITE);
      }
      else
      {
        dispChangeLife();
      }

      switch (menu->cursor)
      {
        //case Menu::M_TIMER:
        case Menu::M_DICE:
        case Menu::M_LOG:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
          utils[cursor]->display();
          break;
        case Menu::M_SETTING:
          break;
      }
    }

    void execute() {};

    virtual void upButton()
    {
      if (setting.menuRotate && cursor == Menu::M_HEAD)
      {
        cursor = Menu::M_TAIL;
      }
      else
      {
        while (subValue(&cursor, Menu::M_HEAD) && !utils[cursor]->isEnable) {}
      }
    }

    virtual void downButton()
    {
      if (setting.menuRotate && cursor == Menu::M_TAIL)
      {
        cursor = Menu::M_HEAD;
      }
      else
      {
        while (addValue(&cursor, Menu::M_TAIL) && !utils[cursor]->isEnable) {}
      }
    }

    virtual void leftButton()
    {
      if (utils[cursor]->cursorMax == 0 || cursor == M_SETTING)
      {
        return;
      }

      utils[cursor]->cursor = utils[cursor]->cursorMax - 1;
      activeUtil();
    }

    virtual void rightButton()
    {
      if (utils[cursor]->cursorMax == 0 || cursor == M_SETTING)
      {
        return;
      }

      utils[cursor]->cursor = 0;
      activeUtil();
    }

    virtual void aButton()
    {
      activeLife();
    }

    virtual void bButton()
    {
      switch (cursor) {
        case Menu::M_TIMER:
        case Menu::M_DICE:
        case Menu::M_LOG:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
          utils[cursor]->execute();
          break;
        case Menu::M_SETTING:
          activeSetting();
          break;
      }
    }

    virtual void abButton()
    {
      switch (cursor) {
        case Menu::M_TIMER:
          if (!isTimer)
          {
            mTimer->abButton();
          }
          break;
        case Menu::M_DICE:
        case Menu::M_LOG:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
        case Menu::M_SETTING:
          break;
      }
    }

  private:
    void dispChangeLife()
    {
      if (p[0].changeLife == 0 && p[1].changeLife == 0)
      {
        return;
      }
      else if (p[0].changeLife != 0 && p[1].changeLife != 0)
      {
        for (byte i = 0; i < PLAYER_COUNT; i++)
        {
          short cl = p[i].changeLife;
          byte addX = (cl >= 100 || cl <= -100) ? 2 : (cl >= 10 || cl <= -10) ? 5 : 8;
          byte addY = 12 + (i * 9);
          drawText(x + addX, y + addY, 1, (cl > 0) ? "+" + String(cl) : cl);
        }
      }
      else
      {
        short cl = 0;
        if (p[0].changeLife == 0)
        {
          cl = p[1].changeLife;
        }
        else
        {
          cl = p[0].changeLife;
        }
        byte addX = (cl >= 100 || cl <= -100) ? 2 : (cl >= 10 || cl <= -10) ? 5 : 8;
        byte addY = 17;
        drawText(x + addX, y + addY, 1, (cl > 0) ? "+" + String(cl) : cl);
      }
    }

};

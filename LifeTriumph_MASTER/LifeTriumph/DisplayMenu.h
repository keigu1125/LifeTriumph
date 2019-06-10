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
        if (cursor != M_HEAD)
        {
          ab.drawBitmap(x + 8, y +  1, i_arrow_up, 11, 7, WHITE);
        }
        if (cursor != M_TAIL)
        {
          ab.drawBitmap(x + 8, y + 32, i_arrow_down, 11, 7, WHITE);
        }
      }

      if (changeLife == 0)
      {
        ab.drawBitmap(x + 8, y + 13, utils[cursor]->icon, MENU_ICON_SIZE_X, MENU_ICON_SIZE_Y, WHITE);
      }
      else
      {
        dispChangeLife();
      }

      switch (menu->cursor)
      {
        case Menu::M_MATCH:
        case Menu::M_DICE:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
        case Menu::M_COUNT:
          utils[cursor]->display();
          break;
        case Menu::M_SETTING:
          break;
      }
    }

    void execute() {};

    virtual void upButton()
    {
      while (subValue(&cursor, Menu::M_HEAD) && !utils[cursor]->isEnable) {}
    }

    virtual void downButton()
    {
      while (addValue(&cursor, Menu::M_TAIL) && !utils[cursor]->isEnable) {}
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
        case Menu::M_MATCH:
        case Menu::M_DICE:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
        case Menu::M_COUNT:
          utils[cursor]->execute();
          break;
        case Menu::M_SETTING:
          activeSetting();
          break;
      }
    }

    virtual void abButton() {}

  private:
    void dispChangeLife()
    {
      if (changeLife == 0)
      {
        return;
      }

      byte addX = (changeLife >= 100 || changeLife <= -100) ? 2 : (changeLife >= 10 || changeLife <= -10) ? 5 : 8;
      byte addY = 17;
      drawText(x + addX, y + addY, 1, (changeLife > 0) ? "+" + String(changeLife) : changeLife);
    }

};

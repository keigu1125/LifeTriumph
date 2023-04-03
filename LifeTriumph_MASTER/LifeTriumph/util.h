bool someButtonPressed()
{
  return (ab.pressed(UP_BUTTON)   || ab.pressed(DOWN_BUTTON)  ||
          ab.pressed(LEFT_BUTTON) || ab.pressed(RIGHT_BUTTON) ||
          ab.pressed(A_BUTTON)    || ab.pressed(B_BUTTON));
}

bool abButtonPressed()
{
  return (ab.pressed(A_BUTTON)    || ab.pressed(B_BUTTON));
}

bool upDownButtonPressed()
{
  return (ab.pressed(UP_BUTTON) || ab.pressed(DOWN_BUTTON));
}

bool rotateUp(byte* target, byte min, byte max)
{
  if (*target == max)
  {
    *target = min;
    return false;
  }
  else
  {
    (*target)++;
    return true;
  }
}

bool rotateDown(byte* target, byte min, byte max)
{
  if (*target == min)
  {
    *target = max;
    return false;
  }
  else
  {
    (*target)--;
    return true;
  }
}

bool addValue(byte* target, byte max)
{
  if (*target <= max - 1)
  {
    (*target)++;
    return true;
  }
  return false;
}

bool subValue(byte* target, byte min)
{
  if (*target >= min + 1)
  {
    (*target)--;
    return true;
  }
  return false;
}

void initArray(byte* ar, byte size)
{
  for (byte i = 0; i < size; i++)
  {
    ar[i] = 0;
  }
}

void initArray(byte** ar, byte size_2, byte size_1)
{
  for (byte i = 0; i < size_2; i++)
  {
    initArray(ar[i], size_1);
  }
}

byte getHour(long l)
{
  if (l < 0)
  {
    l *= -1;
  }

  return (byte)(l / 1000 / 3600);
}

byte getMinute(long l)
{
  if (l < 0)
  {
    l *= -1;
  }

  return (byte)(l / 1000 / 60 % 60);
}

byte getSecond(long l)
{
  if (l < 0)
  {
    l *= -1;
  }

  return (byte)(l / 1000 % 60);
}

bool isOverTime(long l)
{
  return (l / 1000 % 60) < 0;
}

String getHMS(long lStop)
{
  bool isMinus = isOverTime(lStop);
  byte h = getHour(lStop);
  byte m = getMinute(lStop);
  byte s = getSecond(lStop);

  return ((isMinus) ? "-" : " ") + String(h) + ":" + ((m < 10) ? "0" + String(m) : String(m)) + ":" + ((s < 10) ? "0" + String(s) : String(s));
}

void drawArrowLeft(byte x, byte y, bool white)
{
  ab.drawLine(x + 0, y + 0, x + 0, y + 6, white);
  ab.drawLine(x + 1, y + 1, x + 1, y + 5, white);
  ab.drawLine(x + 2, y + 2, x + 2, y + 4, white);
  ab.drawLine(x + 3, y + 3, x + 3, y + 3, white);
}

void drawArrowTop(byte x, byte y, bool white)
{
  ab.drawLine(x + 3, y + 0, x + 3, y + 0, white);
  ab.drawLine(x + 2, y + 1, x + 4, y + 1, white);
  ab.drawLine(x + 1, y + 2, x + 5, y + 2, white);
  ab.drawLine(x + 0, y + 3, x + 6, y + 3, white);
}

void drawArrowDown(byte x, byte y, bool white)
{
  ab.drawLine(x + 3, y + 3, x + 3, y + 3, white);
  ab.drawLine(x + 2, y + 2, x + 4, y + 2, white);
  ab.drawLine(x + 1, y + 1, x + 5, y + 1, white);
  ab.drawLine(x + 0, y + 0, x + 6, y + 0, white);
}

void drawText(byte a, byte b, byte fs, String mes)
{
  ab.setCursor(a, b);
  ab.setTextSize(fs);
  ab.print(mes);
}

void drawText(byte a, byte b, byte fs, int mes)
{
  ab.setCursor(a, b);
  ab.setTextSize(fs);
  ab.print(mes);
}

void drawText(byte a, byte b, byte fs, char* mes)
{
  ab.setCursor(a, b);
  ab.setTextSize(fs);
  ab.print(mes);
}

void drawTextInvert(byte a, byte b, byte fs, int num)
{
  bool isMinus = (num < 0);
  char str[10] = {0};
  int i = 0;

  if (isMinus)
  {
    num *= -1;
  }

  do
  {
    str[i++] = num % 10 + 0x10;
    num /= 10;
  }
  while (num > 0);

  if (isMinus)
  {
    str[i++] = '-';
  }
  str[i] = '\0';

  drawText(a, b, fs, str);
}

void drawText(byte a, byte b, byte fs, int num, bool isInvert)
{
  if (isInvert)
  {
    drawTextInvert(a, b, fs, num);
  }
  else
  {
    drawText(a, b, fs, num);
  }
}

void drawBigDice(byte x, byte y, byte number)
{
  if (number == 0)
  {
    return;
  }

  ab.fillRect(x, y, 8, 8, WHITE);

  if (number == 6)
  {
    ab.drawRect(x + 1, y + 0, 2, 2, BLACK);
    ab.drawRect(x + 1, y + 3, 2, 2, BLACK);
    ab.drawRect(x + 1, y + 6, 2, 2, BLACK);
    ab.drawRect(x + 5, y + 0, 2, 2, BLACK);
    ab.drawRect(x + 5, y + 3, 2, 2, BLACK);
    ab.drawRect(x + 5, y + 6, 2, 2, BLACK);
  }
  else
  {
    if (number & 0x01)
    {
      ab.drawRect(x + 3, y + 3, 2, 2, BLACK);
    }
    if (number >= 2)
    {
      ab.drawRect(x + 5, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 5, 2, 2, BLACK);
    }
    if (number >= 4)
    {
      ab.drawRect(x + 1, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 5, 2, 2, BLACK);
    }
  }
}

char* getBlackWhite(byte value)
{
  return value == 0x00 ? "BLACK" : "WHITE";
}

char* getOnOff(byte value)
{
  return value == 0x00 ? "OFF" : "0N";
}

char* getMenuName(byte value)
{
  switch (value)
  {
    case Menu::M_TIMER:
      return "Timer";
    case Menu::M_DICE:
      return "Dice";
    case Menu::M_LOG:
      return "Log";
    case Menu::M_DISCARD:
      return "Discard";
    case Menu::M_STORM:
      return "Storn";
    case Menu::M_SETTING:
      return "Setting";
  }
}

void activeMenu()
{
  menu->isCursor = !isCursorUtil;
  life->isCursor = false;
  utils[menu->cursor]->isCursor = isCursorUtil;
  sett->isCursor = false;
}

void activeLife()
{
  menu->isCursor = false;
  life->isCursor = true;
  utils[menu->cursor]->isCursor = false;
  sett->isCursor = false;
}

void activeUtil()
{
  menu->isCursor = false;
  life->isCursor = false;
  utils[menu->cursor]->isCursor = true;
  sett->isCursor = false;

  isCursorUtil = true;
}

void activeSetting()
{
  menu->isCursor = false;
  life->isCursor = false;
  utils[menu->cursor]->isCursor = false;
  sett->isCursor = true;
}

void setXY(byte pC, byte x, byte y, byte w, byte h)
{
  p[pC].x = x;
  p[pC].y = y;
  p[pC].w = w;
  p[pC].h = h;
}

void initPlayerLife()
{
  for (auto& pl : p)
  {
    pl.life = 20;
    pl.changeLife = 0;
    pl.logCount = 0;
    for (auto& log : pl.lifeLog)
    {
      log = 0;
    }
  }
}

void initMode()
{
  pCount = 2;
  setXY(0,  0,  0, 48, 41);
  setXY(1, 48,  0, 48, 41);
  p[0].invert = false;
  p[1].invert = setting.invertOpponent;

  initPlayerLife();
}

void initMenuSelect()
{
  if (setting.isWritedSetting == DEF_IS_WRITE_SETTING && utils[setting.menuDefault]->isEnable)
  {
    menu->cursor = setting.menuDefault;
  }
}

void slideArray(short* ar, byte size)
{
  for (byte i = 0; i < size - 1; i++)
  {
    ar[i] = ar[i + 1];
  }

  ar[size - 1] = 0;
}

void saveChangeLife()
{
  for (auto& pl : p)
  {
    short cl = pl.changeLife;
    if (cl == 0)
    {
      continue;
    }

    if (pl.logCount >= CHANGE_LIFE_LOG)
    {
      slideArray(pl.lifeLog, CHANGE_LIFE_LOG);
    }

    if (pl.logCount < CHANGE_LIFE_LOG)
    {
      pl.logCount++;
    }

    pl.lifeLog[pl.logCount - 1] = pl.life + (cl * -1);
    pl.changeLife = 0;
  }
}

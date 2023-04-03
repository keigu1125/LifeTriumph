#include "Arduboy.h"
#include "globalVariant.h"
#include "util.h"
#include "DisplayMenu.h"
#include "DisplayLife.h"
#include "DisplayTime.h"
#include "DisplayLog.h"
#include "DisplayDice.h"
#include "DisplayDiscard.h"
#include "DisplayStorm.h"
#include "DisplaySetting.h"

void setup()
{
  init();
  ab.beginNoLogo();
  ab.setRGBled(0, 0, 0);
  ab.initRandomSeed();

  setting.readEepRomSetting();

  menu = new DisplayMenu();
  life = new DisplayLife();
  mTimer = new DisplayTime();
  dice = new DisplayDice();
  mLog = new DisplayLog();
  discard = new DisplayDiscard();
  storm = new DisplayStorm();
  sett = new DisplaySetting();

  utils[0] = mTimer;
  utils[1] = dice;
  utils[2] = mLog;
  utils[3] = discard;
  utils[4] = storm;
  utils[5] = sett;

  ab.setFrameRate(setting.frameRateMain);
  ab.invert(setting.blackScreen);
  isTitle = (setting.showTitle);
  isMain = !isTitle;
  isEnableAlarm = (setting.isLedTimer || setting.isSoundTimer);
  tStop = setting.timerDefaultMin * 60000;
  initMode();
  initMenuSelect();

  // **FOR Arduboy EEPROM INITIALIZE**
  if (ab.pressed(DOWN_BUTTON))
  {
    activeSetting();
  }
  else
  {
    //activeMenu();
    activeLife();
  }
}

void loop()
{
  if (!(ab.nextFrame()))
  {
    return;
  }
  ab.clear();
  disp();
  ab.display();
  button();
  fpsSetting();
}

void disp()
{
  if (sett->isCursor)
  {
    sett->display();
  }
  else if (isMain)
  {
    mTimer->display();
    life->display();
    menu->display();
  }
  else if (isTitle)
  {
    dispTitle();
  }
}

void fpsSetting()
{
  if (tPressed == 0)
  {
    ab.setFrameRate(setting.frameRateSleep);
  }
  else
  {
    ab.setFrameRate(setting.frameRateMain);
  }
}

void dispTitle()
{
  if (isTitle && millis() > TIME_TITLE)
  {
    isTitle = false;
    isMain = true;
  }

  ab.drawBitmap(0, 0, phy_logo, 128, 64, WHITE);
  // ab.drawBitmap(0, 0, blue_footed_booby_logo, 128, 64, WHITE);
  drawText(80, 55, 1, APP_VER);
}

void button()
{
  if (!someButtonPressed())
  {
    pressFirst = true;
    pressPole = false;
    if (tPressed + DISP_RESET_SECOND < millis())
    {
      tPressed = 0;
      saveChangeLife();
    }
    return;
  }

  if (!allowButtonPress())
  {
    return;
  }

  if (pressFirst)
  {
    pressFirst = false;
    tPressed = millis() + BUTTON_REPEAT;
  }
  else
  {
    tPressed = millis();
  }

  if (isTitle)
  {
    isTitle = false;
    isMain = true;
    return;
  }

  pressButton();
  buttonSound();
}

bool allowButtonPress()
{
  return pressFirst || (!pressPole && (tPressed < millis()));
}

void buttonSound()
{
  if (!setting.isSoundKeyPress)
  {
    return;
  }

  int t1 = setting.baseTone;
  if (life->isCursor)
  {
    int l = p[life->cursor].life;
    t1 += (l >= 100) ? (TONE_ONELIFE * 80) : (l <= -20) ? (TONE_ONELIFE * -40) : ((l - 20) * TONE_ONELIFE);
  }
  ab.tunes.tone(t1, 20);
}

Form* setActiveForm()
{
  Form* activeForm = NULL;

  if (menu->isCursor)
  {
    activeForm = menu;
  }
  else if (life->isCursor)
  {
    activeForm = life;
  }
  else if (utils[menu->cursor]->isCursor)
  {
    activeForm = utils[menu->cursor];
  }
  else if (sett->isCursor)
  {
    activeForm = sett;
  }

  return activeForm;
}

void pressButton()
{
  Form* activeForm = setActiveForm();

  if (activeForm == NULL)
  {
    return;
  }

  if (ab.pressed(UP_BUTTON) && ab.pressed(DOWN_BUTTON))
  {
    activeForm->udButton();
  }
  else if (ab.pressed(UP_BUTTON))
  {
    activeForm->upButton();
  }
  else if (ab.pressed(DOWN_BUTTON))
  {
    activeForm->downButton();
  }
  else if (ab.pressed(LEFT_BUTTON))
  {
    activeForm->leftButton();
  }
  else if (ab.pressed(RIGHT_BUTTON))
  {
    activeForm->rightButton();
  }

  if (ab.pressed(A_BUTTON) && ab.pressed(B_BUTTON))
  {
    activeForm->abButton();
  }
  else if (ab.pressed(A_BUTTON))
  {
    activeForm->aButton();
  }
  else if (ab.pressed(B_BUTTON))
  {
    activeForm->bButton();
  }
}

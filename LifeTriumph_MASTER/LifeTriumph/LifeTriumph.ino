#include "Arduboy.h"
#include "globalVariant.h"
#include "util.h"
#include "DisplayMenu.h"
#include "DisplayLife.h"
#include "DisplayTime.h"
#include "DisplayMatch.h"
#include "DisplayDice.h"
#include "DisplayDiscard.h"
#include "DisplayStorm.h"
#include "DisplayCounter.h"
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
  time = new DisplayTime();
  match = new DisplayMatch();
  dice = new DisplayDice();
  discard = new DisplayDiscard();
  storm = new DisplayStorm();
  counter = new DisplayCounter();
  sett = new DisplaySetting();

  utils[0] = match;
  utils[1] = dice;
  utils[2] = discard;
  utils[3] = storm;
  utils[4] = counter;
  utils[5] = sett;

  format = new Format();

  initMode();
  ab.setFrameRate(setting.frameRateMain);
  ab.invert(setting.blackScreen);
  isTitle = (setting.showTitle);
  isMain = !isTitle;
  isInvertOpponent = (setting.invertOpponent);
  tStop = setting.timerDefaultMin * 60000;
  
  activeMenu();
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
    time->display();
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
    return;
  }

  ab.drawBitmap(0, 0, mtg_logo, 128, 64, WHITE);
}

void button()
{
  if (!someButtonPressed())
  {
    pressFirst = true;
    if (tPressed + DISP_RESET_SECOND < millis())
    {
      tPressed = 0;
      changeLife = 0;
      changeCounter = 0;
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
}

bool allowButtonPress()
{
  return (pressFirst || tPressed < millis());
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

  if (ab.pressed(UP_BUTTON))
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

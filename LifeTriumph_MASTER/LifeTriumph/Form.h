class Form
{
  public:
    byte x = 0;
    byte y = 0;
    byte w = 0;
    byte h = 0;
    byte cursor = 0;
    byte cursorMax = 0;
    bool isCursor = false;
    bool isEnable = true;
    long tPressed = 0;
    char* icon = NULL;

    virtual void display() = 0;
    virtual void execute() = 0;
    virtual void upButton() = 0;
    virtual void downButton() = 0;
    virtual void leftButton() = 0;
    virtual void rightButton() = 0;
    virtual void aButton() = 0;
    virtual void bButton() = 0;
    virtual void abButton() = 0;

    void setTime()
    {
      this->tPressed = millis();
    }

    bool isDisp()
    {
      if (this->tPressed + DISP_RESET_SECOND < millis())
      {
        this->tPressed = 0;
      }

      return this->tPressed != 0;
    }
};

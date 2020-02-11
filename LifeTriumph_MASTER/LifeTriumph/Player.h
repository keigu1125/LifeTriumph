struct Player
{
  public:
    byte x = 0;
    byte y = 0;
    byte w = 0;
    byte h = 0;
    int life = 0;
    short changeLife = 0;
    short lifeLog[CHANGE_LIFE_LOG];
    byte logCount = 0;
    bool invert = false;
};

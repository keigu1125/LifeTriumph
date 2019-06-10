class Format
{
  public:
    byte match = 0;
    byte game = 0;
    byte win = 0;
    byte lose = 0;
    byte draw = 0;
    byte m_win = 0;
    byte m_lose = 0;
    byte m_draw = 0;

    byte g_his[MATCH_HIST_MAX][MATCH_GAME_MAX];

    void initMatch()
    {
      match++;
      game = 0;
      win = 0;
      lose = 0;
      draw = 0;
    }

    void initHist()
    {
      m_win = 0;
      m_lose = 0;
      m_draw = 0;
      match = 0;
      for (int i = 0; i < MATCH_HIST_MAX; i++)
      {
        for (int j = 0; j < MATCH_GAME_MAX; j++)
        {
          g_his[i][j] = 0;
        }
      }
    }
};

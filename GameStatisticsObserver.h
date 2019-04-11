#pragma once

#include "Game.h"
using namespace std;
class GameStatisticsObserver
{
  private:
    Game *game;
  public:
    GameStatisticsObserver(Game *game);
    void update();
  };

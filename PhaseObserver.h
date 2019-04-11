#pragma once

#include "Game.h"
using namespace std;
class PhaseObserver{
private:
  Game *game;
public:
  PhaseObserver(Game *game);
  void update();
};

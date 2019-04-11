#pragma once
#include "Observer.h"
#include "Game.h"
using namespace std;
class PhaseObserver : public Observer{
private:
  Game *game;
public:
  PhaseObserver(Game *game);
  void update();
};

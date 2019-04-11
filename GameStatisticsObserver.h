#include "Observer.h"
#include "Game.h"
using namespace std;
class  GameStatisticsObserver : public Observer{
  private:
    Game *game;
  public:
    GameStatisticsObserver(Game *game);
    void update();
  };

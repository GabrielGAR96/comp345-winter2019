#include "Observer.h"
#include "Game.h"
using namespace std;
class  GameStatisticsObserver : public Observer{
  private:
    Game *game;
  public:
    GameStatisticsObserver(Game *game){
      game = game;
    }
    void update(){
      for(int i=0;i<game->getNumPlayers();i++){
        cout<<"Player = " << game->getPlayer(i).getColor()<<endl;
        cout<< "Current location = "<<game->getPlayer(i).getCurrentCity()<<endl;
        cout<<"Citites = ";
        for(int i=0;i<game->getPlayer(i).getNumCities();i++)
          cout<<"* ";
        cout<<endl;
        cout<< "OIL: "<<game->getCurrentPlayer().getOil();
        cout<< "COAL: "<<game->getCurrentPlayer().getCoal();
        cout<< "GARBAGE: "<<game->getCurrentPlayer().getGarbage();
        cout<< "URANIUM: "<<game->getCurrentPlayer().getUranium();
      }
    }
};

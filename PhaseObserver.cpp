
#include "Game.h"
#include "PhaseObserver.h"
using namespace std;


  PhaseObserver::PhaseObserver(Game *game){
    this->game = game;
  }
  void PhaseObserver::update(){
    if(game->getPhase()==1){
      cout<<"----------------------------------------------"<<endl;
      cout<<"-------------------PHASE 1--------------------"<<endl;
      cout<<"----------------------------------------------"<<endl;
      cout<<"PLAYER ORDER : "<<game->getPlayerOrder();

    }
    if(game->getPhase()==2){
      cout<<"----------------------------------------------"<<endl;
      cout<<"-------------------PHASE 2--------------------"<<endl;
      cout<<"----------------------------------------------"<<endl;
      cout<<"PLAYER: " << game->getCurrentPlayer().getColor()<<endl;
      cout<<"ELEKTRO: "<<game->getCurrentPlayer().getMoney()<<endl;
    }
    if(game->getPhase()==3){
      cout<<"----------------------------------------------"<<endl;
      cout<<"-------------------PHASE 3--------------------"<<endl;
      cout<<"----------------------------------------------"<<endl;
      cout<<"PLAYER: " << game->getCurrentPlayer().getColor()<<endl;
      cout<<"ELEKTRO: "<<game->getCurrentPlayer().getMoney()<<endl;
      cout<< "OIL: "<<game->getCurrentPlayer().getOil();
      cout<< "COAL: "<<game->getCurrentPlayer().getCoal();
      cout<< "GARBAGE: "<<game->getCurrentPlayer().getGarbage();
      cout<< "URANIUM: "<<game->getCurrentPlayer().getUranium();

    }
    if(game->getPhase()==4){
      cout<<"----------------------------------------------"<<endl;
      cout<<"-------------------PHASE 4--------------------"<<endl;
      cout<<"----------------------------------------------"<<endl;
      cout<<"PLAYER: " << game->getCurrentPlayer().getColor()<<endl;
      cout<<"ELEKTRO: "<<game->getCurrentPlayer().getMoney()<<endl;
      cout<<"CITIES: "<<game->getCurrentPlayer().getNumCities()<<endl;

    }
    if(game->getPhase()==5){
      cout<<"----------------------------------------------"<<endl;
      cout<<"-------------------PHASE 5--------------------"<<endl;
      cout<<"----------------------------------------------"<<endl;
      cout<<"PLAYER: " << game->getCurrentPlayer().getColor()<<endl;
      cout<<"ELEKTRO: "<<game->getCurrentPlayer().getMoney()<<endl;
      cout<<"CITITES: "<<game->getCurrentPlayer().getNumCities()<<endl;
      cout<< "OIL: "<<game->getCurrentPlayer().getOil();
      cout<< "COAL: "<<game->getCurrentPlayer().getCoal();
      cout<< "GARBAGE: "<<game->getCurrentPlayer().getGarbage();
      cout<< "URANIUM: "<<game->getCurrentPlayer().getUranium();
    }
  }

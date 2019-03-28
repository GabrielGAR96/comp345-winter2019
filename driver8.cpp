#include "PowerplantCard.h"
#include "Player.h"
#include "Resource.h"
#include "Map.h"
using namespace std;

/*
      THIS DRIVER IMPLEMENTS PHASE 5 OF THE game


      NEEDED TO COMPILE   -Card.cpp  -HouseColor.cpp  -Player.cpp  -Resource.cpp


      micheal:

      no nothing in the phase 5 needs to be modified in this one, the only thing missing is
      the resupplying of the resource market way at the end, i couldnt find gabriels files but
      all we need to add is his card swap at the end that removes last card and replaces from one from the deck


*/

//method to delete a specific resource from a player, removing it from the first card found
bool deleteCardResources(Player& player, Resource resource){
    //loops through all cards and once it finds the resource entered it will delete it from the card
    for(int i=0;i<player.getCardCounter();i++){
      PowerplantCard& card = player.getCard(i);
//condition for  card needing 1 resource
      if(card.getResourceTypeSize()==1){
        Resource cardresource = getResourceByName(player.getCard(i).getResource1());
        if(resource==cardresource){
          card.reduceR1();
          card.reducecurrentStored();
          return true;
        }
      }
      //condition for card using 2 diff resources
      if(card.getResourceTypeSize()==2){
        Resource cardresource1 = getResourceByName(player.getCard(i).getResource1());
        Resource cardresource2 = getResourceByName(player.getCard(i).getResource1());
        if(resource==cardresource1){
          card.reduceR1();
          card.reducecurrentStored();
          return true;
        }
        if(resource==cardresource2){
          card.reduceR2();
          card.reducecurrentStored();
          return true;
        }
      }
    }
}






//method to set players money depending on how many housese he is powering
int bureaucracy(Player& player, int poweredHouses){
  switch(poweredHouses){
      case 0 : player.setMoney(10);return 10; break;
      case 1 : player.setMoney(22);return 22; break;
      case 2 : player.setMoney(33);return 33; break;
      case 3 : player.setMoney(44);return 44; break;
      case 4 : player.setMoney(54);return 54; break;
      case 5 : player.setMoney(64);return 64; break;
      case 6 : player.setMoney(73);return 73; break;
      case 7 : player.setMoney(82);return 82; break;
      case 8 : player.setMoney(90);return 90; break;
      case 9 : player.setMoney(98);return 98; break;
      case 10 : player.setMoney(105);return 105; break;
      case 11 : player.setMoney(112);return 112; break;
      case 12 : player.setMoney(118);return 118; break;
      case 13 : player.setMoney(124);return 124; break;
      case 14 : player.setMoney(129);return 129; break;
      case 15 : player.setMoney(134);return 134; break;
      case 16 : player.setMoney(138);return 138; break;
      case 17 : player.setMoney(142);return 142; break;
      case 18 : player.setMoney(145);return 145;break;
      case 19 : player.setMoney(148);return 148; break;
      case 20 : player.setMoney(150);return 150; break;
  }
}

//this is the method for phase 5, it takes in a player obj and runs throug that specific players turn
int phase5(Player& player){
  int poweredCities=0;      //number of cities being powered
  cout<<player.getColor()<<"\'s turn!"<<endl;
  cout<<"\nWould you like to power Cities? 1-YES 0-NO"<<endl;
      int choice;
      cin>>choice;
      //player chooses what he wants to do
      while(!(choice==0||choice==1)){
        cout<<"\nPlease enter a valid choice!\n"<<endl;
        cin>>choice;
      }

      if(choice==0){
        cout<<"Exiting powering phase!......"<<endl;
        return poweredCities;
      }
  //main loop looping through the choice of cards for powering cities
  while(true){
  cout<<"Cities currently being powered: "<<poweredCities<<endl;
  cout<<"\nYou currently own:\n"<<endl;
  cout<<"RESOURCES: "<<endl;
  player.getTotResources();
  cout<<"\nCARDS:\n"<<endl;
  cout<<player.getCards()<<endl;
  cout<<"What powerplant would you like to use to power your cities? Press 1 for card 1....or Press 9 to exit"<<endl;
  //choice player makes
  int cardChoice;
  cin>>cardChoice;
  if(cardChoice==9){
    cout<<"\n\n.....Exiting powering phase....."<<endl;
    return poweredCities;
  }
  while(cardChoice<1||cardChoice>player.getCardCounter()){
    cout<<"Please enter a valid card! Enter 1 for first card 2 for second card or 3 for third card"<<endl;
    cout<<"Or enter 9 to exit resouce buying phase.\n";
    cin>>cardChoice;
    if(cardChoice==9){
      cout<<"\n\n.....Exiting powering phase.....\n"<<endl;
      return poweredCities;
    }
  }
  //powerplantcard is the card being tested here
  PowerplantCard& powerplant = player.getCard(cardChoice-1);

  if(powerplant.getPowering())
    cout<<"\nThis powerplant is already powering cities!!\n"<<endl;

  else{
    //condition if card is economic
  if(powerplant.getResourceTypeSize()==0){
    poweredCities += powerplant.getPowerable();
    powerplant.setpowering(true);
  }
  //condition if card can store one type of resource
  if(powerplant.getResourceTypeSize()==1){
    Resource resource = getResourceByName(powerplant.getResource1());
    if(powerplant.getNeeded()>player.findNumResource(resource))
      cout<<"Not enough resources to power this card..."<<endl;
    else{
      cout<<"\nBurining resources..."<<endl;
      cout<<"Powering cities......\n"<<endl;
      for(int i=0;i<powerplant.getNeeded();i++){
        player.deleteResource(resource);
        powerplant.reducecurrentStored();
        deleteCardResources(player, resource);
      }
      poweredCities += powerplant.getPowerable();
      powerplant.setpowering(true);
    }
  }
  //condtition if card can store 2 types of resources
  if(powerplant.getResourceTypeSize()==2){
    Resource resource1 = getResourceByName(powerplant.getResource1());
    Resource resource2 = getResourceByName(powerplant.getResource2());
    if(powerplant.getNeeded()>(player.findNumResource(resource1)+player.findNumResource(resource2)))
      cout<<"Not enough resources to power this card..."<<endl;
    else{
        int needed = powerplant.getNeeded();
        //here is a loop where player needs to choose which resource he would like to use to power is plant
        while(needed != 0){
          cout<<"\nWhat resource would you like to use to power your powerplant?"<<endl;

          cout<<"Press 1: "<<powerplant.getResource1()<<" = "<<player.findNumResource(resource1)<<endl;
          cout<<"Press 2: "<<powerplant.getResource2()<<" = "<<player.findNumResource(resource2)<<endl;
          int resourcechoice;
          cin>>resourcechoice;
          while(!(resourcechoice==1||resourcechoice==2)){
            cout<<"Please enter a valid choice: ";
            cin>>resourcechoice;
          }
          if(resourcechoice==1){
            if(player.findNumResource(resource1)==0)
              cout<<"\nYou do not have any of this resource!";
            else{
              player.deleteResource(resource1);
              powerplant.reducecurrentStored();
              deleteCardResources(player, resource1);
              needed--;
            }
          }
          if(resourcechoice==2){
            if(player.findNumResource(resource2)==0)
              cout<<"\nYou do not have any of this resource!";
            else{
              player.deleteResource(resource2);
              powerplant.reducecurrentStored();
              deleteCardResources(player, resource2);
              needed--;
            }
          }
    }
    //adding cities being powered
    poweredCities += powerplant.getPowerable();
    powerplant.setpowering(true);
  }
  }
}}
}

int main(){

  //creating 2 players to test phase 3
  Player p1 = Player(BLACK);
  Player p2 = Player(RED);
  int PLAYERS = 2;
  Player players[PLAYERS];
  players[0] = p1;
  players[1] = p2;
  //creating random cards for players to use
  PowerplantCard c1 = PowerplantCard(4, 2, 0);
  PowerplantCard c2 = PowerplantCard(7, 2, 2, OIL);
  PowerplantCard c3 = PowerplantCard(8, 2, 3, GARBAGE, URANIUM);
  PowerplantCard c4 = PowerplantCard(4, 2, 1, GARBAGE);
  PowerplantCard c5 = PowerplantCard(4, 2, 2, COAL);
  //buying the random cards all at price 1
  players[0].purchaseCard(c1,30);
  players[0].purchaseCard(c2,1);
  players[0].purchaseCard(c3,1);
  players[1].purchaseCard(c4,1);
  players[1].purchaseCard(c5,1);
  //adding random resources to player to test the phase
  players[0].addResource(OIL);
  players[0].addResource(OIL);
  players[0].addResource(OIL);
  players[1].addResource(GARBAGE);
  players[1].addResource(GARBAGE);
  players[1].addResource(GARBAGE);
  players[1].addResource(COAL);

  cout<<"----------------POWERING CITIES---------------------\n\n";
  //looping through players to go throug phase 5 and ouput the amount of $ earned after each player ends his turn
  for(Player& player : players){
    int powering = phase5(player);
    cout<<"\n"<<player.getColor()<< "\'s ELEKTRO: "<<player.getMoney()<<endl;
    if(powering>player.getHouses()){
      cout<<"Houses powered: "<< player.getHouses()<<endl;
      cout<<"Earns: $"<< bureaucracy(player, player.getHouses())<<endl;
      cout<<player.getColor()<< "\'s new ELEKTRO: "<<player.getMoney()<<"\n"<<endl;
    }
    else{
      cout<<"Houses powered: "<< powering <<endl;
      cout<<"Earns: $"<< bureaucracy(player, powering)<<endl;
      cout<<player.getColor()<< "\'s new ELEKTRO: "<<player.getMoney()<<"\n"<<endl;
    }
  }
  //outputting player info at the end of phase 3
  cout<<"Players posessions after phase 3:\n"<<endl;
  for(int i=PLAYERS-1;i>=0;i--){
    cout<<"--------------------------------------------------"<<endl;
    players[i].toString();
  }


  cout<<"\n\n--------------------------------------------------------------------------------"<<endl;
  cout<<"Resupplying resource market..........................."<<endl;
  ////////////////////////////////
  //add market resupply method here
  ////////////////////////////
  cout<<"Removing Card from market and replacing it............"<<endl;
  ///////////////////////////
  //add last card swap here (i cant find it)
  //////////////////////////
  cout<<"--------------------------------------------------------------------------------"<<endl;









}

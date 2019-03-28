#include "Player.h"
#include "Resource.h"
#include "Map.h"
#include "PowerplantCard.h"

/*

THIS DRIVER IS USED TO SHOW PHASE 3 OF PART 3 OF THE GAME


NEEDED TO COMPILE   -Card.cpp  -HouseColor.cpp  -Player.cpp  -Resource.cpp

Micheal :

in the phase 3 method there is only the finding market price for specifc resource
and the removal of a specific resource all commented

there are no modifications to do in the DRIVER


*/

//this is the whole method for phase 3
bool phase3(Player& player){
cout << player.getColor()<<"\'s turn:\n"<<endl;
while(true){

  if(player.getMoney()<1){
    cout<<"Not enough Elektro to buy resources!!\n......Exiting resource buying phase.......";
    return false;
  }

  //condition for buying resources
  cout<<"Would you like to buy resouces? 1-YES 0-NO\n";
  int choice=-1;
  cin>>choice;
  while (!(choice==0 || choice== 1)){
    cout<<"Enter a valid choice!: \n";
    cin>>choice;
  }
  if(choice==0){
    return false;
  }
  //output user info and asks him what he wants to do
  cout << "\nResources owned: \n";
  player.getTotResources();
  cout<<"\nAvalable Elektro: $"<<player.getMoney();
  cout<<"\n\nWhat card would you like to buy resources for? (Press 1 for first....)\n\n";
  cout<<player.getCards();
  int cardChoice= -1;
  cin>>cardChoice; //choice player made for a card
  //loop condition if no correct choice
  while(cardChoice<1||cardChoice>player.getCardCounter()){
    cout<<"Please enter a valid card! Enter 1 for first card 2 for second card or 3 for third card"<<endl;
    cout<<"Or enter 9 to exit resouce buying phase.\n";
    cin>>cardChoice;
    if(cardChoice==9){
      cout<<"\n\n.....Exiting resource buying phase.....\n"<<endl;
      return false;
    }
  }
  //ouputting players choice
  cout<<"\n\nCard selected:\n\n ";
  cout<<player.getCard(cardChoice-1).info()<<endl;
  cout<<"\nCurrently stores:\n\n";
  cout<<player.getCard(cardChoice-1).getCurrentStored()<<" "<<player.getCard(cardChoice-1).getResources();
  cout<<"\n\nAvalable to buy:\n\n";
  int avalable = (player.getCard(cardChoice-1).getNeeded()*2) - player.getCard(cardChoice-1).getCurrentStored();
  cout<< avalable <<" "<< player.getCard(cardChoice-1).getResources();

//this loop loops throug the specific card for buying resources until card is full or player leaves loop
  while(true){


///////////////////////////
//micheal:
  // Resourse r1 =  getResourceByName(player.getCard(cardChoice-1).getResource1());
  // Resource r2 = getResourceByName(player.getCard(cardChoice-1).getResource2());
  //
   int marketPrice=1;
   int marketPrice2=2;
////////////////////////////////////

//conditions depending on cards avalability for buying resources
  if(avalable==0){
    cout<<"\nThis card cannot store any more resouces\nReturning to card selection....."<<endl;
    break;
  }
//checks if player has enough money
  else if(player.getMoney()<marketPrice){
    cout<<"\nYou do not have enough Elektro to buy this Resource\n"<<endl;
    break;
  }
//if player has enough money will loop through askiing player to buy
  else{
    cout<<"\n\nAvalable Elektro: $"<<player.getMoney()<<endl;
  //condition if card only requires 1 resource to power
    if(player.getCard(cardChoice-1).getResourceTypeSize()==1){
    cout<<"Current cheapest "<<player.getCard(cardChoice-1).getResources()<<" is: $"<<marketPrice<<endl;
    cout<<"Would you like to buy it? 1-YES 0-NO\n";
    int buy=0;
    cin>>buy;
    while(!(buy==1||buy==0)){
      cout<<"\nNot a valid choice, please try again.....\n";
      cin>>buy;
    }
    if(buy==0)
      break;

    player.buyResource(cardChoice-1, getResourceByName(player.getCard(cardChoice-1).getResource1()), 1, marketPrice);
    avalable--;
    ////////////////////////
    //micheal:
    //remove resource 1 from resource pools
    //r1
    ///////////////////////
  }
  //condition if card requires 2 resources, player has to choose which resource he would like to use
  else{
    cout<<"Current cheapest "<<player.getCard(cardChoice-1).getResource1()<<" is: $"<<marketPrice<<endl;
    cout<<"Current cheapest "<<player.getCard(cardChoice-1).getResource2()<<" is: $"<<marketPrice2<<endl;
    cout<<"Would you like to buy? 1-"<<player.getCard(cardChoice-1).getResource1()<<" 2-"<<player.getCard(cardChoice-1).getResource2()<< " 0-NO\n";
    int buy=0;
    cin>>buy;
    while(!(buy==1||buy==0||buy==2)){
      cout<<"\nNot a valid choice, please try again.....\n";
      cin>>buy;
    }
    if(buy==0)
      break;
    else if(buy==1){
      player.buyResource(cardChoice-1, getResourceByName(player.getCard(cardChoice-1).getResource1()), 1, marketPrice);
      avalable--;
      ////////////////////////
      //micheal:
      //remove resource 1 from resource pools
      //r1
      ///////////////////////
    }
    else{
    player.buyResource(cardChoice-1, getResourceByName(player.getCard(cardChoice-1).getResource2()), 1, marketPrice);
    avalable--;
    /////////////////////////
    //micheal:
    //remove resource 2 from resource pools
    //r2
    ///////////////////////
    }
  }

}
}
}return true;
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

cout<<"---------------------------BUYING RESOURCE PHASE-------------------------"<<endl;
//loop through players using phse 3 method
for(int i=PLAYERS-1;i>=0;i--){
  phase3(players[i]);
}

//outputting player info at the end of phase 3
cout<<"Players posessions after phase 3:\n"<<endl;
for(int i=PLAYERS-1;i>=0;i--){
  cout<<"--------------------------------------------------"<<endl;
  players[i].toString();
}


}

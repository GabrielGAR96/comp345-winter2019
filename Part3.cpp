#include<string>
#include<iostream>
#include <vector>
#include "PowerplantCard.h"
#include "Player.h"
#include "Resource.h"
using namespace std;

//gets the reverse player order from the initial order.
//
// int* getReversePlayerOrder(int* playerOrder[], int numPlayers){
//   int* revOrder[numPlayers];
//   int ini = 0;
//   for (int i=numPlayers-1;i>=0;i--){
//     *revOrder[ini] = *playerOrder[i];
//     ini++;
//   }
//   return *revOrder;
// }

int bureaucracy(Player player, int poweredHouses){
  switch(poweredHouses){
      case 0 : player.setMoney(10); break;
      case 1 : player.setMoney(22); break;
      case 2 : player.setMoney(33); break;
      case 3 : player.setMoney(44); break;
      case 4 : player.setMoney(54); break;
      case 5 : player.setMoney(64); break;
      case 6 : player.setMoney(73); break;
      case 7 : player.setMoney(82); break;
      case 8 : player.setMoney(90); break;
      case 9 : player.setMoney(98); break;
      case 10 : player.setMoney(105); break;
      case 11 : player.setMoney(112); break;
      case 12 : player.setMoney(118); break;
      case 13 : player.setMoney(124); break;
      case 14 : player.setMoney(129); break;
      case 15 : player.setMoney(134); break;
      case 16 : player.setMoney(138); break;
      case 17 : player.setMoney(142); break;
      case 18 : player.setMoney(145); break;
      case 19 : player.setMoney(148); break;
      case 20 : player.setMoney(150); break;
  }
}

//
//
//
//
//
//
//
// void Phase3(Player *players, int numPlayers){
//
//   for(int i=0;i<numPlayers;i++){
//     //cout << players[i].getColor<<"\'s turn"<<endl;
//     cout<<"Your current info:"<<endl;
//   //  cout<<player[i].toString<<endl;
// }
//
Resource chosenResource(int num){
  switch(num){
    case(1):
    return OIL;
    case(2):
    return GARBAGE;
    case(0):
    return COAL;
    case(3):
    return URANIUM;

  }
}


//add in condition for 2 resource cards
bool phase3(Player player){


cout << player.getColor()<<"\'s turn:\n"<<endl;
while(true){

  if(player.getMoney()<1){
    cout<<"Not enough Elektro to buy resources!!\n......Exiting resource buying phase.......";
    return false;
  }
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
  cout << "\nResources owned: \n";
  player.getTotResources();
  cout<<"\nAvalable Elektro: $"<<player.getMoney();
  cout<<"\n\nWhat card would you like to buy resources for? (Press 1 for first....)\n\n";
  cout<<player.getCards();
  int cardChoice= -1;
  cin>>cardChoice;
  while(cardChoice<1||cardChoice>player.getCardCounter()){
    cout<<"Please enter a valid card! Enter 1 for first card 2 for second card or 3 for third card"<<endl;
    cout<<"Or enter 9 to exit resouce buying phase.\n";
    cin>>cardChoice;
    if(cardChoice==9){
      cout<<"\n\n.....Exiting resource buying phase.....";
      return false;
    }
  }
  cout<<"\n\nCard selected:\n\n ";
  cout<<player.getCard(cardChoice-1).info()<<endl;
  cout<<"\nCurrently stores:\n\n";
  cout<<player.getCard(cardChoice-1).getCurrentStored()<<" "<<player.getCard(cardChoice-1).getResources();
  cout<<"\n\nAvalable to buy:\n\n";
  int avalable = (player.getCard(cardChoice-1).getNeeded()*2) - player.getCard(cardChoice-1).getCurrentStored();
  cout<< avalable <<" "<< player.getCard(cardChoice-1).getResources();


  while(true){


  int marketPrice=1; //add market price method
  int marketPrice2=2;


  if(avalable==0){
    cout<<"\nThis card cannot store any more resouces\nReturning to card selection....."<<endl;
    break;
  }

  else if(player.getMoney()<marketPrice){
    cout<<"\nYou do not have enough Elektro to buy this Resource\n"<<endl;
    break;
  }

  else{
    cout<<"\n\nAvalable Elektro: $"<<player.getMoney()<<endl;
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
  }
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
    }
    else{
    player.buyResource(cardChoice-1, getResourceByName(player.getCard(cardChoice-1).getResource2()), 1, marketPrice);
    avalable--;
    }
  }

  }

    //add method to remove from market
}}return true;
}

bool powerableCard(Player player, PowerplantCard card){
  int needed = card.getNeeded();
  if(card.getResourceTypeSize()==2){
  Resource R1 = getResourceByName(card.getResource1());
  Resource R2 = getResourceByName(card.getResource2());
  int current = 0;
  int storedResource1 = player.findNumResource(R1);
  int storedResource2 = player.findNumResource(R1);
  if(storedResource1+storedResource2>=needed)
    return true;
  return false;
}
else{
  Resource R1 = getResourceByName(card.getResource1());
  int storedResource1 = player.findNumResource(R1);
  if(storedResource1>=needed)
    return true;
  return false;
  }
}
void burnResource(Player& p, Resource r){

  p.deleteResource(r);
  for(int i=0;i<p.getCardCounter();i++){
    if(p.getCard(i).getResource1()==getResourceName(r)){
      p.getCard(i).reduceR1();
      p.getCard(i).reducecurrentStored();
      break;
    }
    if(p.getCard(i).getR2()==r){
      p.getCard(i).reduceR2();
      p.getCard(i).reducecurrentStored();
      break;
    }
  }
}

bool phase5(Player player){
  int poweredCities=0;
    cout<<player.getColor()<<"\'s turn\n"<<endl;

    while (true) {
    cout<<"You currently own:\n"<<endl;

    cout<<"RESOURCES: "<<endl;
    player.getTotResources();
    cout<<"\nCARDS:\n"<<endl;
    cout<<player.getCards();
    cout<<"\nWould you like to power Cities? 1-YES 0-NO"<<endl;
    int choice;
    cin>>choice;
    while(!(choice==0||choice==1)){
      cout<<"\nPlease enter a valid choice!\n"<<endl;
      cin>>choice;
    }
    if(choice==0){
      cout<<"Exiting powering phase!......"<<endl;
      return false;
    }

    cout<<"Which power plant card would you like to use to power cities? Press 1 for first 2 for second......\n"<<endl;
    cout<<player.getCards()<<endl;
    int cardChoice;
    PowerplantCard card = player.getCard(cardChoice);
    cin>>cardChoice;
    while(cardChoice<1||cardChoice>player.getCardCounter()){
       cout<<"Please enter a valid card! Enter 1 for first card 2 for second card or 3 for third card"<<endl;
       cout<<"Or enter 9 to exit resouce buying phase.\n";
       cin>>cardChoice;
       if(cardChoice==9){
         cout<<"\n\n.....Exiting powering phase....."<<endl;
         return false;
       }
     }
    if(!powerableCard(player,card))
      cout<<"You do not have enough RESOURCES to power this card......\n"<<endl;
    else{
      if(card.getResourceTypeSize()==1){
        poweredCities += card.getPowerable();
        cout<<"\nCities being powered: "<<poweredCities<<"\n"<<endl;
        for(int i=0;i<card.getNeeded();i++)
          burnResource(player, getResourceByName(card.getResource1()));


      }

    }




  }
}


int main(){
//
// Player p1(RED);
// Player p2(BLUE);
// // Setup new player
Player player(BLACK);
// cout << "Player 1 has been created...." << '\n';
// cout << "\nPlayer 1:" << '\n';
//
// // Print new player info (should be pretty boring)
// player1.toString();
//
// // Initialize player items (Powerplants, Resources, etc)
PowerplantCard card(17, 2, 1, URANIUM);
PowerplantCard card2(7, 2, 1, GARBAGE);
PowerplantCard card3(1, 2, 1, COAL, OIL);
// cout << "\nAdding a card to player...\n";
player.purchaseCard(card, 17);
player.purchaseCard(card2, 5);
player.purchaseCard(card3, 1);


Resource u = URANIUM;
Resource g = GARBAGE;
Resource g2 = GARBAGE;
Resource u2 = URANIUM;
Resource c1 = COAL;
Resource c2 = COAL;
// cout << "Buying resources for player..." << endl;


player.buyResource(0, u, 1, 1);
player.buyResource(1, g2, 2, 2);

// cout<<"R1: ";
// cout<<player.getCard(0).getR1()<<endl;
// cout<<"curent stored: ";
// cout<<player.getCard(0).getCurrentStored()<<endl;
// player.getTotResources();
//
//
// burnResource(player, URANIUM);
//
// //player.getCard(0).reduceR1();
// cout<<"\nafter burn: ";
// cout<<player.getCard(0).getR1()<<endl;
// cout<<"current strored: ";
// cout<<player.getCard(0).getCurrentStored()<<endl;
// player.getTotResources();
// //bureaucracyPhase(player);


//phase3(player);


phase5(player);



}

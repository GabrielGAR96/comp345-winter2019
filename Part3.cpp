#include<string>
#include<iostream>
#include <vector>
#include "PowerplantCard.h"
#include "Player.h"
#include "Resource.h"
using namespace std;

//gets the reverse player order from the initial order.
// int* getReversePlayerOrder(int* playerOrder[], int numPlayers){
//   int* revOrder[numPlayers];
//   int ini = 0;
//   for (int i=numPlayers-1;i>=0;i--){
//     *revOrder[ini] = *playerOrder[i];
//     ini++;
//   }
//   return *revOrder;
// }
//
// int bureacracy(Player player, int poweredHouses){
//   switch(poweredHouses){
//       case 0 : player.setMoney(10); break;
//       case 1 : player.setMoney(22); break;
//       case 2 : player.setMoney(33); break;
//       case 3 : player.setMoney(44); break;
//       case 4 : player.setMoney(54); break;
//       case 5 : player.setMoney(64); break;
//       case 6 : player.setMoney(73); break;
//       case 7 : player.setMoney(82); break;
//       case 8 : player.setMoney(90); break;
//       case 9 : player.setMoney(98); break;
//       case 10 : player.setMoney(105); break;
//       case 11 : player.setMoney(112); break;
//       case 12 : player.setMoney(118); break;
//       case 13 : player.setMoney(124); break;
//       case 14 : player.setMoney(129); break;
//       case 15 : player.setMoney(134); break;
//       case 16 : player.setMoney(138); break;
//       case 17 : player.setMoney(142); break;
//       case 18 : player.setMoney(145); break;
//       case 19 : player.setMoney(148); break;
//       case 20 : player.setMoney(150); break;
//   }
// }
//
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
    case(3):
    return COAL;
    case(4):
    return URANIUM;

  }
}






int main(){

Player p1(RED);
Player p2(BLUE);
// Setup new player
Player player1(BLACK);
cout << "Player 1 has been created...." << '\n';
cout << "\nPlayer 1:" << '\n';

// Print new player info (should be pretty boring)
player1.toString();

// Initialize player items (Powerplants, Resources, etc)
PowerplantCard card(17, 2, 1, URANIUM);
cout << "\nAdding a card to player...\n";
player1.purchaseCard(card, 17);

cout << "Buying resources for player..." << endl;
player1.buyResource(0, URANIUM, 1, 10);

cout << "Buying City for player....\n";
player1.buyCities("Montreal");
cout << "\nPlayer 1:" << '\n';

// Print player should now have items
player1.toString();


Player players[2]={player1, p2};

cout<<"RESOURCE BUYING PHASE!"<<endl;
cout<<"\n"<<players[0].getColor()<<"\'s turn:\nAvalable: "<<players[0].getMoney()<<endl;  //fix loop players[i]
int loop=-1;

while(loop != 0){
  int card;
  cout<<"\nWhat Card would you like to buy resouces for?\nCARDS:\n"<<players[0].getCards()<<endl;
  cin>>card;
  cout<<"\nRESORCES:\n"<<endl;
  players[0].getTotResources();
  cout<< "\nPress to buy:\n1-OIL\n2-GARBAGE\n3-COAL\n4-URANIUM\n0-exit\nAVALABLE: $" << players[0].getMoney()<<endl;
  cin>>loop;
  if(loop==0)
    break;
  Resource buying = chosenResource(loop);
  cout<<"How many would you like to buy?\n";
  int amount=0;
  cin>>amount;
  players[0].buyResource(card, buying, amount, 10);
  }
}

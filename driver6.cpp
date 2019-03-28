#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "Player.h"
#include "PowerplantCard.h"
#include "HouseColor.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    Player player1(BLACK);
    cout << "Player 1 has been created...." << '\n';
    cout << "\nPlayer 1:" << '\n';
    player1.toString();

    Player player2(RED);
    cout << "Player 2 has been created...." << '\n';
    cout << "\nPlayer 2:" << '\n';
    player2.toString();
    Player player3(BLUE);
    Player player4(YELLOW);
    Player player5(GREEN);
    Player player6(PURPLE);

    PowerplantCard card(17, 2, 1, URANIUM);
    PowerplantCard card2(18, 2, 0);
    PowerplantCard card3(19, 3, 2, GARBAGE);
    PowerplantCard card4(20, 5, 3, COAL);
    PowerplantCard card5(21, 4, 2, OIL, COAL);
    PowerplantCard card6(22, 2, 0);
    PowerplantCard card7(23, 3, 1, URANIUM);
    PowerplantCard card8(24, 4, 2, GARBAGE);
    PowerplantCard card9(25, 5, 2, COAL);
    PowerplantCard card10(26, 5, 2, OIL);
    PowerplantCard card11(27, 3, 0);
    PowerplantCard card12(28, 4, 1, URANIUM);
    PowerplantCard card13(29, 4, 1, OIL, COAL);
    PowerplantCard card14(30, 6, 3, GARBAGE);


    cout << "\nAdding a card to player...\n";
    player1.purchaseCard(card, 17);
    cout << "Buying resources for player..." << endl;
    player1.buyResource(0, URANIUM, 1, 10);
    cout << "Buying City for player....\n";
    player1.buyCities("Montreal");
    cout << "\nPlayer 1:" << '\n';
    player1.buyCities("");
    player1.toString();




    cout << "Game:" << endl;
    Game game;
    cout << endl;
    cout << endl;
    cout << "Phase: " << game.GetPhase() << endl;

    cout <<" Step: " <<  game.GetStep() << endl;
    cout << "Phase: " << game.GetPhase() << endl;
    game.AddPlayer(player1);
    game.AddPlayer(player2);
    game.AddPlayer(player3);
    game.AddPlayer(player4);
    game.AddPlayer(player5);
    game.AddPlayer(player6);
    game.AddPowerplant(card);
    game.AddPowerplant(card2);
    game.AddPowerplant(card3);
    game.AddPowerplant(card4);
    game.AddPowerplant(card5);
    game.AddPowerplant(card6);
    game.AddPowerplant(card7);
    game.AddPowerplant(card8);
    game.AddPowerplant(card9);
    game.AddPowerplant(card10);
    game.AddPowerplant(card11);
    game.AddPowerplant(card12);
    game.AddPowerplant(card13);
    game.AddPowerplant(card14);

    cout <<"Size of Player: " << game.GetPlayers().size() << endl;
    cout << endl;
    for(Player p : game.GetPlayers()){
    p.toString();
    }
    //cout << game.GetCurrentPlayer() << endl;
    for(Player p : game.GetPlayers()){
    p.toString();
    }

    //game.SetPlayerOrder();
    cout << endl;
    cout << endl;

    game.NewGame();


    return 0;
}

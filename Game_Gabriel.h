//
// Created by Gabriel Albuquerque Ribeiro on 2019-03-19.
//

#ifndef COMP345_WINTER2019_GOOD_BRANCH_GAME_H
#define COMP345_WINTER2019_GOOD_BRANCH_GAME_H

#include <map>
#include "Player.h"
#include "PowerplantCard.h"
#include "Elektro.h"

class Game {
private:
    static const int MAX_PLAYERS = 6;

    int fullTurn;  // the number of turns since the beginning
    vector<Player> players;
    Player* currentPlayer;
    vector<PowerplantCard> powerplantCards;
    PowerplantCard* currentCard;
    int phase;
    int playPhase;

public:
    Game(){}
    void Pass();

    vector<Player> GetPlayers(){return players;}
    bool AddPlayer(Player player);
    void AddPowerplant(PowerplantCard powerplantCard);
    void GetPowerplantCards();
    int GetPhase() const { return phase; }
    int GetStep() const { return playPhase; }
    int CountMapFalse();

    //phase 1
    void NewGame();
    void UpdatePlayOrder(bool);
    void Phase1Start();

    //phase 2
    void Phase2Start();
    void Phase2StartBid();
    void Phase2Bid();
    int counter;
    bool firstTurn;
    bool nowBidding;
    void NextPlayer();
    void Phase2End();
    int currentBid;
    int plantIndex;
    std::map<Player*, bool> canBid;
    std::map<Player*, bool> canBuy;
    Player *highestBidder;

};


#endif //COMP345_WINTER2019_GOOD_BRANCH_GAME_H

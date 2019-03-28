#ifndef GAME_H
#define GAME_H

#include <map>
#include <unordered_map>
#include <string>
using namespace std;

#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "PowerplantMarket.h"
#include "PowerplantCard.h"
#include "Elektro.h"

class Game
{

    private:
        static const int MAX_PLAYERS = 6;

        int fullTurn;  // the number of turns since the beginning
        vector<Player> players;
        Player* currentPlayer;
        vector<PowerplantCard> powerplantCards;
        PowerplantCard* currentCard;
        int phase;
        int playPhase;

        /* vector<Player> players; */
        int step = 1;
        Map* board;
        Deck deck;
        PowerplantMarket powerPlants;

        static void readDirectory(const string& name, map<int, string>& files);
        static Map* selectMap(map<int, string>& files);
        static int selectNumberOfPlayers();
        static void selectPlayerColor(int i, unordered_map<string, HouseColor>& colors, vector<Player>& players);
        static void selectRegion(int i, Map* powergrid);
        static void setupPlayers(int numPlayers, unordered_map<string, HouseColor>& colors, vector<Player>& players, Map* powergrid);

    public:
        Game(vector<Player>& players, Map* board);
        ~Game();

        void restockMarket();
        string playerInfo();

        static Game* buildGame();

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
        map<Player*, bool> canBid;
        map<Player*, bool> canBuy;
        Player *highestBidder;
};
/* #ifndef COMP345_WINTER2019_GOOD_BRANCH_GAME_H */
/* #define COMP345_WINTER2019_GOOD_BRANCH_GAME_H */

/* class Game { */
/* private: */
/*     static const int MAX_PLAYERS = 6; */

/*     int fullTurn;  // the number of turns since the beginning */
/*     vector<Player> players; */
/*     Player* currentPlayer; */
/*     vector<PowerplantCard> powerplantCards; */
/*     PowerplantCard* currentCard; */
/*     int phase; */
/*     int playPhase; */

/* public: */
/*     Game(){} */
/*     void Pass(); */

/*     vector<Player> GetPlayers(){return players;} */
/*     bool AddPlayer(Player player); */
/*     void AddPowerplant(PowerplantCard powerplantCard); */
/*     void GetPowerplantCards(); */
/*     int GetPhase() const { return phase; } */
/*     int GetStep() const { return playPhase; } */
/*     int CountMapFalse(); */

/*     //phase 1 */
/*     void NewGame(); */
/*     void UpdatePlayOrder(bool); */
/*     void Phase1Start(); */

/*     //phase 2 */
/*     void Phase2Start(); */
/*     void Phase2StartBid(); */
/*     void Phase2Bid(); */
/*     int counter; */
/*     bool firstTurn; */
/*     bool nowBidding; */
/*     void NextPlayer(); */
/*     void Phase2End(); */
/*     int currentBid; */
/*     int plantIndex; */
/*     std::map<Player*, bool> canBid; */
/*     std::map<Player*, bool> canBuy; */
/*     Player *highestBidder; */

/* >>>>>>> gabriel-branch */
/* }; */


#endif

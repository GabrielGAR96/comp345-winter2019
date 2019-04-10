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
#include "Elektro.h"
#include "Card.h"

class Game
{

    private:
        static const int PAYOUT[21];

        vector<Player> players;
        int step = 1;
        bool firstRound = true;
        Map* board;
        PowerplantCard* cards;
        Step3Card s3Card;
        Deck deck;
        PowerplantMarket powerPlants;
        int currentPlayerIndex = 0;
        bool auctioning;

        /* static void readDirectory(const string& name, map<int, string>& files); */
        static Map* selectMap(map<int, string>& files);
        static int selectNumberOfPlayers();
        static void selectPlayerColor(int i, unordered_map<string, HouseColor>& colors, vector<Player>& players);
        static void selectRegion(int i, Map* powergrid);
        static void setupPlayers(int numPlayers, unordered_map<string, HouseColor>& colors, vector<Player>& players, Map* powergrid);

    public:
        Game();
        Game(vector<Player>& players, Map* board);
        ~Game();

        Player& getCurrentPlayer();
        PowerplantMarket& getMarket();
        int getStep() const;

        bool isFirstRound() const;

        void phase1();


        void phase2();

        bool auctionStarted() const;
        void setAuctionStarted(bool auctioning);

        void phase3();
        void phase4();
        void phase5();

        Map& getMap();
        void restockMarket();
        string gameInfo();

        static Game* buildGame();
        PowerplantCard* loadCards();

};

#endif

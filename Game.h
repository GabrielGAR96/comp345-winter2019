#ifndef GAME_H
#define GAME_H

#include <map>
#include <unordered_map>
#include <string>

#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "PowerplantMarket.h"

class Game
{

    private:
        vector<Player> players;
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
};


#endif

#ifndef GAME_H
#define GAME_H

#include "Map.h"

class Game
{
    public:
        int numPlayers;
        int step = 1;
        Map board;

        Game(int numPlayers, Map& board);

        void restockMarket();
};


#endif

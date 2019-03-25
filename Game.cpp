#include "Game.h"

Game::Game(int numPlayers, Map& board)
    : numPlayers(numPlayers), board(board)
{}

void Game::restockMarket()
{
    board.restockMarket(numPlayers, step);
}

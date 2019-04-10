#include "Game.h"

int main(int argc, char *argv[])
{
    Game* game = Game::buildGame();
    game->phase1();
    game->phase2();
    game->phase3();
    game->phase4();
    game->phase5();
    delete game;
    return 0;
}

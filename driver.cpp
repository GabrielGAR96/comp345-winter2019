
#include "Game.h"
#include "Subject.h"
#include "PhaseObserver.h"
#include "GameStatisticsObserver.h"

int main(int argc, char *argv[])
{

    Game* game = Game::buildGame();
    PhaseObserver po (game);
    //GameStatisticsObserver gso(game);

    game->Attach(&po);
    //game->Attach(gso);

    game->phase1();
    game->phase2();
    game->phase3();
    game->phase4();
    game->phase5();
    delete game;
    return 0;
}

#include <iostream>
using namespace std;

#include "Strategy.h"
#include "Game.h"
#include "Player.h"

Strategy::~Strategy()
{
}

HumanStrategy::~HumanStrategy()
{
}

HumanStrategy* HumanStrategy::clone()
{
    return new HumanStrategy(*this);
}

void HumanStrategy::auction(Game& game)
{
    bool iStarted = false;
    if(!game.auctionStarted()) {
        while(!iStarted) {
            cout << game.getMarket().getActualMarket();
            char response = 'n';
            cout << "PLAYER " << game.getCurrentPlayer().getColor() << endl;
            if(game.isFirstRound()) {
                response = 'y';
                cout << "You must pick a card to auction" << endl;
            } else {
                while(true) {
                    cout << "Would you like to auction a card (y/N): ";
                    cin >> response;
                    response = (char)tolower(response);
                    if(response == 'y' || response == 'n') break;
                    else cout << "Invalid response... Please try again" << endl;
                }
            }
            if(response == 'y') {
                int selection;
                cout << "PLAYER " << game.getCurrentPlayer().getColor() << endl;
                while(true) {
                    cout << "Which card would you like to bid on (1-4, 0 to cancel, 5 to show market): ";
                    cin >> selection;
                    if(selection >= 1 && selection <= 4) {
                        game.setAuctionStarted(true);
                        game.getMarket().setAuctioningCard(selection - 1);
                        iStarted = true;
                        break;
                    } else if(selection == 5) cout << game.getMarket().getActualMarket();
                    else if(selection == 0) {
                        if(game.isFirstRound()) break;
                        else {
                            game.getCurrentPlayer().pass();
                            return;
                        }
                    } else cout << "Invalid selection... Please try again" << endl;
                }
            } else {
                game.getCurrentPlayer().pass();
                return;
            }
        }
    }
    int currentBid = game.getMarket().getCurrentBid();
    int maxBid = game.getCurrentPlayer().getMoney();
    if(maxBid < currentBid) {
        game.getCurrentPlayer().disallowBidding();
        return;
    }
    int bid;
    cout << "PLAYER " << game.getCurrentPlayer().getColor() << endl;
    while(true) {
        cout << "AUCTIONING:" << endl;
        cout << game.getMarket().getAuctioningCard().info() << endl << endl;
        cout << "How much would you like to bid (minimum " << currentBid + 1;
        if(iStarted) cout << "): ";
        else cout << ", 0 to pass): ";
        cin >> bid;
        if(bid > currentBid) {
            game.getMarket().setCurrentBid(bid);
            break;
        } else if(bid == 0) {
            if(iStarted) cout << "You must bid because you started this auction" << endl;
            else {
                game.getCurrentPlayer().disallowBidding();
                return;
            }
        } else cout << "Invalid bid... Please try again" << endl;
    }
}

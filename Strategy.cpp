#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
using namespace std;

#include "Strategy.h"
#include "Resource.h"
#include "Game.h"
#include "Player.h"
#include "HouseColor.h"
#include "City.h"
#include "Graph.h"

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
                cout << "PLAYER " << getHouseColorName(game.getCurrentPlayer().getColor()) << endl;
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
    cout << "PLAYER " << getHouseColorName(game.getCurrentPlayer().getColor()) << endl;
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

bool HumanStrategy::purchaseResources(Game& game)
{
    cout << game.getMap().getResourceMarket().toString() << endl << endl;
    cout << game.getCurrentPlayer().info() << endl << endl;
    char response = 'n';
    while(true) {
        cout << "Would you like to buy resources (y/N): ";
        cin >> response;
        response = (char)tolower(response);
        if(response == 'y' || response == 'n') break;
        else cout << "Invalid response... Please try again" << endl;
    }
    if(response == 'n') return false;
    string rStr;
    Resource r;
    int allowedToStore;
    while(true) {
        cout << "What type of resource do you want to buy: ";
        cin >> rStr;
        try {
            r = getResourceByName(rStr);
            allowedToStore = game.getCurrentPlayer().allowedToStore(r);
            if(allowedToStore == 0) {
                cout << "You cannot store this type of resource." << endl;
                continue;
            }
            break;
        } catch(int i) {
            cout << "Invalid input... Please try again" << endl;
        }
    }
    int inMarket = game.getMap().getResourceMarket().getAmount(r);
    int upper = min(allowedToStore, inMarket);
    int amount;
    while(true) {
        cout << "How many " + rStr + "s do you want to buy (1-" + to_string(upper) + ", 0 cancels): ";
        cin >> amount;
        if(amount == 0) break;
        if(amount < 1 || amount > allowedToStore) {
            cout << "Invalid amount... Please try again" << endl;
        } else {
            int price = game.getMap().getResourceMarket().getPrice(r, amount);
            int money = game.getCurrentPlayer().getMoney();
            if(price > money) {
                cout << "Insufficent funds... Please try again" << endl;
            } else {
                response = 'y';
                while(true) {
                    cout << "Buying " + to_string(amount) + " " + rStr + " for $" + to_string(price) + " (Y/n)? ";
                    cin >> response;
                    response = (char)tolower(response);
                    if(response == 'y' || response == 'n') break;
                    else cout << "Invalid response... Please try again" << endl;
                }
                if(response == 'n') return true;
                game.getMap().getResourceMarket().buy(r, amount);
                game.getCurrentPlayer().buyResources(r, amount, price);
                break;
            }
        }
    }
    if(amount == 0) return true;
    response = 'n';
    while(true) {
        cout << "Would you like to continue to buy resources (y/N): ";
        cin >> response;
        response = (char)tolower(response);
        if(response == 'y' || response == 'n') break;
        else cout << "Invalid response... Please try again" << endl;
        break;
    }
    if(response == 'y') return true;
    else return false;
}

bool HumanStrategy::purchaseCities(Game& game)
{
    Player& currentPlayer = game.getCurrentPlayer();
    char response = 'n';
    while(true) {
        cout << "Player " << getHouseColorName(currentPlayer.getColor()) << endl;
        cout << "Would you like to buy cities (y/N): ";
        cin >> response;
        response = (char)tolower(response);
        if(response == 'y' || response == 'n') break;
        else cout << "Invalid response... Please try again" << endl;
    }
    if(response == 'n') return false;
    unordered_set<City> cities = game.getMap().getCities();
    string location;
    City city;
    int connCost = 0;
    if(currentPlayer.getNumCities() == 0) {
        for(City city : cities) {
            cout << city << endl;
        }
        cout << endl;
        cout << "Where do you want to build? ";
        cin >> location;
        auto cityPtr = cities.find(City(location, 0));

        if(cityPtr != cities.end()) {
            city = *cityPtr;
            int occupants = city.getNumOccupants();
            if(occupants == game.getStep()) {
                cout << "Cannot currently build here... Try again" << endl;
                return true;
            }
        } else {
            cout << "Invalid selection... Try again!" << endl;
            return true;
        }
    } else {
        vector<string> playerCities = currentPlayer.getCities();
        unordered_set<City> playerNetwork;
        for(string city : playerCities) {
            cout << city << endl;
            playerNetwork.insert(City(city, 0));
        }
        cout << endl;
        cout << "Which of your cities do you want to build from? ";
        cin >> location;
        auto cityPtr = playerNetwork.find(City(location, 0));
        if(cityPtr == playerNetwork.end()) {
            cout << "Invalid selection.. Try again" << endl;
            return false;
        }
        vector<Edge<City> > connections = game.getMap().getNeighbors(*cityPtr);
        unordered_map<City, double> destinations;
        for(Edge<City> edge : connections) {
            destinations.insert({edge.dest, edge.cost});
        }
        while(true) {
            cout << "Where do you want to build? ";
            cin >> location;
            auto cityPtr = destinations.find(City(location, 0));

            if(cityPtr != destinations.end()) {
                city = cityPtr->first;
                connCost = cityPtr->second;
                int occupants = city.getNumOccupants();
                if(occupants == game.getStep()) {
                    cout << "Cannot currently build here... Try again" << endl;
                    continue;
                }
            } else {
                cout << "Invalid selection... Try again!" << endl;
                continue;
            }
            break;
        }
    }
    if(city.getPrice() + connCost > currentPlayer.getMoney()) {
        cout << "You cannot afford to build here" << endl;
        return true;
    }
    cout << endl;
    cout << "Building at " << city.getName() << " for $" << (city.getPrice() + connCost) << endl;
    House currentHouse = House(game.getCurrentPlayer().getColor());
    game.getMap().buyCity(city, currentHouse);
    currentPlayer.buyCity(city.getName(), city.getPrice() + connCost);
    return false;
}

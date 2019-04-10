#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
using namespace std;

#include "House.h"
#include "Resource.h"
#include "Card.h"
#include "HouseColor.h"
#include "Strategy.h"

class Game;

class Player {
    private:
        vector<string> cities;
        vector<PowerplantCard> cards;
        int cardCounter;
        bool hasCard = false;
        int mostValuablePlant = 0;
        HouseColor color;
        int numHouses = 21;
        int money=0;
        SummaryCard summary;

        Strategy* strategy;

        int oilNum=0;
        int garbageNum=0;
        int uraniumNum=0;
        int coalNum=0;

        int maxOil = 0;
        int maxCoal = 0;
        int maxGarbage = 0;
        int maxUranium = 0;
        int extraCoalOrOil = 0;

        int numToPower = 0;

        bool canBid = true;
        bool canAuction = true;

    public:
        Player();
        Player(HouseColor color, Strategy* strategy);
        Player(const Player& other);
        ~Player();

        void purchaseCard(PowerplantCard& card, int value);
        void removeCard(PowerplantCard& card);
        int allowedToStore(Resource r) const;
        //method to get cards
        vector<PowerplantCard> getCards() const;
        void buyResources(Resource r, int value, int price);
        void removeResources(Resource r, int n);
        //setter for $$
        void setMoney(int money);
        //geter for $$
        int getMoney();
        //adds city name in vector
        void buyCity(string city, int cost);
        //outputs the cities owned
        vector<string> getCities() const;
        //returns the number of cities currently owned
        int getNumCities();
        int getHousesLeft() const;
        HouseColor getColor() const;
        int getCardCounter() const;

        void auction(Game& game);
        void pass();
        bool allowedToBid() const;
        bool allowedToAuction() const;
        void disallowBidding();
        void resetCanBid();
        void resetCanAuction();

        bool purchaseResources(Game& game);

        bool buildCities(Game& game);

        bool powerCities(Game& game);

        string info();

        int powerCard();

        int getNumCards();

        int getOil();
        int getCoal();
        int getUranium();
        int getGarbage();
        
        int getNumToPower() const;

        bool operator<(const Player& rhs) const;

        Player& operator=(const Player& rhs);
};

#endif

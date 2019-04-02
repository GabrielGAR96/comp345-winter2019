#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
using namespace std;

#include "House.h"
#include "Resource.h"
#include "Card.h"
#include "HouseColor.h"
#include "PowerplantCard.h"
#include "SummaryCard.h"
#include "Strategy.h"

class Game;

class Player {
    private:
        vector<string> cities;
        PowerplantCard cardArray[3];
        int mostValuablePlant = 0;
        HouseColor color;
        int numHouses = 21;
        int cardCounter;
        int money=0;
        SummaryCard summary;

        Strategy* strategy;

        int oilNum=0;
        int garbageNum=0;
        int uraniumNum=0;
        int coalNum=0;

        bool canBid = true;
        bool canAuction = true;

    public:
        Player();
        Player(HouseColor color, Strategy* strategy);
        Player(const Player& other);
        ~Player();

        //method to choose a card on the board and set it for auction
        int auctionCard(PowerplantCard card);
        //method to purchase card
        void purchaseCard(PowerplantCard card, int value);
        //method to get cards
        string getCards();
        PowerplantCard &getCard(int position);
        //determines score from owned cards
        int getScore() const;
        //chooses resources to buy
        void buyResources();
        //setter for $$
        void setMoney(int money);
        //geter for $$
        int getMoney();
        //buys resource and stores it in card
        void buyResource(int cardPosition, Resource resources, int amount, int price);
        //gets resources from cards
        string getResources();
        //adds city name in vector
        void buyCities(string city);
        //outputs the cities owned
        string getCities();
        //returns the number of cities currently owned
        int getNumCities();
        string getColor();
        int getHousesLeft() const;

        void auction(Game& game);
        void pass();
        bool allowedToBid() const;
        bool allowedToAuction() const;
        void disallowBidding();
        void resetCanBid();
        void resetCanAuction();

        void toString();
        string info();

        int powerCard();

        int getCardCounter();

        int powerableHouses();
        void addResource(Resource resource);
        void deleteResource(Resource resource);
        int findNumResource(Resource resource);
        int gettotstored();
        int getOil();
        int getCoal();
        int getUranium();
        int getGarbage();
        void getTotResources();

        bool operator<(const Player& rhs) const;

        Player& operator=(const Player& rhs);
};

#endif

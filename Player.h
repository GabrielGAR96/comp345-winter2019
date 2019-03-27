#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
using namespace std;

#include"House.h"
#include"Resource.h"
#include"Card.h"
#include "HouseColor.h"
#include "PowerplantCard.h"
#include "Resource.h"
class Player {
    private:
        vector<string> cities;
        PowerplantCard cardArray[3];
        HouseColor color;
        int cardCounter;
        int money;
        int housesOwned=4;


        int oilNum=0;
        int garbageNum=0;
        int uraniumNum=0;
        int coalNum=0;

        std::vector<Resource*> garbage;
        std::vector<Resource*> uranium;
        std::vector<Resource*> oil;
        std::vector<Resource*> coal;
    public:
        void setHouses(int houses);
        int getHouses();
        Player();
        Player(HouseColor color);
        ~Player();
        void gettotalresources();
        int getOil();
        int getGarbage();
        int getUranium();
        int getCoal();
        void getTotResources();
        //method to choose a card on the board and set it for auction
        void auctionCard(PowerplantCard card, int value);
        //method to purchase card
        void purchaseCard(PowerplantCard card, int value);
        //method to get cards
        string getCards();
        PowerplantCard &getCard(int position);
        //determines score from owned cards
        int getScore();
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

        void toString();

        int powerCard();

        int getCardCounter();

        int powerableHouses();
        void addResource(Resource resource);
        void deleteResource(Resource resource);
        int findNumResource(Resource resource);
        int gettotstored();
};

#endif

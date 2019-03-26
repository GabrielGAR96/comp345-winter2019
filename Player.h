#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
using namespace std;
using std::shared_ptr;
using std::vector;
using std::string;

#include"House.h"
#include"Resource.h"
#include"Card.h"
#include "HouseColor.h"
#include "PowerplantCard.h"

class Player {
    private:
        string name;
        vector<string> cities;
        PowerplantCard cardArray[3];
        HouseColor color;
        int cardCounter;
        int money;
        vector<shared_ptr<PowerplantCard>> powerPlants;
        vector<shared_ptr<House>> houses;
    public:

        Player();
        Player(HouseColor color);
        ~Player();

        //getters and setters for name
        string GetName() const { return name; }
        void SetName(string name) { this->name = name; }
        //method to choose a card on the board and set it for auction
        int auctionCard(PowerplantCard card);
        //method to purchase card
        void purchaseCard(PowerplantCard card, int value);
        //method to get cards
        string getCards();
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
        //return the number of houses currently owned
        vector<shared_ptr<House>>& getHouses() { return houses; }
        string getColor();
        void toString();
};

#endif

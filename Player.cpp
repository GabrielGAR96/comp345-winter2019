#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#include "Player.h"
#include"House.h"
#include"Resource.h"
#include"Card.h"
#include "HouseColor.h"
#include "Game.h"
#include "Strategy.h"

using namespace std;

Player::Player(){}

//constructor for a player setting initail $$ and color
Player::Player(HouseColor color, Strategy* strategy) {
    this->color = color;
    this->cardCounter = 0;
    this->strategy = strategy;
}

Player::Player(const Player& other)
{
    this->cities = other.cities;
    this->cards = other.cards;
    this->mostValuablePlant = other.mostValuablePlant;
    this->color = other.color;
    this->numHouses = other.numHouses;
    this->cardCounter = other.cardCounter;
    this->money = other.money;
    this->summary = other.summary;
    this->strategy = other.strategy->clone();
    this->oilNum = other.oilNum;
    this->garbageNum = other.garbageNum;
    this->uraniumNum = other.uraniumNum;
    this->coalNum = other.coalNum;
    this->canBid = other.canBid;
    this->canAuction = other.canAuction;
    this->maxOil = other.maxOil;
    this->maxCoal = other.maxCoal;
    this->maxGarbage = other.maxGarbage;
    this->maxUranium = other.maxUranium;
    this->extraCoalOrOil = other.extraCoalOrOil;
    this->numToPower = other.numToPower;
}

Player::~Player()
{
    delete strategy;
}

//buy a card and places in card array, if player already has 3 cards it will ask to swap for one
void Player::purchaseCard(PowerplantCard& card, int value) {
    if(hasCard) {
        if(mostValuablePlant < card.getName()) {
            mostValuablePlant = card.getName();
        }
    } else {
        hasCard = true;
        mostValuablePlant = card.getName();
    }
    cards.push_back(card);
    int canStore = card.getNeeded() * 2;
    switch(card.getResourceType()) {
        case COALOIL:
            maxCoal += canStore;
            maxOil += canStore;
            extraCoalOrOil += canStore;
            break;
        case COAL:
            maxCoal += canStore;
            break;
        case OIL:
            maxOil += canStore;
            break;
        case GARBAGE:
            maxGarbage += canStore;
            break;
        case URANIUM:
            maxUranium += canStore;
            break;
    }
    money -= value;
    cardCounter++;
}

void Player::removeCard(PowerplantCard& card)
{
    cards.erase(remove(cards.begin(), cards.end(), card), cards.end());
    int canStore = card.getNeeded() * 2;
    switch(card.getResourceType()) {
        case COALOIL:
            maxCoal -= canStore;
            maxOil -= canStore;
            extraCoalOrOil += canStore;
            break;
        case COAL:
            maxCoal -= canStore;
            break;
        case OIL:
            maxOil -= canStore;
            break;
        case GARBAGE:
            maxGarbage -= canStore;
            break;
        case URANIUM:
            maxUranium -= canStore;
            break;
    }
}

int Player::allowedToStore(Resource r) const
{
    switch(r) {
        case COAL:
            if(extraCoalOrOil > 0 ) {
                return maxCoal + extraCoalOrOil - (max(0, oilNum - maxOil)) - coalNum;
            }
            return maxCoal - coalNum;
        case OIL:
            if(extraCoalOrOil > 0) {
                return maxOil + extraCoalOrOil - (max(0, coalNum - maxCoal)) - oilNum;
            }
            return maxOil - oilNum;
        case GARBAGE:
            return maxGarbage - garbageNum;
        case URANIUM:
            return maxUranium - uraniumNum;
        default:
            throw -1;
    }
}

//outputs the players current cards
vector<PowerplantCard> Player::getCards() const
{
    return cards;
}

//setter for Elektro
void Player::setMoney(int amount) {
    this->money = money + amount;
}

//getter for Elektro
int Player::getMoney() {
    return this->money;
}

//returns the number of cities the player currently owns
int Player::getNumCities() {
    return cities.size();
}

void Player::buyResources(Resource r, int value, int price)
{
    switch(r) {
        case COAL:
            coalNum += value;
            break;
        case OIL:
            oilNum += value;
            break;
        case GARBAGE:
            garbageNum += value;
            break;
        case URANIUM:
            uraniumNum += value;
            break;
        default:
            throw -1;
    }
    money -= price;
}

void Player::removeResources(Resource r, int n)
{
    switch(r) {
        case COAL:
            coalNum -= n;
            break;
        case OIL:
            oilNum -= n;
            break;
        case GARBAGE:
            garbageNum -= n;
            break;
        case URANIUM:
            uraniumNum -= n;
            break;
        default:
            throw -1;
    }
}

//adds the the name of the cities that the player owns in a vector
void Player::buyCity(string city, int cost) {
    cities.push_back(city);
    money -= cost;
    numHouses--;
}

//outputs the cities that the player owns
vector<string> Player::getCities() const
{
    return cities;
}

int Player::getHousesLeft() const
{
    return numHouses;
}

HouseColor Player::getColor() const
{
    return color;
}

void Player::auction(Game& game)
{
    strategy->auction(game);
}

void Player::pass()
{
    canBid = false;
    canAuction = false;
}

bool Player::allowedToBid() const
{
    return canBid;
}

bool Player::allowedToAuction() const
{
    return canAuction;
}

void Player::disallowBidding()
{
    canBid = false;
}

void Player::resetCanBid()
{
    if(canAuction) canBid = true;
}

void Player::resetCanAuction()
{
    canBid = true;
    canAuction = true;
}

bool Player::purchaseResources(Game& game)
{
    return strategy->purchaseResources(game);
}

bool Player::buildCities(Game& game)
{
    return strategy->purchaseCities(game);
}

int Player::getNumToPower() const
{
    return numToPower;
}

bool Player::powerCities(Game& game)
{
    int coalToUse = 0;
    int oilToUse = 0;
    int garbageToUse = 0;
    int uraniumToUse = 0;

    numToPower = 0;
    bool cardsToUse[3] = {false, false, false};

    char response = 'n';
    while(true) {
        cout << "Player " << getHouseColorName(color) << endl;
        cout << "Would you like to power cities (y/N): ";
        cin >> response;
        response = (char)tolower(response);
        if(response == 'y' || response == 'n') break;
        else cout << "Invalid response.. Please try again" << endl;
    }
    if(response == 'n') return false;
    int plants = 0;
    while(plants < cardCounter) {
        int index;
        for(PowerplantCard& card : cards) {
            cout << card.info() << endl << endl;
        }
        string selector = (cardCounter > 1) ? ("1-" + to_string(cardCounter)) : "1";
        cout << "Which card would you like to use (" + selector + "): ";
        cin >> index;
        if(index < 1 || index > cardCounter) {
            cout << "Invalid selection... Try again" << endl;
            continue;
        }
        if(cardsToUse[index-1]) {
            cout << "You have already selected this card" << endl;
            continue;
        }
        PowerplantCard& card = cards[index-1];
        Resource uses = card.getResourceType();
        int resourceAmount;
        switch(uses) {
            case COALOIL:
                resourceAmount = coalNum + oilNum;
                break;
            case COAL:
                resourceAmount = coalNum;
                break;
            case OIL:
                resourceAmount = oilNum;
                break;
            case GARBAGE:
                resourceAmount = garbageNum;
                break;
            case URANIUM:
                resourceAmount = uraniumNum;
                break;
        }
        if(resourceAmount < card.getNeeded()) {
            cout << "You cannot use this card... insufficient resources available" << endl;
            return true;
        }
        cardsToUse[index-1] = true;
        numToPower += card.getPowerable();
        if(uses == COALOIL) {
            cout << "Coal: " << coalNum << " Oil: " << oilNum << endl;
            cout << "You need " << card.getNeeded() << " coal/oil in any combination" << endl;
            int selectCoal = 0;
            while(true) {
                if(coalNum > 0) {
                    cout << "How much coal do you want to use (1-" << coalNum << ", 0 to cancel): ";
                    cin >> selectCoal;
                    if(oilNum + selectCoal < card.getNeeded()) {
                        cout << "You must select more coal (you do not have enough oil)" << endl;
                        continue;
                    }
                    if(selectCoal < 0 || selectCoal > coalNum) {
                        cout << "Invalid selection... Try again" << endl;
                        continue;
                    }
                }
            }
            int selectOil = 0;
            while(true) {
                if(oilNum > 0 && selectCoal < card.getNeeded()) {
                    cout << "How much oil do you want o use (1-" << oilNum << "): ";
                    cin >> selectOil;
                    if(selectOil < 0 || selectOil > oilNum) {
                        cout << "Invalid selection... Try again" << endl;
                        continue;
                    }
                }
            }
            coalToUse += selectCoal;
            oilToUse += selectOil;
        }
        if(uses == COAL) coalToUse += card.getNeeded();
        if(uses == OIL) oilToUse += card.getNeeded();
        if(uses == GARBAGE) garbageToUse += card.getNeeded();
        if(uses == URANIUM) uraniumToUse += card.getNeeded();
        response = 'n';
        if(plants < cardCounter) {
            while(true) {
                cout << "Would you like to continue selecting cards (y/N): ";
                cin >> response;
                response = (char)tolower(response);
                if(response == 'y' || response == 'n') break;
                else cout << "Invalid response.. Please try again" << endl;
            }
            if(response == 'n') break;
        }
    }
    cout << "Powering " << numToPower << " cities" << endl;
    coalNum -= coalToUse;
    oilNum -= oilToUse;
    garbageNum -= garbageToUse;
    uraniumNum -= uraniumNum;
    game.getMap().addResourceToPool(COAL, coalToUse);
    game.getMap().addResourceToPool(OIL, oilToUse);
    game.getMap().addResourceToPool(GARBAGE, garbageToUse);
    game.getMap().addResourceToPool(URANIUM, uraniumToUse);
    return false;
}


string Player::info()
{
    string answer = "";
    answer += "Player: " + getHouseColorName(color) + "\n";
    answer += "Elektro: " + to_string(getMoney()) + "\n";
    answer += "Cities: " + to_string(getNumCities()) + "\n";
    answer += "Houses: " + to_string(getHousesLeft()) + "\n";
    answer += "Powerplants: " + to_string(cards.size()) + "\n";
    answer += "Resources: Coal: " + to_string(coalNum) + ", Oil: " + to_string(oilNum) + ", Garbage: " + to_string(garbageNum) + ", Uranium: " + to_string(uraniumNum) + "\n";
    answer += "Storage capacity: Coal: " + to_string(allowedToStore(COAL)) + ", Oil: " + to_string(allowedToStore(OIL)) + ", Garbage: " + to_string(allowedToStore(GARBAGE)) + ", Uranium: " + to_string(allowedToStore(URANIUM));

    return answer;
}

int Player::getOil(){
  return oilNum;
}
int Player::getCoal(){
  return coalNum;
}
int Player::getUranium(){
  return uraniumNum;
}
int Player::getGarbage(){
  return garbageNum;
}

int Player:: getCardCounter() const
{
  return cardCounter;
}

bool Player::operator<(const Player& rhs) const
{
    if(this->cities.size() == rhs.cities.size()) {
        return this->mostValuablePlant < rhs.mostValuablePlant;
    }
    return this->cities.size() < rhs.cities.size();
}

Player& Player::operator=(const Player& rhs)
{
    if(this == &rhs) return *this;
    this->cities = rhs.cities;
    this->cards = rhs.cards;
    this->color = rhs.color;
    this->numHouses = rhs.numHouses;
    this->cardCounter = rhs.cardCounter;
    this->money = rhs.money;
    this->summary = rhs.summary;
    this->strategy = rhs.strategy->clone();
    this->oilNum = rhs.oilNum;
    this->garbageNum = rhs.garbageNum;
    this->uraniumNum = rhs.uraniumNum;
    this->coalNum = rhs.coalNum;
    this->canBid = rhs.canBid;
    this->canAuction = rhs.canAuction;
    this->maxOil = rhs.maxOil;
    this->maxCoal = rhs.maxCoal;
    this->maxGarbage = rhs.maxGarbage;
    this->maxUranium = rhs.maxUranium;
    this->extraCoalOrOil = rhs.extraCoalOrOil;
    this->numToPower = rhs.numToPower;

    return *this;
}

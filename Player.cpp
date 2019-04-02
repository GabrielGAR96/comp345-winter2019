#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "Player.h"
#include"House.h"
#include"Resource.h"
#include"Card.h"
#include "HouseColor.h"
#include "SummaryCard.h"
#include "PowerplantCard.h"
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
    for(int i = 0; i < other.cardCounter; i++) {
        this->cardArray[i] = other.cardArray[i];
    }
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
}

Player::~Player()
{
    // LOOK INTO THIS
    delete strategy;
}

//auction a selected card modifying the auction value on card
int Player::auctionCard(PowerplantCard card) {
        int bet;
        cout << "Please enter an auction amount: ";
        cin >> bet;
        while (bet <= card.GetPrice()) {
            cout << "Please enter a bet greater than the current auction value: ";
            cin >> bet;
        }
        while (bet > money) {
            cout << "You do not have enough Elektro to bet!!" << endl;
            cout << "Enter a different amout or bet 0 to skip: ";
            cin >> bet;
            if (bet == 0)
                return 0;
        }
        card.SetPrice(bet);
        return card.GetPrice();
}

//buy a card and places in card array, if player already has 3 cards it will ask to swap for one
void Player::purchaseCard(PowerplantCard card, int value) {
    if (cardCounter == 3) {
        int position;
        cout << "What card would you like to swap with?" << endl;
        cout << "Press 1 for " << cardArray[0].getName();
        cout << "\nPress 2 for " << cardArray[1].getName();
        cout << "\nPress 3 for " << cardArray[2].getName();
        cin >> position;
        while (position > 3 || position < 0) {
            cout << "Please chose a valid option or press -1 to cancel trade: ";
            cin >> position;
            if (position == -1)
                return;
        }
    }
    money = money - value;
    cardArray[cardCounter] = card;
    if(!(cardCounter == 3))
    cardCounter++;
}

//outputs the players current cards
string Player::getCards() {
    string myCards = "";
    for (int i = 0; i < cardCounter; i++) {
        myCards.append(cardArray[i].info());
    }

    return myCards;
}

//determins score based on highest value card
int Player::getScore() const {
    int price=0;
    int myScore=0;
    for (int i = 0; i < cardCounter; i++)
        if (cardArray[i].getName() > price)
            price = cardArray[i].getName();
        myScore = price;
    return myScore;
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

//buys resources based on the currently owned cards and stores it in the card
void Player::buyResource(int cardPosition, Resource resources, int amount, int price) {
    for (int i = 0; i < amount; i++) {
        cardArray[cardPosition].store(resources);
        this->money = money - price;
    }
}

//outputs the resources the player owns
string Player::getResources() {
    string result = "";
    for (int i = 0; i < cardCounter; i++) {
        result.append(cardArray[i].getResources() + " ");
    }
    return result;
}

//adds the the name of the cities that the player owns in a vector
void Player::buyCities(string city) {
    cities.push_back(city);
}

//outputs the cities that the player owns
string Player::getCities() {
    string city;
    for (string c : cities)
        city.append(c + " ");
    return city;
}


string Player::getColor() {
    return getHouseColorName(color);

}

void Player::toString(){
    std::cout << "Score: " << this->getScore() <<'\n';
    std::cout << "Color: " << this->getColor()<<'\n';
    std::cout << "Elektro:  " <<this->getMoney() <<'\n';
    std::cout << "Resources: " <<"\n"<<endl;
    getTotResources();

    std::cout << "\nCities: " << this->getCities()<<'\n';
    std::cout << "Cards:\n" << this->getCards()<<'\n';
}

int Player::getHousesLeft() const
{
    return numHouses;
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

string Player::info()
{
    string answer = "";
    answer += "Score: " + to_string(getScore()) + "\n";
    answer += "Color: " + getColor() + "\n";
    answer += "Elektro: " + to_string(getMoney()) + "\n";
    answer += "Resources: " + getResources() + "\n";
    answer += "Cities: " + getCities() + "\n";
    answer += "Cards: " + getCards() + "\n";
    answer += "Houses: " + to_string(getHousesLeft()) + "\n";
    answer += "SummaryCard:\n" + summary.info() + "\n";

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

void Player::getTotResources(){
  cout<<"GARBARGE = "<<garbageNum<<endl;
  cout<<"COAL = "<<coalNum<<endl;
  cout<<"OIL = "<<oilNum<<endl;
  cout<<"URANIUM = "<<uraniumNum<<endl;
}
int Player::powerCard(){

  cout<<"What card would you like to power?"<<endl;
  for(int i=0;i<cardCounter;i++){
    cout<<i+1<<": " << cardArray[i].info();
  }
return 0;
}

int Player:: getCardCounter(){
  return cardCounter;
}

PowerplantCard &Player::getCard(int position){
  return cardArray[position];
}

int Player::gettotstored(){
  return oilNum + uraniumNum + garbageNum + coalNum;
}

bool Player::operator<(const Player& rhs) const
{
    if(this->cities.size() == rhs.cities.size()) {
        return this->getScore() < rhs.getScore();
    }
    return this->cities.size() < rhs.cities.size();
}

Player& Player::operator=(const Player& rhs)
{
    if(this == &rhs) return *this;
    this->cities = rhs.cities;
    for(int i = 0; i < rhs.cardCounter; i++) {
        this->cardArray[i] = rhs.cardArray[i];
    }
    this->mostValuablePlant = rhs.mostValuablePlant;
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

    return *this;
}

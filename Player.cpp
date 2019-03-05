#include "Player.h"
#include "PowerplantCard.h"
#include "HouseColor.h"

using namespace std;

//constructor for a player setting initail $$ and color
Player::Player(HouseColor color) {
	this->color = color;
	this->cardCounter = 0;
	this->money = 50;

}

Player::~Player()
{
}

//auction a selected card modifying the auction value on card
void Player::auctionCard(PowerplantCard card, int value){
		int bet;
		cout << "Please enter an auction amount: ";
		cin >> bet;
		while (bet < value) {
			cout << "Please enter a bet greater than the current auction value: ";
			cin >> bet;
		}
		while (bet > money) {
			cout << "You do not have enough Elektro to bet!!" << endl;
			cout << "Enter a different amout or bet 0 to skip: ";
			cin >> bet;
			if (bet == 0)
				return;
		}
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
			money = money - value;
			cardArray[position - 1] = card;
			cardCounter++;
		}
	}
//outputs the players current cards
string Player::getCards() {
		string myCards = "Your current cards are:\n";
			if (cardCounter == 0)
				return "You have no owned cards";
			else {
			for (int i = 0; i < cardCounter; i++) {
				myCards.append(to_string(cardArray[i].getName()) + "\n");
			}
		}
        return myCards;
	}
//determins score based on highest value card
string Player::getScore() {
		string myScore = "Your current highest value power plant is: ";
		int price=0;
		for (int i = 0; i < cardCounter; i++)
			if (cardArray[i].getName() > price)
				price = cardArray[i].getName();
		myScore.append(to_string(price));
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
void Player::buyResource(PowerplantCard card, Resource resources, int amount, int price) {
		for (int i = 0; i < amount; i++) {
			card.store(resources);
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
			city.append(c);
		return city;
	}
string Player::getColor() {

	string hc = "Players house color is: ";
	hc.append(getHouseColorName(color));
    return hc;
}

#include "Player.h"

using namespace std;
//constructor for a player setting initail $$ and color  
Player::Player(string color) {
		this->house.setColor(color);
		this->cardCounter = 0;
		this->money = 50;
		this->resources;
	}
//auction a selected card modifying the auction value on card
void Player::auctionCard(Card card){
		int bet;
		cout << "Please enter an auction amount: ";
		cin >> bet;
		while (bet < card.getAuctionPrice()) {
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
		card.setAuctionPrice(bet);
	}
//buy a card and places in card array, if player already has 3 cards it will ask to swap for one
void Player::purchaseCard(Card card) {
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
			money = money - card.getAuctionPrice;
			cardArray[position - 1] = card;
			cardCounter++;
		}
	}
//outputs the players current cards
string Player::getCards() {
		cout << "Your current cards are:" << endl;
			if (cardCounter == 0)
				cout << "You have no owned cards";
			else {
			for (int i = 0; i < cardCounter; i++) {
				cout << cardArray[i].getName();
				cout << endl;
			}
		}
	}
//determins score based on highest value card
string Player::getScore() {
		cout << "Your current highest value power plant is: ";
		int price=0;
		for (int i = 0; i < cardCounter; i++)
			if (cardArray[i].getprice > price)
				price = cardArray[i].getprice;
		cout << price;
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
		return cities.size;
	}
//buys resources based on the currently owned cards and stores it in the card 
void Player::buyResource(Card card, Resource resources, int amount, int price) {
		for (int i = 0; i < amount; i++) {
			card.store(resources);
			this->money = money - price;
		}
	}
//outputs the resources the player owns 
string Player::getResources() {
		for (int i = 0; i < cardCounter; i++) {
			cardArray[i].getresources();
		}
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



















int main() {

	std::cout << "hi";

}
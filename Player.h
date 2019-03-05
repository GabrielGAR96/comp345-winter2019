#pragma once
#include <iostream>
#include<string>
#include"House.h"
#include"Resource.h"
#include"Card.h"
#include<vector>
#include "HouseColor.h"
#include "PowerplantCard.h"
//#include "City.h"

class Player {
	

	private:

		
		vector<string> cities;
		PowerplantCard cardArray[3];
		HouseColor color;
		int cardCounter;
		int money;

	public:

		Player();
		Player(HouseColor color);
		~Player();

		//method to choose a card on the board and set it for auction
		void auctionCard(PowerplantCard card, int value);
		//method to purchase card
		void purchaseCard(PowerplantCard card, int value);
		//method to get cards
		string getCards();
		//determines score from owned cards 
		string getScore();
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








};

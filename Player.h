#pragma once
#include <iostream>
#include<string>
#include"House.h"
#include"Resource.h"
#include"Cards.h"
#include <vector>
//#include "City.h"

class Player {
	

	private:

		
		vector <string> cities;
		Card cardArray[3];
		House house;
		int cardCounter;
		Resource resources;
		int money;

	public:

		Player();
		Player(string color);
		~Player();

		//method to choose a card on the board and set it for auction
		void auctionCard(Card card);
		//method to purchase card
		void purchaseCard(Card card);
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
		void buyResource(Card card, Resource resources, int amount, int price);
		//gets resources from cards 
		string getResources();
		//adds city name in vector 
		void buyCities(string city);
		//outputs the cities owned
		string getCities();
		//returns the number of cities currently owned
		int getNumCities();









};

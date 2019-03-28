///*
////
//// Created by Gabriel Albuquerque Ribeiro on 2019-03-19.
////
//
#include "Game.h"
#include "Player.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
//
//counts how many players have passed the auction
int Game::CountMapFalse(){
    int count = 0;
    for (int i = 0; i < canBuy.size(); ++i) {
        if(canBuy[&players[i]] == false) count++;
    }
    return count;
};

bool Game::AddPlayer(Player player) {
    if(players.size() == MAX_PLAYERS){
        return false;
    }
    players.push_back(player);
    return true;
}

void Game::GetPowerplantCards() {
    for(int i = 0; i < 4 ; i++){
        cout << "Card: " << powerplantCards[i].getName() << endl;
        cout << "Price: " << powerplantCards[i].GetPrice() << endl;
        cout << "Resource: " << powerplantCards[i].getResources() << endl;
        cout << "Amount needed: " << powerplantCards[i].getNeeded() << endl;
        cout << "Powerable houses: " <<  powerplantCards[i].getPowerable() << endl;
        cout << endl;
    }
}

void Game::AddPowerplant(PowerplantCard powerplantCard) {
    powerplantCards.push_back(powerplantCard);
}

void Game::NewGame() {
    cout << "New game started!" << endl;

    firstTurn = true;
    counter = 0;
    fullTurn = 1;
    //resets all attributes
    Phase1Start();
}

void Game::UpdatePlayOrder(bool reverse) {
    // Priority: 1 - House
    for (int i = 0; i < GetPlayers().size()-1; ++i) {
        for (int j = 1; j < GetPlayers().size(); ++j) {
            if(players[i].getHouses() > players[j].getHouses()){
               std::swap(players[i], players[j]);
            }
        }
    }
    // Priority: 2 - highest value card
    for (int i = 0; i < GetPlayers().size()-1; ++i) {
        for (int j = 1; j < GetPlayers().size(); ++j) {
            if(players[i].getScore() > players[j].getScore()) {
                std::swap(players[i], players[j]);
            }
        }
    }

    if(reverse) std::reverse(players.begin(), players.end());
    currentPlayer = &players[0];

}
void Game::Phase1Start() {
    phase = 0;
    playPhase = 1;
    plantIndex = -1;
    
    //initializes both maps so all players can buy once phase 1 starts
    for (Player &player : players) {
        canBuy[&player] = true;
        canBid[&player] = true;
    }
    playPhase = 1;
    cout << "Phase 1 started" << endl;
    cout << "Determining player order" << endl;
    if(fullTurn = 1){
    random_shuffle(players.begin(), players.end());
    currentPlayer = &players[0];
    }
    else UpdatePlayOrder(true); //do not sort in first turn
    for(Player player : players){
        cout << "playerOrder: " << player.getColor() << endl;
    }

    cout << "Player order determined successfully!" << endl;
    Phase2Start();
}


void Game::Phase2Start() {
    playPhase = 2;
    cout << "Phase 2 started" << endl;

    // Reset can buy for all players

    for (Player &player : players) {
        canBuy[&player] = true;
    }
    Phase2StartBid();
}
//if the counter has accessed every single element in the vector
//the players that did not skip will be able to bid in their following turn
void Game::Phase2StartBid() {
    if(counter == players.size()){
        for (Player &player : players) {
            if (canBuy[&player])
                canBid[&player] = true;
            else
                canBid[&player] = false;
        }
    }
    cout << "Current Player: " << currentPlayer->getColor() << endl;
    cout << "Would you like to bid?" << endl;
    cin >> nowBidding;
    if(nowBidding){
        highestBidder = currentPlayer;
        Phase2Bid();
    }
    else Pass();
}

void Game::Phase2Bid() {

    if(plantIndex < 0){
        do{
            cout << "Select a card to bid" << endl;
            GetPowerplantCards();
            cin >> plantIndex;
        }while(plantIndex >= 4 || plantIndex < 0);
        currentCard = &powerplantCards[plantIndex];
    }
    if(fullTurn > 1){ //in case the current player is not the one who started the auction
        cout << "Currently auctioning: Card #" << currentCard->getName() << endl;
        cout << "Current offer: " << currentCard->GetPrice() << endl;
        cout << "resource: " << currentCard->getResources() << endl;

        currentBid = currentPlayer->auctionCard(*currentCard);
        if(currentBid != 0)
            currentCard->SetPrice(currentBid);
        else Pass();
    }else currentBid = currentCard->GetPrice(); //in case the current player is the one who started the auction
    canBid[currentPlayer] = false;

    NextPlayer();

}
//players who skip will not have a chance to bid in the next turn in the same auction
void Game::Pass() {
    if(fullTurn == 1 && firstTurn == true) {
        cout << "Cannot skip on first turn!" << endl;
        Phase2StartBid();
    }
    canBid[currentPlayer] = false;
    canBuy[currentPlayer] = false;
    // go to next player
    NextPlayer();

}

void Game::NextPlayer() {
    counter = 0; //counts how many elements the loop has accessed in the vector

        canBid[currentPlayer] = false;
        for (Player &player : players) {
            counter++;
           // cout << canBid[&player] << endl;
            if (canBid[&player]) {
                currentPlayer = &player; // next player turn
                while (CountMapFalse() < 5){
                    if(currentCard != nullptr) //fullturn only updates if a card is in auction
                    fullTurn++;
                Phase2StartBid();
                }
        }
    }
    Phase2End();

}


void Game::Phase2End() {
    firstTurn = false;
    cout << highestBidder->getColor() << " player won the auction!" << endl;
    highestBidder->purchaseCard(*currentCard, currentBid);
    powerplantCards.erase(std::remove(powerplantCards.begin(), powerplantCards.end(), *currentCard), powerplantCards.end());
    //powerplantCards.r
    random_shuffle(powerplantCards.begin() + 8, powerplantCards.end());
    currentCard = nullptr;
    currentPlayer = nullptr;
    for(Player &player : players){
        player.toString();
        cout << endl;
    }
    Phase1Start();//this should point to the next phase, I'm only pointing to the start of phase 1
                  //so my loop continues

}


#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iomanip>
using namespace std;

#include <boost/filesystem.hpp>

#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader2.h"
#include "HouseColor.h"

Game::Game(vector<Player>& players, Map* board)
    : players(players), board(board)
{
    board->addElektroToBank(1000);
    for(Player& player : this->players) {
        player.setMoney(board->getElektroFromBank(50));
    }
}

Game::~Game()
{
    delete board;
}

void Game::restockMarket()
{
    board->restockMarket(players.size(), step);
}

string Game::playerInfo()
{
    string info = "";
    int i = 1;
    for(Player& player : players) {
        info += "Player " + to_string(i++) + ":\n";
        info += player.info() + "\n";
    }
    return info;
}

Game* Game::buildGame()
{
    unordered_map<string, HouseColor> colors = {{"black", BLACK},
                                                {"blue", BLUE},
                                                {"red", RED},
                                                {"yellow", YELLOW},
                                                {"green", GREEN},
                                                {"purple", PURPLE}};
    map<int, string> files;
    readDirectory("./maps/", files);
    Map* powergrid = selectMap(files);
    int numPlayers = selectNumberOfPlayers();
    vector<Player> players;
    setupPlayers(numPlayers, colors, players, powergrid);
    powergrid->finalize();
    cout << endl;
    return new Game(players, powergrid);
}

struct pathLeafString
{
    pair<int, string> operator()(const boost::filesystem::directory_entry& entry) const
    {
        static int i = 1;
        return make_pair(i++, entry.path().leaf().string());
    }
};

void Game::readDirectory(const string& name, map<int, string>& files)
{
    boost::filesystem::path p(name);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    transform(start, end, inserter(files, files.end()), pathLeafString());
}

Map* Game::selectMap(map<int, string>& files)
{
    Map* powergrid;
    bool loaded = false;
    do {
        cout << "Available maps:" << endl;
        for(auto file : files)
        {
            cout << file.first << ". " << file.second << endl;
        }
        int selection;
        cout << endl << "select by entering #: ";
        cin >> selection;
        string file = "./maps/" + files[selection];
        cout << endl << "loading " << file << endl;
        try {
            powergrid = MapLoader2::load(file);
            loaded = true;
        } catch(BadMap& ex) {
            cout << ex.what() << endl << endl;
        }
    } while(!loaded);
    return powergrid;
}

int Game::selectNumberOfPlayers()
{
    int numPlayers;
    do {
        cout << "How many players are there (2-6): ";
        cin >> numPlayers;
        if(numPlayers < 2 || numPlayers > 6) {
            cout << "Invalid number of players (" << numPlayers << ") selected" << endl << endl;
        }
    } while(numPlayers < 2 || numPlayers > 6);
    return numPlayers;
}

void Game::selectPlayerColor(int i, unordered_map<string, HouseColor>& colors, vector<Player>& players)
{
    bool colorSelected = false;
    do {
        string selection;
        cout << "Available colors:" << endl;
        for(auto color : colors)
        {
            cout << color.first << endl;
        }
        cout << endl;
        cout << "Player " << i << " select a house color: ";
        cin >> selection;
        if(colors.find(selection) != colors.end()) {
            players.push_back(Player(colors[selection]));
            colors.erase(selection);
            colorSelected = true;
        } else {
            cout << "Not a vailid selection" << endl << endl;
        }
    } while(!colorSelected);
}

void Game::selectRegion(int i, Map* powergrid)
{
    int region;
    bool regionSelected = false;
    do {
        cout << "Player " << i << " select a region for play: ";
        cin >> region;
        if(powergrid->getRegions().find(region) != powergrid->getRegions().end() || region < 1 || region > 6) {
            powergrid->useRegion(region);
            regionSelected = true;
        } else {
            cout << "Region " << region << " is an invalid selection" << endl << endl;
        }
    } while(!regionSelected);
}

void Game::setupPlayers(int numPlayers, unordered_map<string, HouseColor>& colors, vector<Player>& players, Map* powergrid)
{
    bool playersCreated = false;
    bool validRegionsSelected = false;
    if(numPlayers < 6) {
        do {
            int i = 1;
            powergrid->clearRegions();
            while(i <= numPlayers)
            {
                cout << endl;
                if(!playersCreated) {
                    selectPlayerColor(i, colors, players);
                }
                selectRegion(i, powergrid);
                i++;
            }
            playersCreated = true;
            validRegionsSelected = powergrid->test();
            if(!validRegionsSelected) {
                cout << "Selected regions are not adjactent. Please try again" << endl << endl;
            }
        } while(!validRegionsSelected);
    } else {
        for(int i = 1; i <= 6; i++) {
            selectPlayerColor(i, colors, players);
            powergrid->useRegion(i);
        }
    }
}

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
    for (Player &player : players) {
        canBuy[&player] = true;
        canBid[&player] = true;
    }
    playPhase = 1;
    cout << "Phase 1 started" << endl;
    cout << "Determining player order" << endl;
    if(fullTurn == 1){
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


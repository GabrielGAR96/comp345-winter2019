#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <dirent.h>
using namespace std;

/* #include <boost/filesystem.hpp> */

#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "HouseColor.h"
#include "Card.h"

const int Game::PAYOUT[21] = {10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150};

Game::Game()
{
}
string Game::getPlayerOrder(){
  string s ="";
  for(Player p : players){
    s += p.getColor() + " ";
  }
  return s;
}
Game::Game(vector<Player>& players, Map* board)
    : players(players), board(board)
{
    board->addElektroToBank(1000);
    for(Player& player : this->players) {
        player.setMoney(board->getElektroFromBank(50));
    }
    cards = loadCards();
    // First 8 Powerplants get put in fixed size Market
    PowerplantCard market[8] = {cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7]};
    powerPlants.setMarket(market);
    int ecoOnePos = 2;
    int deckSize = 32;
    PowerplantCard* deck = cards + 8;
    this->deck.setDeck(deck, deckSize, ecoOnePos, s3Card);
}
int Game::getPhase(){
  return phase;
}
Player Game::getPlayer(int i){
  return players[i];
}
Game::~Game()
{
    delete board;
    delete [] cards;
}

Player& Game::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

PowerplantMarket& Game::getMarket()
{
    return powerPlants;
}

int Game::getStep() const
{
    return step;
}

bool Game::isFirstRound() const
{
    return firstRound;
}

void Game::phase1()
{
    phase = 1;

    sort(players.begin(), players.end());
    currentPlayerIndex = 0;
    notifyObserver();
}
int Game::getNumPlayers(){
  return players.size();
}
void Game::phase2()
{
    phase =2;
    int auctionee = currentPlayerIndex;
    int participants = players.size();
    while(true) {
        notifyObserver();
        int currentWinnerIndex = -1;
        int bidders = 0;
        for(Player& player : players) {
            if(player.allowedToBid()) bidders++;
        }
        Player* currentPlayer = &players[auctionee];
        while(true) {
            currentPlayer->auction(*this);
            if(currentPlayer->allowedToBid()) currentWinnerIndex = currentPlayerIndex;
            else {
                bidders--;
                if(!currentPlayer->allowedToAuction()) participants--;
            }
            // There is a winner
            if(bidders <= 1) break;
            // Next players chance to bid
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            currentPlayer = &players[currentPlayerIndex];
            while(!currentPlayer->allowedToBid()) {
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                currentPlayer = &players[currentPlayerIndex];
            }
        }
        if(auctioning) {
            Player& winner = players[currentWinnerIndex];
            int price  = powerPlants.getCurrentBid();
            PowerplantCard card = powerPlants.buy(deck);
            if(winner.getCardCounter() == 3) {
                cout << "You must discard a powerplant" << endl;
                vector<PowerplantCard> playerCards = winner.getCards();
                int index = 1;
                for(PowerplantCard& powerplant : playerCards) {
                    cout << index++ << endl;
                    cout << powerplant.info() << endl;
                }
                int removeIndex = 0;
                while(removeIndex < 1 || removeIndex > 3) {
                    cout << "Pick a card (1-3): ";
                    cin >> removeIndex;
                    if(removeIndex < 1 || removeIndex > 3) {
                        cout << "Invalid choice" << endl;
                    }
                }
                PowerplantCard& toRemove = playerCards[removeIndex];
                winner.removeCard(toRemove);
            }
            winner.purchaseCard(card, price);
            int poolCoal = -1*min(0, winner.allowedToStore(COAL));
            int poolOil = -1*min(0, winner.allowedToStore(OIL));
            int poolGarbage = -1*min(0, winner.allowedToStore(GARBAGE));
            int poolUranium = -1*min(0, winner.allowedToStore(URANIUM));
            board->addResourceToPool(COAL, poolCoal);
            board->addResourceToPool(OIL, poolOil);
            board->addResourceToPool(GARBAGE, poolGarbage);
            board->addResourceToPool(URANIUM, poolUranium);
            winner.removeResources(COAL, poolCoal);
            winner.removeResources(OIL, poolOil);
            winner.removeResources(GARBAGE, poolGarbage);
            winner.removeResources(URANIUM, poolUranium);
            winner.pass(); // Can't participate in future auctions
            participants--;
            for(Player& player : players) {
                player.resetCanBid();
            }
            auctioning = false;
        }
        if(participants == 0) break;
        auctionee = (auctionee + 1) % players.size();
        while(!players[auctionee].allowedToAuction()) {
            auctionee = (auctionee + 1) % players.size();
        }
        currentPlayerIndex = auctionee;
    }
    for(Player& player : players) {
        player.resetCanAuction();
    }
    reverse(players.begin(), players.end());
    currentPlayerIndex = 0;
}

bool Game::auctionStarted() const
{
    return auctioning;
}

void Game::setAuctionStarted(bool auctioning)
{
    this->auctioning = auctioning;
}

void Game::phase3()
{
  phase = 3;
    for(Player& player : players) {
      notifyObserver();
        while(player.purchaseResources(*this));
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}

void Game::phase4()
{

  phase = 4;
    for(Player& player : players) {
      notifyObserver();
        while(player.buildCities(*this));
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}

void Game::phase5()
{
  phase = 5;
    for(Player& player : players) {
      notifyObserver();
        while(player.powerCities(*this));
        int currentMoney = player.getMoney();
        int pay = PAYOUT[player.getNumToPower()];
        player.setMoney(currentMoney + pay);
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
    cout << gameInfo() << endl;
}

Map& Game::getMap()
{
    return *board;
}

void Game::restockMarket()
{
    board->restockMarket(players.size(), step);
}

string Game::gameInfo()
{
    string info = "Players:\n";
    int i = 1;
    for(Player& player : players) {
        info += "Player " + to_string(i++) + ":\n";
        info += player.info() + "\n";
    }
    info += "\n";
    info += "Resource Market:\n";
    info += board->marketDescription();
    info += "\n";
    info += "Powerplant Market:\n";
    info += powerPlants.toString();
    info += "\n";
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
    /* readDirectory("./maps/", files); */
    DIR *dir;
    struct dirent *ent;
    int i = 1;
    if((dir = opendir("./maps")) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            files.insert({i++, string(ent->d_name)});
        }
        closedir(dir);
    } else {
        throw -1;
    }
    Map* powergrid = selectMap(files);
    int numPlayers = selectNumberOfPlayers();
    vector<Player> players;
    setupPlayers(numPlayers, colors, players, powergrid);
    powergrid->finalize();
    cout << endl;
    return new Game(players, powergrid);
}


/* struct pathLeafString */
/* { */
/*     pair<int, string> operator()(const boost::filesystem::directory_entry& entry) const */
/*     { */
/*         static int i = 1; */
/*         return make_pair(i++, entry.path().leaf().string()); */
/*     } */
/* }; */

/* void Game::readDirectory(const string& name, map<int, string>& files) */
/* { */
/*     boost::filesystem::path p(name); */
/*     boost::filesystem::directory_iterator start(p); */
/*     boost::filesystem::directory_iterator end; */
/*     transform(start, end, inserter(files, files.end()), pathLeafString()); */
/* } */

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
        string file = files[selection];
        cout << endl << "loading " << file << endl;
        try {
            powergrid = MapLoader::load(file);
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
            players.push_back(Player(colors[selection], new HumanStrategy()));
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

PowerplantCard* Game::loadCards()
{
    const int NUM_POWER_PLANTS = 42;
    const int MARKET_SIZE = 8;

    PowerplantCard* cards = new PowerplantCard[NUM_POWER_PLANTS];

    // We will read the definition of the cards from text... This is better than
    // hardcoding here
    fstream input;

    // Info from the text file will be stored here
    int name;
    string resources;
    int powerable;

    input.open("powerplants.txt");

    // Loop over lines of the text file to collect cards
    int i = 0;
    while(input >> name >> resources >> powerable)
    {
        PowerplantCard c;

        int needed = stoi(resources.substr(0, 1));

        // Skip if we read an ecological plant
        if(needed > 0)
        {
            string types[2];
            size_t size = 0;
            size_t start = 2;
            size_t end = resources.find(",");

            // Resources need some special parsing because a plant might use
            // more than one type of resource
            while(end != string::npos)
            {
                // Resource records are stored as:
                // resource1[:resource2]
                types[size++] = resources.substr(start, end - start);
                start = end + 1;
                end = resources.find(",", start);

            }

            types[size++] = resources.substr(start, end);

            // Did we find one resource or two
            if(size == 1) c = PowerplantCard(name, powerable, needed, getResourceByName(types[0]));

            else c = PowerplantCard(name, powerable, needed, COALOIL);

        } else {
            // Ecological card
            c = PowerplantCard(name, powerable, needed);
        }
        // Deck of only Powerplant cards
        cards[i++] = c;
    }

    // We're done
    input.close();
    return cards;

    // First 8 Powerplants get put in fixed size Market
    /* PowerplantCard market[8] = {cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7]}; */

    /* this->powerPlants.setMarket(market); */

    /* const int FULL_DECK_SIZE = NUM_POWER_PLANTS - MARKET_SIZE; */

    /* // Get the remaining Powerplants for the deck */
    /* PowerplantCard deckCards[FULL_DECK_SIZE]; */
    /* for(int i = 0; i < FULL_DECK_SIZE; i++) */
    /* { */
    /*     deckCards[i] = cards[i + MARKET_SIZE]; */
    /* } */

    /* // First ecological Powerplant goes on top of the deck after shuffling so */
    /* // let's remove it */
    /* PowerplantCard ecoOne = cards[10]; */

    /* // The Step 3 card goes on the bottom of the deck after shuffling */
    /* Step3Card s3Card; */

    /* // Shuffle the remaining deck cards */
    /* Deck::shuffle(deckCards, FULL_DECK_SIZE); */

    /* // Create a deck with a linked list */
    /* list<Card*> deck; */
    /* for(PowerplantCard& c: deckCards) */
    /* { */
    /*     // We actually shuffled card 13 into the deck anyway so don't add it */
    /*     // to the real deck */
    /*     if(c == ecoOne) continue; */
    /*     deck.push_back(&c); */
    /* } */

    /* // Add special cards to their special places */
    /* deck.push_front(&ecoOne); */
    /* deck.push_back(&s3Card); */

    /* return deck; */
}

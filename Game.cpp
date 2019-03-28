#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#include <boost/filesystem.hpp>

#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader2.h"
#include "HouseColor.h"
#include "Step3Card.h"
#include "PowerplantCard.h"

Game::Game(vector<Player>& players, Map* board)
    : players(players), board(board)
{
    board->addElektroToBank(1000);
    for(Player& player : this->players) {
        player.setMoney(board->getElektroFromBank(50));
    }
    loadCards();
}

Game::~Game()
{
    delete board;
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
    info += "Deck:\n";
    info += deck.toString();
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

void Game::loadCards()
{
    const int NUM_POWER_PLANTS = 42;
    const int MARKET_SIZE = 8;

    PowerplantCard cards[NUM_POWER_PLANTS];

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

            else c = PowerplantCard(name, powerable, needed, getResourceByName(types[0]), getResourceByName(types[1]));

        } else {
            // Ecological card
            c = PowerplantCard(name, powerable, needed);
        }
        // Deck of only Powerplant cards
        cards[i++] = c;
    }

    // We're done
    input.close();

    // First 8 Powerplants get put in fixed size Market
    PowerplantCard market[8] = {cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7]};

    this->powerPlants.setMarket(market);

    const int FULL_DECK_SIZE = NUM_POWER_PLANTS - MARKET_SIZE;

    // Get the remaining Powerplants for the deck
    PowerplantCard deckCards[FULL_DECK_SIZE];
    for(int i = 0; i < FULL_DECK_SIZE; i++)
    {
        deckCards[i] = cards[i + MARKET_SIZE];
    }

    // First ecological Powerplant goes on top of the deck after shuffling so
    // let's remove it
    PowerplantCard ecoOne = cards[10];

    // The Step 3 card goes on the bottom of the deck after shuffling
    Step3Card s3Card;

    // Shuffle the remaining deck cards
    Deck::shuffle(deckCards, FULL_DECK_SIZE);

    // Create a deck with a linked list
    list<Card*> deck;
    for(PowerplantCard& c: deckCards)
    {
        // We actually shuffled card 13 into the deck anyway so don't add it
        // to the real deck
        if(c == ecoOne) continue;
        deck.push_back(&c);
    }

    // Add special cards to their special places
    deck.push_front(&ecoOne);
    deck.push_back(&s3Card);

    this->deck.setDeck(deck);
}

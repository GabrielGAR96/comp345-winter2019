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

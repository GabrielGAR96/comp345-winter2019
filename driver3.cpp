#include <fstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

#include "MapLoader.h"
#include "Map.h"
#include "Resource.h"
#include "House.h"
#include "HouseColor.h"

// Wrappers around functions for Map class that also write to savefile
// See: Map.h
void addResourceToMarket(Resource r, Map& game, string fname);
void addResourceToPool(Resource r, Map& game, string fname);
void addElektroToBank(int amount, Map& game, string fname);
void buyCity(City city, House house, Map& game, string fname);
void printMapToFile(Map& game, string fname);

int main(int argc, char *argv[])
{
    // Valid map file
    string mapFile = "map.txt";
    Map* game = MapLoader::load(mapFile);
    if(game == nullptr) {
        cout << "Could not load " << mapFile << endl;
    } else {
        cout << "Successfully loaded " << mapFile << endl;
    }

    // We will save the game in a new file
    string saveFile = "saved_map.txt";

    // Add tokens to Map
    addResourceToPool(OIL, *game, saveFile);
    cout << "Saved an oil token to the market" << endl;
    addResourceToMarket(COAL, *game, saveFile);
    cout << "Saved a coal resource to the resource pool" << endl;
    addElektroToBank(100, *game, saveFile);
    cout << "Give the bank 100 Elektro" << endl;

    // Give a city a house
    unordered_set<City> cities = game->getCities();

    City city = *(cities.begin());
    House house(PURPLE);
    buyCity(city, house, *game, saveFile);
    cout << "Gave a purple house to 1 city" << endl;
    cout << "See " << saveFile << " to see these results" << endl;

    // Cleanup
    delete game;

    return 0;
}

void addResourceToMarket(Resource r, Map& game, string fname)
{
    game.addResourceToMarket(r);
    printMapToFile(game, fname);
}

void addResourceToPool(Resource r, Map& game, string fname)
{
    game.addResourceToPool(r);
    printMapToFile(game, fname);
}

void addElektroToBank(int amount, Map& game, string fname)
{
    game.addElektroToBank(amount);
    printMapToFile(game, fname);
}

void buyCity(City city, House house, Map& game, string fname)
{
    game.buyCity(city, house);
    printMapToFile(game, fname);
}

void printMapToFile(Map& game, string fname)
{
    ofstream out(fname);
    string mapText = game.printMap();
    const char* data = mapText.c_str();
    out.write(data, mapText.length());
    out.close();
}

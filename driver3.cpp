#include <fstream>
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

void addResourceToMarket(Resource r, Map& game, string fname);
void addResourceToPool(Resource r, Map& game, string fname);
void addElektroToBank(int amount, Map& game, string fname);
void buyCity(City city, House house, Map& game, string fname);
void printMapToFile(Map& game, string fname);

int main(int argc, char *argv[])
{
    string mapFile = "map.txt";
    Map* game = MapLoader::load(mapFile);

    string saveFile = "saved_map.txt";
    addResourceToPool(OIL, *game, saveFile);
    addResourceToMarket(COAL, *game, saveFile);
    addElektroToBank(100, *game, saveFile);

    unordered_set<City> cities = game->getCities();

    City city = *(cities.begin());
    House house(PURPLE);
    buyCity(city, house, *game, saveFile);

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

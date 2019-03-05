#include <string>
#include <vector>
using namespace std;

#include "Graph.h"
#include "City.h"
#include "Elektro.h"
#include "Map.h"
#include "MapLoader.h"

Map::Map(string mapFile)
{
    UndirectedGraph<City>* g = MapLoader::load(mapFile);
    UndirectedGraph<City> m = *g;
    this->powerGridMap = m;
    delete g;
}

void Map::addElektroToBank(int amount)
{
    bank.setElektro(bank.getElektro() + amount);
}

void Map::addResourceToPool(Resource r)
{
    resourcePool.push_back(r);
}

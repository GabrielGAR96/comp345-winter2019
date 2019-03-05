#include <string>
#include <iostream> //test
#include <vector>
using namespace std;

#include "Graph.h"
#include "City.h"
#include "Elektro.h"
#include "Map.h"
#include "MapLoader.h"

Map::Map(UndirectedGraph<City> cities)
{
    powerGridMap = cities;
}

void Map::addElektroToBank(int amount)
{
    bank.setElektro(bank.getElektro() + amount);
}

void Map::addResourceToPool(Resource r)
{
    resourcePool.push_back(r);
}

void Map::addResourceToMarket(Resource r)
{
    if(marketSize == 14) return;
    resourceMarket[marketSize++] = r;
}

void Map::buyCity(City city, House house)
{
    vector<Edge<City> > edges = powerGridMap.getEdges(city);
    City current = powerGridMap.delVertex(city);
    current.build(house);
    powerGridMap.addVertex(current);
    for(Edge<City> e: edges)
    {
        powerGridMap.addEdge(current, e.dest, e.cost);
    }
}

void Map::printMap() const
{
    cout << powerGridMap;
}

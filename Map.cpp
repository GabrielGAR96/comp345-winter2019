#include <string>
#include <iostream> //test
#include <vector>
#include <unordered_set>
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

unordered_set<City> Map::getCities() const
{
    return powerGridMap.getVerts();
}

string Map::printMap() const
{
    string mapText = "";
    mapText += "--CITIES--\n";
    unordered_set<City> cities = powerGridMap.getVerts();
    for(City c : cities)
    {
        mapText += c.getName() + ":" + to_string(c.getRegion()) + ":" + c.getHouses() + "\n";
    }
    mapText += "--CITIES--\n\n";
    mapText += "--CONNECTIONS--\n";
    for(Edge<City> edge: powerGridMap.allEdges())
    {
        mapText += edge.source.getName() + ":" + edge.dest.getName() + ":" + to_string(static_cast<int>(edge.cost)) + "\n";
    }
    mapText += "--CONNECTIONS--\n\n";
    mapText += "--MARKET--\n";
    for(int i = 0; i < marketSize; i++)
    {
        mapText += getResourceName(resourceMarket[i]) + "\n";
    }
    mapText += "--MARKET--\n\n";
    mapText += "--POOL--\n";
    for(Resource r : resourcePool)
    {
        mapText += getResourceName(r) + "\n";
    }
    mapText += "--POOL--\n\n";
    mapText += "--BANK--\n";
    mapText += to_string(bank.getElektro()) + "\n";
    mapText += "--BANK--";
    return mapText;
}

#include <string>
#include <iostream> //test
#include <set>
using namespace std;

#include "Graph.h"
#include "City.h"
#include "Elektro.h"
#include "Map.h"
#include "MapLoader.h"
#include "Resource.h"

Map::Map()
{
}

Map::Map(UndirectedGraph<City> cities)
{
    powergrid = cities;
    market.initialize(pool);
}

void Map::addElektroToBank(int amount)
{
    bank.setElektro(bank.getElektro() + amount);
}

void Map::addResourceToPool(Resource r, int n)
{
    pool.putBack(r, n);
}

void Map::restockMarket(int numPlayers, int step)
{
    market.restock(pool, numPlayers, step);
}

void Map::useRegion(int region)
{
    activeRegions.insert(region);
}

bool Map::test()
{
    UndirectedGraph<City> temp;
    for(City city : powergrid.getVerts())
    {
        if(activeRegions.find(city.getRegion()) != activeRegions.end())
        {
            temp.addVertex(city);
        }
    }
    for(UndirectedEdge<City> edge : powergrid.allEdges())
    {
        temp.addEdge(edge.source, edge.dest, edge.cost);
    }
    return Graph<City>::isConnected(temp);
}

void Map::finalize()
{
    UndirectedGraph<City> temp;
    for(City city : powergrid.getVerts())
    {
        if(activeRegions.find(city.getRegion()) != activeRegions.end())
        {
            temp.addVertex(city);
        }
    }
    for(UndirectedEdge<City> edge : powergrid.allEdges())
    {
        temp.addEdge(edge.source, edge.dest, edge.cost);
    }
    powergrid = temp;
}

void Map::buyCity(City city, House house)
{
    // We Have to add a House but that means changing a vertex in the graph the
    // stratgey is to just save the edges delete the vertex update it then
    // readd the edges... Works but hacky
    vector<Edge<City> > edges = powergrid.getEdges(city);
    City current = powergrid.delVertex(city);
    current.build(house);
    powergrid.addVertex(current);
    for(Edge<City> e: edges)
    {
        powergrid.addEdge(current, e.dest, e.cost);
    }
}

unordered_set<City> Map::getCities() const
{
    return powergrid.getVerts();
}

bool Map::isValid() const
{
    return Graph<City>::isConnected(powergrid);
}

// Conforms to the syntax in map.txt which is a human readable textfile
// containing a portion of an actual Powergrid map
// TODO: Could implement better serialization here and in MapLoader.cpp
string Map::printMap() const
{
    // Sections need to be in proper order (see order of sentinal below)
    string mapText = "";
    mapText += "--CITIES--\n";
    unordered_set<City> cities = powergrid.getVerts();
    for(City c : cities)
    {
        mapText += c.getName() + ":" + to_string(c.getRegion()) + ":" + c.getHouses() + "\n";
    }
    mapText += "--CITIES--\n\n";
    mapText += "--CONNECTIONS--\n";
    for(Edge<City> edge: powergrid.allEdges())
    {
        mapText += edge.source.getName() + ":" + edge.dest.getName() + ":" + to_string(static_cast<int>(edge.cost)) + "\n";
    }
    mapText += "--CONNECTIONS--\n\n";
    mapText += "--MARKET--\n";
    mapText += "COAL: " + to_string(market.getAmount(COAL)) + " OIL: " + to_string(market.getAmount(OIL)) + " GARBAGE: " + to_string(market.getAmount(GARBAGE)) + " URANIUM: " + to_string(market.getAmount(URANIUM)) + "\n";
    mapText += "--MARKET--\n\n";
    mapText += "--POOL--\n";
    mapText += "COAL: " + to_string(pool.getAvailable(COAL)) + " OIL: " + to_string(pool.getAvailable(OIL)) + " GARBAGE: " + to_string(pool.getAvailable(GARBAGE)) + " URANIUM: " + to_string(pool.getAvailable(URANIUM)) + "\n";
    mapText += "--POOL--\n\n";
    mapText += "--BANK--\n";
    mapText += to_string(bank.getElektro()) + "\n";
    mapText += "--BANK--";
    return mapText;
}

ostream& operator<<(ostream& out, const Map& m)
{
    out << m.powergrid;
    return out;
}

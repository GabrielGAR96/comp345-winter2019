#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

#include "MapLoader.h"
#include "Map.h"
#include "Resource.h"

/* Resource getResourceByName(string r); */

Map* MapLoader::load(string& fname)
{
    UndirectedGraph<City> graph;
    ifstream input;
    input.open(fname);
    string sentinal;
    string infoLine;

    // Read fname under the assumption that it has the correct format
    // If not then always return null as indication that Map could not be loaded
    if(input.eof()) return nullptr;
    input >> sentinal;
    if(sentinal != "--CITIES--") return nullptr;
    
    // Collect cities for vertex population and later edge creation
    unordered_map<string, City> cities;
    while(input >> infoLine)
    {
        if(infoLine == sentinal) break;
        size_t start = 0;
        size_t end = infoLine.find(":");
        string name = infoLine.substr(start, end - start);
        start = end + 1;
        int region = stoi(infoLine.substr(start));
        City city(name, region);
        graph.addVertex(city);
        cities.insert({name, city});
    }

    // Collect information about edges
    if(input.eof()) return nullptr;
    input >> sentinal;
    if(sentinal != "--CONNECTIONS--") return nullptr;
    while(input >> infoLine)
    {
        if(infoLine == sentinal) break;
        size_t start = 0;
        size_t end = infoLine.find(":", start);
        string source = infoLine.substr(start, end - start);
        start = end + 1;
        end = infoLine.find(":", start);
        string dest = infoLine.substr(start, end - start);
        start = end + 1;
        int cost = stoi(infoLine.substr(start));
        graph.addEdge(cities[source], cities[dest], cost);
    }

    // We know enough to make the Powergrid
    Map* powerGrid = new Map(graph);

    // Collect the information about other game areas
    input >> sentinal;
    if(sentinal != "--MARKET--")
    {
        // powerGrid is a pointer if we don't plan on using it we should delete
        // it here
        delete powerGrid;
        return nullptr;
    }
    while(input >> infoLine)
    {
        if(infoLine == sentinal) break;
    }

    input >> sentinal;
    if(sentinal != "--POOL--")
    {
        delete powerGrid;
        return nullptr;
    }
    while(input >> infoLine)
    {
        if(infoLine == sentinal) break;
        powerGrid->addResourceToPool(getResourceByName(infoLine), 1);
    }

    input >> sentinal;
    if(sentinal != "--BANK--")
    {
        delete powerGrid;
        return nullptr;
    }
    input >> infoLine;
    if(infoLine != sentinal) powerGrid->addElektroToBank(stoi(infoLine));

    input.close();
    return powerGrid;
}

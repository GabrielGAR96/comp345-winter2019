#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

#include "MapLoader.h"
#include "Map.h"
#include "Resource.h"

BadMap::BadMap(string msg)
    : logic_error(msg)
{}

Map* MapLoader::load(string& fname)
{
    fname = "./maps/" + fname;
    UndirectedGraph<City> graph;
    ifstream input;
    input.open(fname);
    string sentinal;
    string infoLine;

    // Read fname under the assumption that it has the correct format
    // If not then always return null as indication that Map could not be loaded
    if(input.eof()) throw BadMap("Cannot read " + fname + " because it is malformed");
    input >> sentinal;
    if(sentinal != "--CITIES--") throw BadMap("Cannot read " + fname + " because it is malformed");

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
    if(input.eof()) throw BadMap("Cannot read " + fname + " because it is malformed");
    input >> sentinal;
    if(sentinal != "--CONNECTIONS--") throw BadMap("Cannot read " + fname + " because it is malformed");
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
    if(!powerGrid->isValid()) {
        delete powerGrid;
        throw BadMap(fname + " represents a disconnected map");
    }

    input.close();
    return powerGrid;
}

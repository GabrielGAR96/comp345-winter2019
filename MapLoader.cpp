#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

#include "MapLoader.h"
#include "City.h"
#include "Graph.h"

UndirectedGraph<City>* MapLoader::load(string& fname)
{
    UndirectedGraph<City>* map = new UndirectedGraph<City>();
    ifstream input;
    input.open(fname);
    string sentinal;
    string infoLine;
    input >> sentinal;
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
        map->addVertex(city);
        cities.insert({name, city});
    }
    input >> sentinal;
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
        map->addEdge(cities[source], cities[dest], cost);
    }
    input.close();
    return map;
}

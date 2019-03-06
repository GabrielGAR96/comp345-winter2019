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

    if(input.eof()) return nullptr;
    input >> sentinal;
    if(sentinal != "--CITIES--") return nullptr;
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

    Map* powerGrid = new Map(graph);

    // if(!input.eof())
    // {
    //     input >> sentinal;
    //     if(sentinal != "--MARKET--")
    //     {
    //         delete powerGrid;
    //         return nullptr;
    //     }
    //     while(input >> infoLine)
    //     {
    //         powerGrid->addResourceToMarket(getResourceByName(infoLine));
    //     }
    // }

    // if(!input.eof())
    // {
    //     input >> sentinal;
    //     if(sentinal != "--POOL--")
    //     {
    //         delete powerGrid;
    //         return nullptr;
    //     }
    //     while(input >> infoLine)
    //     {
    //         powerGrid->addResourceToPool(getResourceByName(infoLine));
    //     }
    // }

    // if(!input.eof())
    // {
    //     input >> sentinal;
    //     if(sentinal != "--BANK--")
    //     {
    //         delete powerGrid;
    //         return nullptr;
    //     }
    //     input >> infoLine;
    //     powerGrid->addElektroToBank(stoi(infoLine));
    // }

    input.close();
    return powerGrid;
}

/* Resource getResourceByName(string r) */
/* { */
/*     if(r == "coal") return COAL; */
/*     if(r == "oil") return OIL; */
/*     if(r == "garbage") return GARBAGE; */
/*     if(r == "uranium") return URANIUM; */
/*     return COAL; // keep compiler happy */
/* } */

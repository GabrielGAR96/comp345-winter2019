#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
using namespace std;

#include "City.h"
#include "Graph.h"

class MapLoader
{
    public:
        static UndirectedGraph<City>* load(string& fname);
};

#endif
